#ifndef HIKARI_OBJECT_H
#define HIKARI_OBJECT_H

/*=============================================================================================
Base class for most classes in the Engine.
Making a class inherit from Hikari::Object will:
- Enable additional runtime type information + some basic "reflection" functionality.
- Allow you to use Hikari::ObjectPtr<T> on instances of the class

==============================================================================================*/
#include "Core/Object/objdefs.h"
#include "Core/Object/objectrefhandle.h"
#include "string"

namespace Hikari
{
	class Object
	{
		DEFINE_CLASS_INTERNAL(Hikari::Object, , 0)

	private:
		ObjectFlagRegister mObjectFlags;
		ObjectRefHandle* mObjectRefHandle;
	
	protected:
		std::string mObjectName;

	public:
		Object();
		~Object();

		virtual void InitialiseObject(ObjectInitialiserParams arg_params);

		void Destroy();

		virtual void OnDestroy() {}; // TODO: call this on all objects marked for pending destroy
		
		inline ObjectRefHandle*  GetRefHandle() { return mObjectRefHandle; }

		std::string GetMemoryHash() const;

	};
}

#endif
