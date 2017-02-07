#include "objectrefhandle.h"

namespace Hikari
{
	ObjectRefHandle::ObjectRefHandle(Object* arg_object)
		: mObject(arg_object), mRefCount(0)
	{
		maybeDelete();
	}

	void ObjectRefHandle::AddRef()
	{
		mRefCount++;
	}

	void ObjectRefHandle::RemoveRef()
	{
		mRefCount--;

		maybeDelete();
	}

	void ObjectRefHandle::maybeDelete()
	{
		if (mRefCount == 0 && mObject == nullptr)
		{
			delete(this);
		}
	}
}
