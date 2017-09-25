#include "game_object.h"

#include "Core/Managers/input_manager.h"
#include "Core/Managers/tick_manager.h"
#include "Core/World/world.h"

IMPLEMENT_CLASS(Hikari::GameObject)

namespace Hikari
{
	GameObject::GameObject()
	{
	}

	GameObject* GameObject::CreateGameObject(Class* arg_class)
	{
		__Assert(arg_class->IsA(GameObject::GetStaticClass()));

		GameObject* gameObject = static_cast<GameObject*>(arg_class->CreateInstance());
		gameObject->InitialiseObject(ObjectInitialiserParams()); // todo
		return gameObject;
	}


	void GameObject::Initialise()
	{

	}

	void GameObject::OnStart()
	{

	}

	void GameObject::OnStop()
	{

	}

}
