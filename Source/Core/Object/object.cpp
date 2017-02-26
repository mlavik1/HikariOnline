#include "object.h"
#include <sstream>
#include "function.h"

IMPLEMENT_CLASS(Hikari::Object)

#define ADD_OBJECT_FLAG(flag) mObjectFlags |= (ObjectFlagRegister)(flag)
#define REMOVE_OBJECT_FLAG(flag) mObjectFlags &= ~(ObjectFlagRegister)(flag)

namespace Hikari
{
	Object::Object()
	{
		mObjectRefHandle = new ObjectRefHandle(this);
		
		std::stringstream ss;
		ss << GetClass()->GetName() << GetClass()->mCreatedInstanceCount;
		mObjectName = ss.str();

		GetClass()->mCreatedInstanceCount++;
	}

	Object::~Object()
	{
		mObjectRefHandle->SetObject(nullptr);
	}

	void Object::CallFunction(Function* arg_function, FunctionArgContainer args)
	{
		(this->*(arg_function->mFunctionPointer))(args);
	}

	void Object::Destroy()
	{
		ADD_OBJECT_FLAG(ObjectFlag::PendingDestroy);
	}

	void Object::InitialiseObject(ObjectInitialiserParams arg_params)
	{

	}

	std::string Object::GetMemoryHash() const
	{
		std::stringstream ss;
		ss << this;
		return ss.str();
	}
}