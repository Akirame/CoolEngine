#pragma once
#include "Animation.h"
#include <list>
class ENGINEDLL_API AnimationPlayer
{
public:
	AnimationPlayer();
	~AnimationPlayer();
	void Play(const char * animationName, float deltaTime);
	void AddAnimation(Animation* anim);
private:
	list<Animation*> animationList;
	Animation *currentAnimation;
};

