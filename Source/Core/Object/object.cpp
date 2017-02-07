#include "object.h"

IMPLEMENT_CLASS(Hikari::Object)

#define ADD_OBJECT_FLAG(flag) mObjectFlags |= (ObjectFlagRegister)(flag)
#define REMOVE_OBJECT_FLAG(flag) mObjectFlags &= ~(ObjectFlagRegister)(flag)

namespace Hikari
{
	Object::Object()
	{
		mObjectRefHandle = new ObjectRefHandle(this);
	}

	Object::~Object()
	{
		mObjectRefHandle->SetObject(nullptr);
	}

	void Object::Destroy()
	{
		ADD_OBJECT_FLAG(ObjectFlag::PendingDestroy);
	}
}