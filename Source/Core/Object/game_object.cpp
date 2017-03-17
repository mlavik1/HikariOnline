#include "game_object.h"

#include "Core/Managers/input_manager.h"
#include "Core/Managers/tick_manager.h"
#include "Core/World/world.h"
#include "Core/Engine/game_instance.h"

IMPLEMENT_CLASS(Hikari::GameObject)

namespace Hikari
{
	GameObject::GameObject(GameInstance* arg_gameinstance)
	{
		mGameInstance = arg_gameinstance;
	}

	GameObject* GameObject::CreateGameObject(Class* arg_class, GameInstance* arg_gameinstance)
	{
		__Assert(arg_class->IsA(GameObject::GetStaticClass()));
		__Assert(arg_gameinstance);

		GameObject* gameObject = static_cast<GameObject*>(arg_class->CreateInstance());
		gameObject->InitialiseObject(ObjectInitialiserParams()); // todo
		gameObject->mGameInstance = arg_gameinstance;
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

	TickManager* GameObject::GetTickManager()
	{
		return mGameInstance->GetTickManager();
	}

	InputManager* GameObject::GetInputManager()
	{
		return mGameInstance->GetInputManager();
	}
}
