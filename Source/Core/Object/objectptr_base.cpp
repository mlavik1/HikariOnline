#ifndef HIKARI_OBJECTPTRBASE_CPP
#define HIKARI_OBJECTPTRBASE_CPP

#include "objectptr_base.h"
#include "object.h"
#include <type_traits>

namespace Hikari
{
	template<typename T>
	T* ObjectPtrBase<T>::Get() const
	{
		return static_cast<T*>(mRefHandle->GetObjectPointer());
	}

	template<typename T>
	T* ObjectPtrBase<T>::operator->() const
	{
		return static_cast<T*>(GetObjectSafe());
	}

	template<typename T>
	bool ObjectPtrBase<T>::operator==(const ObjectPtrBase<T>& arg_other) const
	{
		return GetObjectSafe() == arg_other.GetObjectSafe();
	}

	template<typename T>
	bool ObjectPtrBase<T>::operator!=(const ObjectPtrBase<T>& arg_other) const
	{
		return GetObjectSafe() != arg_other.GetObjectSafe();
	}

	template<typename T>
	bool ObjectPtrBase<T>::operator==(const T* arg_other) const
	{
		return GetObjectSafe() == arg_other;
	}

	template<typename T>
	bool ObjectPtrBase<T>::operator!=(const T* arg_other) const
	{
		return GetObjectSafe() != arg_other;
	}

	template<typename T>
	bool ObjectPtrBase<T>::IsValid() const
	{
		return GetObjectSafe() != nullptr;
	}

}

#endif
