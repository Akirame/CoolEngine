#pragma once
#include <iostream>
#include "Exports.h"
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f


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
	const void* GetWindowPrt() { return window;};
	bool ShouldClose();
	void PollEvents();
};

