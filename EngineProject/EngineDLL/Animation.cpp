#include "Animation.h"


Animation::Animation(Sprite* _sprite) :
	sprite(_sprite)
{
	speed = 1.0f/8.0f;
	timer = 0;
}


void Animation::CreateAnimation(const char * _name, float start, float end, bool _loop)
{
	name = _name;
	from = start;
	to = end;
	currentKey = start;
	loop = _loop;
	if (sprite)
		sprite->SetFrame(currentKey);
}

void Animation::RunAnimation()
{
	if (sprite)
	{
		if (currentKey <= to)
		{
			sprite->SetFrame(currentKey);
			currentKey++;
		}
		else
		{
			if (loop)
				currentKey = from;
		}
	}
}

void Animation::Stop()
{
	currentKey = from;
}

void Animation::OnUpdate(float deltaTime)
{

	if (timer >= speed)
	{		
		RunAnimation();
		timer = 0;
	}
	else
	{
		timer += deltaTime;
	}
}

const char * Animation::GetName()
{
	return name;
}
