#ifndef HIKARI_WEAKOBJECTPTR_H
#define HIKARI_WEAKOBJECTPTR_H

/*=============================================================================================
Weak pointer to a Hikari::Object.
When the object is destroyed (in any way), this will return nullptr.

==============================================================================================*/
#include "objectrefhandle.h"
#include "objectptr_base.h"

namespace Hikari
{
	template <class T>
	class WeakObjectPtr : public ObjectPtrBase<T>
	{
	public:
		WeakObjectPtr();
		WeakObjectPtr(Object* arg_object);
		WeakObjectPtr(const WeakObjectPtr<T>& arg_other);
		WeakObjectPtr(const ObjectPtrBase<T>& arg_other);
		~WeakObjectPtr();

		WeakObjectPtr<T>& operator=(const WeakObjectPtr<T>& arg_other);

		T* Get() const;
		T* operator->() const;
		bool operator==(const ObjectPtrBase<T>& arg_other) const;
		bool operator!=(const ObjectPtrBase<T>& arg_other) const;
		bool operator==(const T* arg_other) const;
		bool operator!=(const T* arg_other) const;

		virtual bool IsValid() const;

	};
}

#include "weak_objectptr.cpp"

#endif
