#pragma once

#include "../CommonHelpers.h"
#include <stdlib.h>

class BlockAllocator
{
public:
	static const u_int32 HEAP_SIZE = GB(1);
	static void Init();
	static void* Allocate(size_t size);
	static void Free(void *p);

private:
	static void *allocLocation;
	typedef struct _blockEntry {
		void *address;
		u_int32 size;
		_blockEntry *nextEntry;
	} blockEntry;
	static blockEntry *blocks, *prevBlock;
};

