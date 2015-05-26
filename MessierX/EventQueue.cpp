#include "EventQueue.h"

EventQueue::EventQueue()
{
	headPosition = 0;
	tailPosition = 0;
	entryCount = 0;
}


EventQueue::~EventQueue()
{
}

u_int32 EventQueue::EnqueueMessage(Entry message)
{
	if (entryCount + 1 != MAX_ITEMS) {
		entryCount++;
		entries[tailPosition].details = message.details;
		entries[tailPosition].entryType = message.entryType;
		tailPosition = ++tailPosition % MAX_ITEMS;
	}
	return entryCount;
}

EventQueue::Entry EventQueue::PeekMessage()
{
	if (entryCount != 0) {
		return entries[headPosition];
	}
	else {
		return Entry(EntryType::None, 0);	//Return a blank Entry object if there's nothing present
	}
}

//TODO multiple systems can listen to this, so how does one decide to dequeue a message?
EventQueue::Entry EventQueue::DequeueMessage()
{
	Entry toRet = PeekMessage();
	if (toRet.details != (void*)0 && toRet.entryType != EntryType::None) {
		entryCount--;
		headPosition = ++headPosition % MAX_ITEMS;
	}
	return toRet;
}
