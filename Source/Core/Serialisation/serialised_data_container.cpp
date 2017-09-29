#include "serialised_data_container.h"

namespace Hikari
{
	SerialisedDataContainer::SerialisedDataContainer()
	{

	}

	SerialisedDataContainer::SerialisedDataContainer(SerialisedDataContainer& arg_other)
	{
		if (mData != nullptr)
		{
			delete[] mData;
		}
		if (arg_other.GetData() != nullptr)
		{
			mData = new char[arg_other.GetDataSize()];
			SetData(arg_other.GetData(), arg_other.GetDataSize());
		}
	}

	SerialisedDataContainer::~SerialisedDataContainer()
	{
		if (mData != nullptr)
		{
			delete[] mData;
		}
	}

	void SerialisedDataContainer::Read(DataWriter& arg_writer)
	{
		if (mData != nullptr)
		{
			delete[] mData;
		}
		arg_writer.Read(&mDataSize, sizeof(size_t));
		mData = new char[mDataSize];
		arg_writer.Read(mData, mDataSize);
	}

	void SerialisedDataContainer::Write(DataWriter& arg_writer)
	{
		if (mData != nullptr)
		{
			arg_writer.Write(&mDataSize, sizeof(size_t));
			arg_writer.Write(mData, mDataSize);
		}
	}

	void SerialisedDataContainer::SetData(const void* arg_data, const size_t& arg_bytes)
	{
		if (mData != nullptr)
		{
			delete[] mData;
		}
		mData = new char[arg_bytes];
		mDataSize = arg_bytes;
		memcpy(mData, arg_data, arg_bytes);
	}

}
