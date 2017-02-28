#ifndef HIKARI_ANIMATIONINSTANCE_H
#define HIKARI_ANIMATIONINSTANCE_H

#include "OGRE/Ogre.h"
#include <string>

namespace Hikari
{
	class AnimationInstance
	{
	private:
		std::string mName;
		Ogre::AnimationState* mAnimationState;
		float mPlayRate;
		float mBlendWeight;
		bool mLoopEnabled;

	public:
		AnimationInstance(Ogre::AnimationState* arg_animstate, std::string arg_name);
		void TickAnimation(float arg_deltatime);

		void SetWeight(float arg_weight);
		void BeginFadeOut();
		void BeginPlay();
		void StopPlay();
		void EnableLooping(bool arg_loop);

		float GetWeight() const;
		bool GetLoopEnabled() const;

		std::string GetName() const;
	};
}

#endif
