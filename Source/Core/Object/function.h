#ifndef HIKARI_FUNCTION_H
#define HIKARI_FUNCTION_H

#include "Core/Object/object.h"
#include <string>
#include "Core/Serialisation/data_serialisation.h"
#include "Core/Serialisation/data_writer.h"

namespace Hikari
{
	class FunctionArgContainer
	{
	public:
		DataWriter mDataWriter;

		FunctionArgContainer()
			: mDataWriter(30)
		{
		}

		FunctionArgContainer(const FunctionArgContainer& arg_other)
			: mDataWriter(arg_other.mDataWriter)
		{
		}

		FunctionArgContainer(const char* arg_data, const size_t& arg_size)
			: mDataWriter(arg_size)
		{
			mDataWriter.Write(arg_data, arg_size);
		}

		~FunctionArgContainer()
		{
		}

		const char* GetData() const
		{
			return mDataWriter.GetData();
		}

		const size_t& GetSize() const
		{
			return mDataWriter.mBytesWritten;
		}

		template <typename T1>
		void TemplateConstruct(T1 t1)
		{
			TypeSerialisationTraits<T1>::Write(mDataWriter, t1);
		}

		template <typename T1, typename T2>
		void TemplateConstruct(T1 t1, T2 t2)
		{
			TypeSerialisationTraits<T1>::Write(mDataWriter, t1);
			TypeSerialisationTraits<T2>::Write(mDataWriter, t2);
		}

		template <typename T1, typename T2, typename T3>
		void TemplateConstruct(T1 t1, T2 t2, T3 t3)
		{
			TypeSerialisationTraits<T1>::Write(mDataWriter, t1);
			TypeSerialisationTraits<T2>::Write(mDataWriter, t2);
			TypeSerialisationTraits<T3>::Write(mDataWriter, t3);
		}

		template <typename T1>
		void TemplateAccess(T1 &t1)
		{
			TypeSerialisationTraits<T1>::Read(mDataWriter, t1);
		}

		template <typename T1, typename T2>
		void TemplateAccess(T1 &t1, T2 &t2)
		{
			TypeSerialisationTraits<T1>::Read(mDataWriter, t1);
			TypeSerialisationTraits<T2>::Read(mDataWriter, t2);
		}

		template <typename T1, typename T2, typename T3>
		void TemplateAccess(T1 &t1, T2 &t2, T3 &t3)
		{
			TypeSerialisationTraits<T1>::Read(mDataWriter, t1);
			TypeSerialisationTraits<T2>::Read(mDataWriter, t2);
			TypeSerialisationTraits<T3>::Read(mDataWriter, t3);
		}

	};

	class Function
	{
	public:
		std::string mFunctionName;
		void(Hikari::Object::*mFunctionPointer)(FunctionArgContainer);

	public:
		Function(std::string arg_name, void(Hikari::Object::*arg_functionptr)(FunctionArgContainer))
		{
			mFunctionName = arg_name;
			mFunctionPointer = arg_functionptr;
		}
	
	};
}

#endif
