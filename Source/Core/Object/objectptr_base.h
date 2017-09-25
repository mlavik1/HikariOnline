#ifndef HIKARI_OBJECTPTRBASE_H
#define HIKARI_OBJECTPTRBASE_H

/*=============================================================================================
Base class for object pointers.

==============================================================================================*/
#include "objectrefhandle.h"

namespace Hikari
{
	class Object;

	template <class T>
	class ObjectPtrBase
	{
	protected:
		ObjectRefHandle* mRefHandle;

	public:
		inline Object* GetObjectSafe() const { return (mRefHandle != nullptr ? mRefHandle->GetObjectPointer() : nullptr); }

	public:
		T* Get() const;
		T* operator->() const;
		bool operator==(const ObjectPtrBase<T>& arg_other) const;
		bool operator!=(const ObjectPtrBase<T>& arg_other) const;
		bool operator==(const T* arg_other) const;
		bool operator!=(const T* arg_other) const;

		virtual bool IsValid() const;

	};
}

#include "objectptr_base.cpp"

#endif
