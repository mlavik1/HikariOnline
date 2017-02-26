#ifndef HIKARI_OBJECTPTR_CPP
#define HIKARI_OBJECTPTR_CPP

#include "objectptr.h"
#include "Core/Debug/st_assert.h"
#include "Core/Object/object.h"
#include <type_traits>

namespace Hikari
{
	template<typename T>
	ObjectPtr<T>::ObjectPtr()
		: mRefHandle(nullptr)
	{
		__AssertComment((std::is_base_of<Object, T>::value), "Type of T must be Object or subclass of Object.");
	}

	template<typename T>
	ObjectPtr<T>::ObjectPtr(Object* arg_object)
	{
		__AssertComment((std::is_base_of<Object, T>::value), "Type of T must be Object or subclass of Object.");

		mRefHandle = arg_object->GetRefHandle();
		mRefHandle->AddRef();
	}

	template<typename T>
	ObjectPtr<T>::~ObjectPtr()
	{
		if (mRefHandle != nullptr)
		{
			mRefHandle->RemoveRef();
		}
	}

	template<typename T>
	T* ObjectPtr<T>::Get()
	{
		return static_cast<T*>(mRefHandle->GetObject());
	}

	template<typename T>
	T* ObjectPtr<T>::operator->() const
	{
		return static_cast<T*>(getObjectSafe());
	}

	template<typename T>
	bool ObjectPtr<T>::operator==(const ObjectPtr<T>& arg_other) const
	{
		return getObjectSafe() == arg_other.getObjectSafe();
	}

	template<typename T>
	bool ObjectPtr<T>::operator!=(const ObjectPtr<T>& arg_other) const
	{
		return getObjectSafe() != arg_other.getObjectSafe();
	}

	template<typename T>
	bool ObjectPtr<T>::operator==(const T* arg_other) const
	{
		return getObjectSafe() == arg_other;
	}

	template<typename T>
	bool ObjectPtr<T>::operator!=(const T* arg_other) const
	{
		return getObjectSafe() != arg_other;
	}

	template<typename T>
	bool ObjectPtr<T>::IsValid() const
	{
		return getObjectSafe() != nullptr;
	}

}

#endif
