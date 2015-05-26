#pragma once
#include "CommonHelpers.h"

//Represents a generic message queue
class EventQueue
{
public:
	enum class EntryType {
		None = 0, Message, Command
	};

	typedef struct _entry {
		void *details;
		EntryType entryType;
		_entry() {}
		_entry(EntryType eType, void* detail)
		{
			entryType = eType;
			details = detail;
		}
	}Entry;

	static const u_int32 MAX_ITEMS = 256;

	u_int32 headPosition, tailPosition, entryCount;

	Entry entries[MAX_ITEMS];
	EventQueue();
	~EventQueue();
	u_int32 EnqueueMessage(Entry message);
	EventQueue::Entry PeekMessage();
	EventQueue::Entry DequeueMessage();

};

