#include "animation_instance.h"

#include "Core/Debug/st_assert.h"

namespace Hikari
{
	AnimationInstance::AnimationInstance(Ogre::AnimationState* arg_animstate)
	{
		__Assert(arg_animstate != nullptr);
		mPlayRate = 1.0f;
		mBlendWeight = 0.0f;
		mAnimationState = arg_animstate;
		mLoopEnabled = true; // TEMP !!! TODO: animation controller decides
	}

	void AnimationInstance::TickAnimation(float arg_deltatime)
	{
		mAnimationState->addTime(arg_deltatime * mPlayRate);
	}

	void AnimationInstance::SetWeight(float arg_weight)
	{
		mBlendWeight = arg_weight;
		mAnimationState->setWeight(mBlendWeight);
		if(mBlendWeight > 0.0f && !mAnimationState->getEnabled())
		{
			mAnimationState->setEnabled(true);
		}
		else if (mBlendWeight <= 0.0f && mAnimationState->getEnabled())
		{
			mAnimationState->setEnabled(false);
		}
	}

	void AnimationInstance::BeginFadeOut()
	{
		mAnimationState->setLoop(false);
	}

	void AnimationInstance::BeginPlay()
	{
		mAnimationState->setLoop(mLoopEnabled);
	}

	void AnimationInstance::StopPlay()
	{
		mAnimationState->setEnabled(false);
	}

	void AnimationInstance::EnableLooping(bool arg_loop)
	{
		mLoopEnabled = arg_loop;
		if (mAnimationState)
		{
			mAnimationState->setLoop(arg_loop);
		}
	}


	float AnimationInstance::GetWeight() const
	{
		return mBlendWeight;

	}
	bool AnimationInstance::GetLoopEnabled() const
	{
		return mLoopEnabled;
	}
}
