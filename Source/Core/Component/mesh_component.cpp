#include "mesh_component.h"

#include "Core/World/world.h"
#include "Core/Actor/actor.h"

IMPLEMENT_CLASS(Hikari::MeshComponent)

namespace Hikari
{
	void MeshComponent::InitialiseObject(ObjectInitialiserParams arg_params)
	{
		Hikari::Component::InitialiseObject(arg_params);

		mActiveAnim = nullptr;
	}

	void MeshComponent::Initialise()
	{
		Component::Initialise();
		
	}

	void MeshComponent::Tick(float arg_deltatime)
	{
		if (mActiveAnim != nullptr)
		{
			float activeAnimWeight = mActiveAnim->GetWeight();
			if (mActiveAnim->GetWeight() < 1.0f)
			{
				float remainingWeightIncrement = 1.0f - activeAnimWeight;
				float weightIncrement = std::min(arg_deltatime, remainingWeightIncrement);

				mActiveAnim->SetWeight(activeAnimWeight + weightIncrement);

				float remainingWeight = weightIncrement;
				bool bContinueIteration = mFadeOutAnims.size() > 0;
				while (bContinueIteration)
				{
					bContinueIteration = false;
					float weightThisIteration = remainingWeight;
					float weightPerInstance = weightThisIteration / mFadeOutAnims.size();
					
					int i = 0;
					while (i < mFadeOutAnims.size())
					{
						__Assert(remainingWeight >= 0.0f);
						AnimationInstance* animInstance = mFadeOutAnims[i];
						float instanceWeight = animInstance->GetWeight();
						animInstance->SetWeight(instanceWeight - weightPerInstance);
						remainingWeight -= weightPerInstance;

						if (animInstance->GetWeight() <= 0.01f)
						{
							animInstance->StopPlay();
							mFadeOutAnims.erase(mFadeOutAnims.begin() + i);
							if(animInstance->GetWeight() < 0.0f)
								remainingWeight -= animInstance->GetWeight();
							bContinueIteration = true; // start over again after iteration is done
						}
						else
						{
							i++;
						}
					}
				}
			}
			mActiveAnim->TickAnimation(arg_deltatime);
			for (AnimationInstance* animInstance : mFadeOutAnims)
			{
				animInstance->TickAnimation(arg_deltatime);
			}
		}
	}

	Ogre::Entity* MeshComponent::GetOgreEntity()
	{
		return mOgreEntity;
	}

	AnimationInstance* MeshComponent::GetActiveAnimation()
	{
		return mActiveAnim;
	}

	void MeshComponent::SetActiveAnimation(const char* arg_name)
	{
		__Assert(mAnimationInstances.find(arg_name) != mAnimationInstances.end()); // TODO: remove
		AnimationInstance* animInstance = mAnimationInstances[arg_name];
		if (animInstance != mActiveAnim)
		{
			if (mActiveAnim != nullptr)
			{
				mFadeOutAnims.push_back(mActiveAnim);
				mActiveAnim->BeginFadeOut();
			}
			mActiveAnim = animInstance;
			mActiveAnim->SetWeight(0.0f);
			mActiveAnim->BeginPlay();
		}
	}

	void MeshComponent::SetMesh(const char* arg_mesh)
	{
		// THIS IS TEMP

		mOgreEntity = mWorld->GetSceneManager()->createEntity(arg_mesh);
		mParent->GetSceneNode()->attachObject(mOgreEntity);

		if (mOgreEntity->getAllAnimationStates() != 0)
		{
			for (std::pair<Ogre::String, Ogre::AnimationState*> pair : mOgreEntity->getAllAnimationStates()->getAnimationStateIterator())
			{
				std::string animName = pair.first.c_str();
				std::transform(animName.begin(), animName.end(), animName.begin(), ::tolower);
				AnimationInstance* animInstance = new AnimationInstance(pair.second, pair.first);
				mAnimationInstances.emplace(animName, animInstance);
			}
		}
		
	}
	
}
