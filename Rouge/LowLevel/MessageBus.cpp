#include "MessageBus.h"

MessageBus::RegisteredSystems MessageBus::systems[MessageBus::MAX_SYSTEMS];
u_int32 registeredSystemCount = 0;

void MessageBus::Initialize()
{
	//Initialize the array of message handlers
	for (u_int32 i = 0; i < MessageBus::MAX_SYSTEMS; i++) {
		MessageBus::systems[i].handler = nullptr;
		MessageBus::systems[i].types = MessageBus::MessageType::None;
	}
}

void MessageBus::QueueMessage(MessageBus::Message msg)
{
	//TODO maybe we need thread safety mechanisms here
	//Queue a message ad send the message to all hte systems that are registered to recieve messages about that event
	for (u_int32 i = 0; i < registeredSystemCount; i++) {
		if (flags(msg.Type & MessageBus::systems[i].types)) {
			MessageBus::systems[i].handler(msg);
		}
	}
}

std::mutex registerMutex;
void MessageBus::RegisterSystem(MessageBus::MessageType types, void(*handler)(MessageBus::Message))
{
	registerMutex.lock();
	//Register a new system into the system
	MessageBus::systems[registeredSystemCount].handler = handler;
	MessageBus::systems[registeredSystemCount].types = types;
	registeredSystemCount++;

	registerMutex.unlock();
}
