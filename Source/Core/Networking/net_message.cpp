#include "net_message.h"

#include <sstream>
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	NetMessage::NetMessage()
		: mMessageData(nullptr)
	{

	}

	NetMessage::NetMessage(NetMessageType arg_type)
		: mMessageType(arg_type), mMessageLength(0)
	{
	}

	NetMessage::NetMessage(const char* arg_message)
	{
		msgprefix_t prefix = *(reinterpret_cast<msgprefix_t*>((char*)arg_message));
		if (prefix != NetMessagePrefix)
		{
			NetMessage(NetMessageType::Ignored, 0, "");
			return;
		}
		SetMessageHeader(arg_message);
		// TODO: Do not copy so much! D:
		std::string msg = std::string((char*)arg_message + sizeof(msgprefix_t) + sizeof(msgtype_t) + sizeof(msglen_t), mMessageLength);
		SetMessageData(msg.c_str(), msg.size());
	}

	NetMessage::NetMessage(NetMessageType arg_type, msglen_t arg_length, const char* arg_message)
	{
		mMessageType = arg_type;
		mMessageLength = arg_length;
		SetMessageData(arg_message, mMessageLength);
	}

	NetMessage::NetMessage(NetMessageType arg_type, std::string arg_message)
	{
		mMessageType = arg_type;
		mMessageLength = arg_message.size() + 1;
		SetMessageData(arg_message.c_str(), mMessageLength);
	}

	NetMessage::~NetMessage()
	{
		if (mMessageData != nullptr)
		{
			delete mMessageData;
		}
	}

	NetMessage::NetMessage(const NetMessage& arg_other)
		: mMessageType(arg_other.mMessageType), mMessageLength(arg_other.mMessageLength)
	{
		SetMessageData(arg_other.mMessageData, arg_other.mMessageLength);
	}

	NetMessage NetMessage::operator=(NetMessage &arg_other)
	{
		return NetMessage(arg_other.GetMessageType(), arg_other.GetMessageLength(), arg_other.GetMessageData());
	}

	bool NetMessage::GetIsValid() const
	{
		return true; // TODO
	}

	void NetMessage::SetMessageData(const char* arg_message, size_t arg_length)
	{
		if (arg_length > 0)
		{
			mMessageData = new char[arg_length];
			memcpy(mMessageData, arg_message, arg_length);
		}
		else
		{
			mMessageData = nullptr;
		}
	}

	void NetMessage::SetMessageDataPtr(char* arg_ptr, msglen_t arg_bytes)
	{
		mMessageData = arg_ptr;
		mMessageLength = arg_bytes;
	}

	const char*	NetMessage::GetMessageData() const
	{
		return mMessageData;
	}

	std::string NetMessage::GetStringRepresentation() const
	{
		std::ostringstream ss;

		const char * chararr = const_cast<char *>(reinterpret_cast<const char *>(&NetMessagePrefix));
		for (std::size_t i = 0; i != sizeof(msgprefix_t); ++i)
			ss << chararr[i];

		chararr = reinterpret_cast<const char *>(&mMessageType);
		for (std::size_t i = 0; i != sizeof(msgtype_t); ++i)
			ss << chararr[i];

		chararr = reinterpret_cast<const char *>(&mMessageLength);
		for (std::size_t i = 0; i != sizeof(msglen_t); ++i)
			ss << chararr[i];

		chararr = const_cast<char *>(mMessageData);
		for (std::size_t i = 0; i != (size_t)mMessageLength; ++i)
			ss << chararr[i];
		int a = ss.str().size();
		int b = GetTotalLength();
		__AssertComment(ss.str().size() == GetTotalLength(), "Length of string representation does not match total length of NetMessage. Should equal header size + message length.");

		return ss.str();
	}

	void NetMessage::SetMessageHeader(const char* arg_message)
	{
		mMessageType = (NetMessageType)*(reinterpret_cast<msgtype_t*>((char*)arg_message + sizeof(msgprefix_t)));
		mMessageLength = *(reinterpret_cast<msglen_t*>((char*)arg_message + sizeof(msgprefix_t) + sizeof(msgtype_t)));
	}

}
