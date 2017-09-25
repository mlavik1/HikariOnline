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
		/** The owning object */
		Object* mObject;

		/** Strong references (used by ObjectPtr) */
		unsigned int mStrongRefCount;

		/** Weak references (used by WeakObjectPtr) */
		unsigned int mWeakRefCount;

		void maybeDelete();

	public:
		ObjectRefHandle(Object* arg_object);

		/** Gets the owning object of the handle */
		inline Object* GetObjectPointer() const { return mObject; };

		/** Sets the owning object of the handle. */
		void SetObject(Object* arg_object);

		/** Adds a strong reference to the object. */
		void AddStrongRef();

		/** Removes a strong reference to the object. This might result in object destruction. */
		void RemoveStrongRef();

		/** Adds a weak reference to the object. Used by WeakObjectPtr. */
		void AddWeakRef();

		/** Removes a weak reference to the object. Used by WeakObjectPtr. */
		void RemoveWeakRef();
	};
}

#endif
