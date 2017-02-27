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
		{

		}

		template <typename T1>
		void TemplateConstruct(T1 t1)
		{
			mSize = sizeof(T1);
			mData = new char(mSize);
			*((T1*)mData) = t1;
		}

		template <typename T1, typename T2>
		void TemplateConstruct(T1 t1, T2 t2)
		{
			mSize = sizeof(T1) + sizeof(T2);
			mData = new char(mSize);
			*((T1*)mData) = t1;
			*((T2*)(mData + sizeof(T1))) = t2;
		}

		template <typename T1, typename T2, typename T3>
		void TemplateConstruct(T1 t1, T2 t2, T3 t3)
		{
			mSize = sizeof(T1) + sizeof(T2) + sizeof(T3);
			mData = new char(mSize);
			*((T1*)mData) = t1;
			*((T2*)(mData + sizeof(T1))) = t2;
			*((T3*)(mData + sizeof(T1) + sizeof(T2))) = t3;
		}


		template <typename T1>
		void TemplateAccess(T1 &t1)
		{
			t1 = *((T1*)mData);
		}

		template <typename T1, typename T2>
		void TemplateAccess(T1 &t1, T2 &t2)
		{
			t1 = *((T1*)mData);
			t2 = *((T2*)(mData + sizeof(T1)));
		}

		template <typename T1, typename T2, typename T3>
		void TemplateAccess(T1 &t1, T2 &t2, T3 &t3)
		{
			t1 = *((T1*)mData);
			t2 = *((T2*)(mData + sizeof(T1)));
			t3 = *((T3*)(mData + sizeof(T1) + sizeof(T2)));
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