#ifndef HIKARI_ACTOR_H
#define HIKARI_ACTOR_H

#include "Core/Object/game_object.h"
#include "OGRE/Ogre.h"
#include "Core/Debug/st_assert.h"
#include <vector>

namespace Hikari
{
	class World;
	class Component;

	class Actor : public GameObject
	{
		DEFINE_CLASS(Hikari::Actor, Hikari::GameObject)

	protected:
		Ogre::SceneNode* mSceneNode;
		std::vector<Component*> mComponents;

	public:
		Actor(Hikari::World* arg_world);

		const Ogre::Vector3& GetPosition() const;
		const Ogre::Vector3& GetScale() const;

		void SetPosition(const Ogre::Vector3& arg_position);
		void SetScale(const Ogre::Vector3& arg_scale);

		inline Ogre::SceneNode* GetSceneNode()
		{
			return mSceneNode;
		}

		template <typename T>
		T *AddComponent()
		{
			__AssertComment((std::is_base_of<Component, T>::value), "Must be subclass of Component");
			
			T* newComp = static_cast<T*>(GameObject::CreateGameObject<T>(this->mWorld));
			newComp->mWorld = this->mWorld;
			newComp->mParent = this;
			mComponents.push_back(newComp);
			return newComp;
		}

		virtual void Initialise() override;
		virtual void OnStart() override;
		virtual void OnStop() override;
	};
}
#endif
