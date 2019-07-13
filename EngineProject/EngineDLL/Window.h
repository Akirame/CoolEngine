#pragma once
#include <iostream>
#include "Exports.h"



using namespace std;

class ENGINEDLL_API Window
{
private:
	void* window;
protected:
	int height;
	int width;
	const char* name;
public:
	Window(int _height, int _witdh,string &(_name));
	~Window();
	bool Start();
	bool Stop();
	const void* GetWindowPtr() { return window;};
	bool ShouldClose();
	void PollEvents();
};

