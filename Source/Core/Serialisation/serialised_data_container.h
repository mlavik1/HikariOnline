#ifndef HIKARI_SERIALISEDDATACONTAINER_H
#define HIKARI_SERIALISEDDATACONTAINER_H

#include "i_serialisable.h"

namespace Hikari
{
	class SerialisedDataContainer : public ISerialisable
	{
	private:
		char* mData = nullptr;
		size_t mDataSize = 0;

	public:
		SerialisedDataContainer();
		SerialisedDataContainer(SerialisedDataContainer& arg_other);
		~SerialisedDataContainer();

		virtual void Read(DataWriter& arg_writer) override;
		virtual void Write(DataWriter& arg_writer) override;

		void SetData(const void* arg_data, const size_t& arg_bytes);

		inline char* GetData() { return mData; }
		inline size_t GetDataSize() { return mDataSize; }
	};
}

#endif
