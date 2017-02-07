#ifndef HIKARI_OBJECTREFHANDLE_H
#define HIKARI_OBJECTREFHANDLE_H

/*=============================================================================================
A reference handle that contains:
- raw pointer to a Hikari::Object
- reference count

ObjectRefHandle should only belong to, and be instansiated by, a Hikari::Object.
When the Hikari::Object is destroyed, the object pointer of the handle will be sett to nullptr.
When the reference count is 0 and the object is destroyed, the ObjectRefHandle will be destroyed.

==============================================================================================*/
namespace Hikari
{
	class Object;

	class ObjectRefHandle
	{
	private:
		Object* mObject;
		unsigned int mRefCount;

		void maybeDelete();

	public:
		ObjectRefHandle(Object* arg_object);

		inline Object* GetObject() const { return mObject; };

		inline void SetObject(Object* arg_object) { mObject = arg_object; }
		void AddRef();
		void RemoveRef();
	};
}

#endif
