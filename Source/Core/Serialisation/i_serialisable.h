#ifndef HIKARI_ISERIALISABLE_H
#define HIKARI_ISERIALISABLE_H

#include "data_writer.h"

namespace Hikari
{
	class ISerialisable
	{
		virtual void Read(DataWriter& arg_writer) = 0;
		virtual void Write(DataWriter& arg_writer) = 0;
	};
}

#endif
