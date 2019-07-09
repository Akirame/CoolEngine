#include "AnimationPlayer.h"



AnimationPlayer::AnimationPlayer()
{
}


AnimationPlayer::~AnimationPlayer()
{
}

void AnimationPlayer::Play(const char * animationName, float deltaTime)
{
	if (currentAnimation)
	{
		if (currentAnimation->GetName() == animationName)
		{
			currentAnimation->OnUpdate(deltaTime);
		}
		else
		{
			currentAnimation->Stop();
			list<Animation*>::iterator it;
			for (it = animationList.begin(); it != animationList.end(); it++)
			{
				if ((*it)->GetName() == animationName)
				{
					currentAnimation = *it;
				}
			}
		}
	}
	else
	{
		list<Animation*>::iterator it;
		for (it = animationList.begin(); it != animationList.end(); it++)
		{
			if ((*it)->GetName() == animationName)
			{
				currentAnimation = *it;
			}
		}
	}
}

void AnimationPlayer::AddAnimation(Animation * anim)
{
	animationList.push_front(anim);
}
