#ifndef HIKARI_INITIALREPLICATIONDATA_H
#define HIKARI_INITIALREPLICATIONDATA_H

#include "Core/Serialisation/i_serialisable.h"

namespace Hikari
{
	class InitialReplicationData
	{
	public:
		~InitialReplicationData();

		/**
		* Returns the size of this class (in bytes)
		*/
		virtual size_t GetSize() { return 0; };
	};
}

#endif // HIKARI_INITIALREPLICATIONDATA_H
