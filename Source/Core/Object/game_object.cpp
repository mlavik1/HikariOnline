#include "game_object.h"

IMPLEMENT_CLASS(Hikari::GameObject)

namespace Hikari
{
	GameObject::GameObject()
	{

	}

	GameObject* GameObject::CreateGameObject(Class* arg_class, World* arg_world)
	{
		__Assert(arg_class->IsA(GameObject::GetStaticClass()));
		__Assert(arg_world);

		GameObject* gameObject = static_cast<GameObject*>(arg_class->CreateInstance());
		gameObject->InitialiseObject(ObjectInitialiserParams()); // todo
		gameObject->mWorld = arg_world;
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
