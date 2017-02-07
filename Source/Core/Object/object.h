#ifndef MING3D_OBJECT_H
#define MING3D_OBJECT_H

/*=============================================================================================
Base class for most classes in the Engine.
Making a class inherit from Hikari::Object will:
- Enable additional runtime type information + some basic "reflection" functionality.
- Allow you to use Hikari::ObjectPtr<T> on instances of the class

==============================================================================================*/
#include "Core/Object/objdefs.h"
#include "Core/Object/objectrefhandle.h"

namespace Hikari
{
	class Object
	{
		DEFINE_CLASS_INTERNAL(Hikari::Object, , 0)

	private:
		ObjectFlagRegister mObjectFlags;
		ObjectRefHandle* mObjectRefHandle;

	public:
		Object();
		~Object();

		void Destroy();

		virtual void OnDestroy() {}; // TODO: call this on all objects marked for pending destroy
		
		inline ObjectRefHandle*  GetRefHandle() { return mObjectRefHandle; }

	};
}

#endif
