#pragma once
#include <iostream>
#include "Exports.h"
using namespace std;

class ENGINEDLL_API Window
{
protected:
	int height;
	int width;
	const char* name;
public:
	Window(int _height, int _witdh,string &(_name));
	~Window();
	bool Start() const;
	bool Stop() const;
};

