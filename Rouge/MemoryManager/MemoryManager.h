#pragma once
#include <mutex>
#include "../CommonHelpers.h"
#include "BlockAllocator.h"
#include "../Math/SimpleMath.h"

//This number is chosen to limit the amount of memory consumed
const u_int32 PAGE_COUNT = 7;
const u_int32 MIN_BLOCK_SIZE = BYTES(16);
const u_int32 MAX_BLOCK_SIZE = KB(1);
const u_int32 BLOCK_COUNT = 2048;

//Contains the size in bytes of a single array storing the state of all the blocks in the page
const u_int32 BlOCK_STATE_COUNT = BLOCK_COUNT / (sizeof(u_int32) * CHAR_BIT);

const char CACHE_FILE[] = "MemoryCache.tmp";

class MemoryManager
{
public:
	static void Init();
	static void* Alloc(size_t size);
	static void Free(void *p);
	static void Defrag();

private:
	struct pageData {
		u_int16 pageID;
		u_int16 blockSize;
		u_int32 blockStates[BlOCK_STATE_COUNT];
		void* pageLocation;
	};
	thread_local static struct pageData pages[PAGE_COUNT];
};

