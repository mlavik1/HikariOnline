#ifndef HIKARI_MESHCOMPONENT_H
#define HIKARI_MESHCOMPONENT_H

#include "component.h"
#include "OGRE/Ogre.h"
#include <vector>
#include <unordered_map>
#include "Core/Animation/animation_instance.h"

namespace Hikari
{
	class MeshComponent : public Hikari::Component
	{
		DEFINE_CLASS(Hikari::MeshComponent, Hikari::Component)

	private:
		std::unordered_map<std::string, AnimationInstance*> mAnimationInstances;
		std::vector<AnimationInstance*> mFadeOutAnims;
		AnimationInstance* mActiveAnim;

	public:
		virtual void InitialiseObject(ObjectInitialiserParams arg_params) override;

		virtual void Initialise() override;

		virtual void Tick(float arg_deltatime) override;

		AnimationInstance* GetActiveAnimation();
		void SetActiveAnimation(const char* arg_name);

	};
}

#endif
