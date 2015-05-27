#include "BlockAllocator.h"

void* BlockAllocator::allocLocation;
BlockAllocator::blockEntry *BlockAllocator::blocks, *BlockAllocator::prevBlock;

void BlockAllocator::Initialize()
{
	allocLocation = malloc(HEAP_SIZE);
	blocks = (blockEntry*)malloc(sizeof(blockEntry));
	prevBlock = blocks;

	blocks->address = allocLocation;
	blocks->size = HEAP_SIZE;
	blocks->nextEntry = (blockEntry*)0;
}

void * BlockAllocator::Allocate(size_t size)
{
	if (size <= prevBlock->size) {
		blockEntry *nextEntry = (blockEntry*)malloc(sizeof(blockEntry));
		nextEntry->address = (void*)((u_int32)prevBlock->address + size);
		nextEntry->size = prevBlock->size - size;
		nextEntry->nextEntry = (blockEntry*)0;

		prevBlock->nextEntry = nextEntry;
		return prevBlock->address;
	}
	else {
		return nullptr;
	}
}

void BlockAllocator::Free(void * p)
{
	//Find the block with the same address
	blockEntry *curEntry = blocks;
	while (curEntry != (blockEntry*)0 && curEntry->address != p) {
		curEntry = blocks->nextEntry;
	}

	//TODO figure out how to deal with the problems with this allocator, once the HEAP_SIZE is exhausted the allocator will fail
}
