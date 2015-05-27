#include "MemoryManager.h"

thread_local struct MemoryManager::pageData MemoryManager::pages[PAGE_COUNT];

void MemoryManager::Initialize()
{
	int blockSize = MIN_BLOCK_SIZE;
	for (int pageID = 0; pageID < PAGE_COUNT; pageID++)
	{
		MemoryManager::pages[pageID].pageID = pageID;
		MemoryManager::pages[pageID].blockSize = blockSize;
		MemoryManager::pages[pageID].pageLocation = (void*)0;	//Initialize this to 0, we will allocate the page the first time the size is requested
		memset(MemoryManager::pages[pageID].blockStates, (u_int32)0, BlOCK_STATE_COUNT * sizeof(u_int32));

		blockSize *= 2;	//Next Po2 please!
	}
}

void * MemoryManager::Alloc(size_t size)	//TODO for debug mode implement buffer overrun detection
{
	if (size > MAX_BLOCK_SIZE)return BlockAllocator::Allocate(size);
	if (size == 0)return 0;

	void *allocLocation = nullptr;
	u_int32 blockIndex = 0;

	u_int32 rSize = (u_int32)uPoT((u_int32)size);
	s_int32 pageID = Math::log2(rSize / MIN_BLOCK_SIZE);	//This should allow us to instantly get the page ID based off of the size rather than having to search

	//If a page hasn't been allocated for this, allocate it
	if (pages[pageID].pageLocation == (void*)0)pages[pageID].pageLocation = malloc(pages[pageID].blockSize * BLOCK_COUNT);


	for (s_int32 blockID = 0; blockID < BlOCK_STATE_COUNT; blockID++) {
		if (pages[pageID].blockStates[blockID] != UINT32_MAX) {		//Check if the block is full, skip if it is full
			for (u_int32 i = 0; i < sizeof(u_int32) * CHAR_BIT; i++) {
				if (!CHECK_BIT(pages[pageID].blockStates[blockID], i)) {
					pages[pageID].blockStates[blockID] = SET_BIT(pages[pageID].blockStates[blockID], i);	//Mark the block as in use
					blockIndex = blockID * (sizeof(u_int32) * CHAR_BIT) + (u_int32)i;
					allocLocation = (void*)((u_int32)pages[pageID].pageLocation + (pages[pageID].blockSize * blockIndex));
					break;
				}
			}
			break;
		}
	}

	//If an allocLocation still wasn't found, repeat on higher page annd return that
	if (allocLocation == nullptr) {
		return MemoryManager::Alloc(rSize + 1);
	}
	//TODO if all pages are full this will create a very large unnecessary allocation on heap which should be handled


	LOG__INFO("Allocated %v(%v) bytes", rSize, size);
	//Find empty page in requested, allocate page if not allocated, if not enough room, allocate in higher page, if that fails, allocate on heap
	return allocLocation;
}

void MemoryManager::Free(void * p)
{
	//Find out which page this pointer is in and update the memory map
	//TODO maybe cache optimization?

	u_int32 pointerVal = (u_int32)p;

	for (u_int8 index = 0; index < PAGE_COUNT; index++)
	{
		u_int32 blockIndex = (pointerVal - (u_int32)pages[index].pageLocation) / (u_int32)pages[index].blockSize;
		if (blockIndex < BLOCK_COUNT)	//Does this pointer belong to this block?
		{
			//Calculate the exact block index
			u_int32 blockBit = blockIndex % (sizeof(u_int32) * CHAR_BIT);
			u_int8 blockOff = blockIndex / (sizeof(u_int32) * CHAR_BIT);
			pages[index].blockStates[blockOff] = CLEAR_BIT(pages[index].blockStates[blockOff], blockBit);
			LOG__INFO("Freed %v bytes", pages[index].blockSize);
			pointerVal = 0;
			break;
		}
	}
}