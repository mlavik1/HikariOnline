#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#include <string>
#include <vector>
#include "net_message_type.h"

typedef uint16_t msgprefix_t;
typedef uint8_t msgtype_t;
typedef uint16_t msglen_t;

namespace Hikari
{
	class NetMessage
	{
	private:
		NetMessageType				mMessageType;
		msglen_t					mMessageLength;
		char*						mMessageData;

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
		inline size_t			GetTotalLength() const { return GetMessageLength() + sizeof(msgprefix_t) + sizeof(msgtype_t) + sizeof(msglen_t); }

		const char*		GetMessageData() const;
		std::string		GetStringRepresentation() const;
		bool			GetIsValid() const;

		void			SetMessageData(const char* arg_message, size_t arg_length);
		void			SetMessageHeader(const char* arg_message);

	};
}


#endif // #ifndef NETMESSAGE_H
