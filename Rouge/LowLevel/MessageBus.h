#pragma once
#include "../CommonHelpers.h"
#include <mutex>

class MessageBus
{
public:
	enum class MessageType {
		None = 0, Gameplay = 1, Window = 1 << 1, Input = 1 << 2, Render = 1 << 3, Audio = 1 << 4, Physics = 1 << 5, AI = 1 << 6, GPGPU = 1 << 7, Resource = 1 << 8, Animation = 1 << 9
	};
	ENUM_FLAGS(MessageType)

	typedef struct _message {
		MessageType Type;
		s_int32 ParseInfo;
		void *Data;
	} Message;

	static void Initialize();
	static void QueueMessage(MessageBus::Message msg);
	static void RegisterSystem(MessageBus::MessageType types, void(*handler)(MessageBus::Message));

private:
	static const u_int32 MAX_SYSTEMS = 128;

	struct RegisteredSystems {
		MessageBus::MessageType types;
		void(*handler)(MessageBus::Message);
	};

	static MessageBus::RegisteredSystems systems[MAX_SYSTEMS];

};

