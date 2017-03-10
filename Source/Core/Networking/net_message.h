#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#include <string>
#include <vector>
#include "net_message_type.h"

typedef uint16_t msgprefix_t;
typedef uint8_t msgtype_t;
typedef uint16_t msglen_t;
typedef uint8_t msgcount_t;

namespace Hikari
{
	class NetMessage
	{
	private:
		NetMessageType				mMessageType;
		msglen_t					mMessageLength;
		std::vector<std::string>	mMessageParts;
		msgcount_t					mNumMessageParts;

		const msgprefix_t			NetMessagePrefix = 52134; // don't need this anymore
		const size_t				NetMessageMaxLength = 4000;

	public:
		NetMessage();
		NetMessage(const char* arg_message);
		NetMessage(NetMessageType arg_type, msglen_t arg_length, const char* arg_message);
		NetMessage(NetMessageType arg_type, std::string arg_message);
		~NetMessage();
		NetMessage				operator=(NetMessage &arg_other);

		inline NetMessageType	GetMessageType() const { return mMessageType; }
		inline msglen_t			GetMessageLength() const { return mMessageLength; }
		inline msgcount_t		GetMessagePartCount() const { return mNumMessageParts; }
		inline size_t			GetTotalLength() const { return GetMessageLength() + sizeof(msgprefix_t) + sizeof(msgtype_t) + sizeof(msglen_t) + sizeof(msgcount_t); }

		std::string		GetMessage() const;
		std::string		GetStringRepresentation(int arg_part = 0) const;
		bool			GetIsValid() const;

		void			SetMessage(std::string arg_message);
		void			AppendMessage(std::string arg_part);

	};
}


#endif // #ifndef NETMESSAGE_H
