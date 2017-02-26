#ifndef HIKARI_OBJECTPTR_H
#define HIKARI_OBJECTPTR_H

/*=============================================================================================
Reference-counted pointer to a Hikari::Object.
When the object is destroyed (in any way), this will return nullptr.

==============================================================================================*/
#include "Core/Object/objectrefhandle.h"

namespace Hikari
{
	class Object;

	template <class T>
	class ObjectPtr
	{
	private:
		ObjectRefHandle* mRefHandle;

		inline Object* getObjectSafe() const { return (mRefHandle != nullptr ? mRefHandle->GetObject() : nullptr); }

	public:
		ObjectPtr();
		ObjectPtr(Object* arg_object);
		~ObjectPtr();

		T* Get();
		T* operator->() const;
		bool operator==(const ObjectPtr<T>& arg_other) const;
		bool operator!=(const ObjectPtr<T>& arg_other) const;
		bool operator==(const T* arg_other) const;
		bool operator!=(const T* arg_other) const;

		bool IsValid() const;

	};
}

#include "objectptr.cpp"

#endif
