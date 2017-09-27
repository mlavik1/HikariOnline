#ifndef HIKARI_FUNCTION_H
#define HIKARI_FUNCTION_H

#include "Core/Object/object.h"
#include <string>

namespace Hikari
{
	class FunctionArgContainer
	{
	public:
		char* mData;
		size_t mSize;

		FunctionArgContainer()
			: mData(nullptr)
		{
		}

		template <typename T>
		inline const size_t getsize(const T& t)
		{
			if (std::is_same<T, std::string>::value)
			{
				return ((std::string*)&t)->length() + 1;
			}
			return sizeof(t);
		}

		FunctionArgContainer(const FunctionArgContainer& arg_other)
		{
			mSize = arg_other.mSize;
			if (arg_other.mData != nullptr)
			{
				mData = new char[mSize];
				memcpy(mData, arg_other.mData, mSize);
			}
		}

		~FunctionArgContainer()
		{
			if (mData)
				delete mData;
		}

		/**
		* Copy data of type T into memory location at arg_dest.
		* @param arg_dest Memory location to copy data to.
		* @param t Value of type T that we want to copy.
		**/
		template <typename T>
		inline void CopyData(void* arg_dest, const T& t)
		{
			if (std::is_same<T, std::string>::value)
			{
				const std::string& str = (*((std::string*)&t));
				memcpy(arg_dest, (*((std::string*)&t)).c_str(), str.length() + 1);
			}
			else
			{
				*(T*)arg_dest = t;
			}
		}

		template <typename T1>
		void TemplateConstruct(T1 t1)
		{
			mSize = getsize(t1);
			mData = new char[mSize];
			CopyData<T1>((mData), t1);
		}

		template <typename T1, typename T2>
		void TemplateConstruct(T1 t1, T2 t2)
		{
			mSize = getsize(t1) + getsize(t2);
			mData = new char[mSize];
			CopyData<T1>((mData), t1);
			CopyData<T2>((mData + getsize(t1)), t2);
		}

		template <typename T1, typename T2, typename T3>
		void TemplateConstruct(T1 t1, T2 t2, T3 t3)
		{
			mSize = getsize(t1) + getsize(t2) + getsize(t3);
			mData = new char[mSize];
			CopyData<T1>((mData), t1);
			CopyData<T2>((mData + getsize(t1)), t2);
			CopyData<T3>((mData + getsize(t1) + getsize(t2)), t3);
		}

		/**
		* Convert raw data to type T.
		**/
		template <typename T>
		inline const T ConvertData(char* arg_data)
		{
			if (std::is_same<T, std::string>::value)
			{
				return *(T*)&std::string(arg_data);
			}
			return *((T*)arg_data);
		}

		template <typename T1>
		void TemplateAccess(T1 &t1)
		{
			t1 = ConvertData<T1>(mData);
		}

		template <typename T1, typename T2>
		void TemplateAccess(T1 &t1, T2 &t2)
		{
			t1 = ConvertData<T1>(mData);
			t2 = ConvertData<T2>((mData + getsize(t1)));
		}

		template <typename T1, typename T2, typename T3>
		void TemplateAccess(T1 &t1, T2 &t2, T3 &t3)
		{
			t1 = ConvertData<T1>(mData);
			t2 = ConvertData<T2>((mData + getsize(t1)));
			t3 = ConvertData<T3>((mData + getsize(t1) + getsize(t2)));
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
