#ifndef HIKARI_OBJECTPTR_H
#define HIKARI_OBJECTPTR_H

/*=============================================================================================
Reference-counted pointer to a Hikari::Object.
When the object is destroyed (in any way), this will return nullptr.

==============================================================================================*/
#include "objectrefhandle.h"
#include "objectptr_base.h"

namespace Hikari
{
	template <class T>
	class ObjectPtr : public ObjectPtrBase<T>
	{
	public:
		ObjectPtr();
		ObjectPtr(Object* arg_object);
		ObjectPtr(const ObjectPtr<T>& arg_other);
		~ObjectPtr();

		ObjectPtr<T>& operator=(const ObjectPtr<T>& arg_other);

		T* Get() const;
		T* operator->() const;
		bool operator==(const ObjectPtrBase<T>& arg_other) const;
		bool operator!=(const ObjectPtrBase<T>& arg_other) const;
		bool operator==(const T* arg_other) const;
		bool operator!=(const T* arg_other) const;

		virtual bool IsValid() const;

	};
}

#include "objectptr.cpp"

#endif
