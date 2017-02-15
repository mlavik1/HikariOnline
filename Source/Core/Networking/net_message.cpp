#include "net_message.h"

#include <sstream>
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	NetMessage::NetMessage()
		: mMessageType(NetMessageType::Ignored), mMessageLength(0)
	{
		SetMessage("");
	}

	NetMessage::NetMessage(const char* arg_message)
	{
		msgprefix_t prefix = *(reinterpret_cast<msgprefix_t*>((char*)arg_message));
		if (prefix != NetMessagePrefix)
		{
			NetMessage(NetMessageType::Ignored, 0, "");
			return;
		}
		mMessageType = (NetMessageType)*(reinterpret_cast<msgtype_t*>((char*)arg_message + sizeof(msgprefix_t)));
		mMessageLength = *(reinterpret_cast<msglen_t*>((char*)arg_message + sizeof(msgprefix_t) + sizeof(msgtype_t)));
		msgcount_t partCount = *(reinterpret_cast<msgcount_t*>((char*)arg_message + sizeof(msgprefix_t) + sizeof(msgtype_t) + sizeof(msglen_t)));
		std::string msg = std::string((char*)arg_message + sizeof(msgprefix_t) + sizeof(msgtype_t) + sizeof(msglen_t) + sizeof(msgcount_t), mMessageLength);
		SetMessage(msg);

		mNumMessageParts = partCount; // Must come after SetMessage   -  TODO: Find a better solution
	}

	NetMessage::NetMessage(NetMessageType arg_type, msglen_t arg_length, const char* arg_message)
	{
		mMessageType = arg_type;
		mMessageLength = arg_length;
		SetMessage(std::string(arg_message, mMessageLength));
	}

	NetMessage::NetMessage(NetMessageType arg_type, std::string arg_message)
	{
		mMessageType = arg_type;
		mMessageLength = arg_message.size();
		SetMessage(arg_message);
	}

	NetMessage::~NetMessage()
	{
	}

	bool NetMessage::GetIsValid() const
	{
		return (mNumMessageParts == mMessageParts.size());
	}

	void NetMessage::AppendMessage(std::string arg_part)
	{
		mMessageParts.push_back(arg_part);
	}

	void NetMessage::SetMessage(std::string arg_message)
	{
		int maxMessageLength = NetMessageMaxLength - (GetTotalLength() - GetMessageLength());
		int strlen = arg_message.size();

		if (strlen > 0)
			mNumMessageParts = strlen / maxMessageLength + 1;
		else
			mNumMessageParts = 1;

		if (strlen < maxMessageLength)
			mMessageParts.push_back(arg_message);
		else
		{
			for (int i = 0; i < mNumMessageParts; i++)
			{
				int start = maxMessageLength*i;
				int length = maxMessageLength;
				if (start + length > strlen)
					length = strlen - start;
				mMessageParts.push_back(arg_message.substr(start, length));
			}
		}

		__AssertComment(mNumMessageParts == mMessageParts.size(), "Invalid message part count");
	}

	std::string	NetMessage::GetMessage() const
	{
		std::ostringstream oss;
		for (size_t i = 0; i < mMessageParts.size(); i++)
		{
			oss << mMessageParts[i];
		}
		return oss.str();
	}

	std::string NetMessage::GetStringRepresentation(int arg_part)
	{
		__AssertComment(mMessageParts.size() == mNumMessageParts, "Message part vector has been modified without updating count");
		__AssertComment(arg_part < mMessageParts.size(), "Out of bounds");

		std::ostringstream ss;

		char * chararr = const_cast<char *>(reinterpret_cast<const char *>(&NetMessagePrefix));
		for (std::size_t i = 0; i != sizeof(msgprefix_t); ++i)
			ss << chararr[i];

		chararr = reinterpret_cast<char *>(&mMessageType);
		for (std::size_t i = 0; i != sizeof(msgtype_t); ++i)
			ss << chararr[i];

		chararr = reinterpret_cast<char *>(&mMessageLength);
		for (std::size_t i = 0; i != sizeof(msglen_t); ++i)
			ss << chararr[i];

		chararr = reinterpret_cast<char *>(&mNumMessageParts);
		for (std::size_t i = 0; i != sizeof(msgcount_t); ++i)
			ss << chararr[i];

		chararr = const_cast<char *>(mMessageParts[arg_part].c_str());
		for (std::size_t i = 0; i != (size_t)mMessageLength; ++i)
			ss << chararr[i];
		int a = ss.str().size();
		int b = GetTotalLength();
		__AssertComment(ss.str().size() == GetTotalLength(), "Length of string representation does not match total length of NetMessage. Should equal header size + message length.");

		return ss.str();

	}


	NetMessage NetMessage::operator=(NetMessage &arg_other)
	{
		return NetMessage(arg_other.GetMessageType(), arg_other.GetMessageLength(), arg_other.GetMessage().c_str());
	}
}
