#ifndef HIKARI_ANIMATIONINSTANCE_H
#define HIKARI_ANIMATIONINSTANCE_H

#include "OGRE/Ogre.h"

namespace Hikari
{
	class AnimationInstance
	{
	private:
		Ogre::AnimationState* mAnimationState;
		float mPlayRate;
		float mBlendWeight;
		bool mLoopEnabled;

	public:
		AnimationInstance(Ogre::AnimationState* arg_animstate);
		void TickAnimation(float arg_deltatime);

		void SetWeight(float arg_weight);
		void BeginFadeOut();
		void BeginPlay();
		void StopPlay();
		void EnableLooping(bool arg_loop);

		float GetWeight() const;
		bool GetLoopEnabled() const;
	};
}

#endif
