#ifndef HIKARI_GAMEOBJECT_H
#define HIKARI_GAMEOBJECT_H

#include "Core/Object/object.h"
#include "Core/Debug/st_assert.h"

namespace Hikari
{
	class World;
	class TickManager;
	class InputManager;

	class GameObject : public Hikari::Object
	{
		DEFINE_CLASS(Hikari::GameObject, Hikari::Object)

	protected:
		World* mWorld;

	public:
		GameObject();

		static GameObject* CreateGameObject(Class* arg_class, World* arg_world);

		template<typename T>
		static T* CreateGameObject(World* arg_world)
		{
			__AssertComment((std::is_base_of<GameObject, T>::value), "Must be subclass of GameObject");
			return static_cast<T*>(CreateGameObject(T::GetStaticClass(), arg_world));
		}

		virtual void Initialise();
		//virtual void Tick() = 0;
		virtual void OnStart();
		virtual void OnStop();


		TickManager* GetTickManager();
		InputManager* GetInputManager();

	};
}

#endif
