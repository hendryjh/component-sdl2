#pragma once

#include "../kit/component/component.h"

using namespace Lib;

class Button : public Component
{
private:
	string text;

public:
	Button(string id, Rect size, string classes, string text);
	

public:
	void setup();
};