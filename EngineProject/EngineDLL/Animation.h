#pragma once
#include "Exports.h"
#include "Sprite.h"
class ENGINEDLL_API Animation
{
public:
	Animation(Sprite* _sprite);
	~Animation();
	void CreateAnimation(const char* name, float start, float end, bool loop);
	void RunAnimation();
	void Stop();
	void OnUpdate(float deltaTime);
	const char* GetName();
private:
	const char* name;
	float from;
	float to;
	float currentKey;
	float speed;
	float timer;
	bool loop;
	Sprite* sprite;
};