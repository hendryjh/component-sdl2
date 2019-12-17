#pragma once

#include "SDL.h"
#include "../../tools/rect/extended-rect/extended-rect.h"
#include "../../tools/point/extended-point/extended-point.h"

namespace Kit
{

class Component;

class Scroll
{
private:
	Rect _bodySize;
	Rect _sliderSize;

	SDL_Renderer* _renderer;
	SDL_Texture* _texture;

	SDL_Texture* _parentTexture;

	bool _display;


	int _maxValue;
	int _nowValue;

	double _relSizes;

	/* { 0, 1 } */
	double _position;

public:
	Scroll(SDL_Renderer* renderer, Rect size, int maxValue, double relSizes);
	~Scroll();

public:
	friend Component;

private:
	void init();


public:
	void shift(int d);

	bool onHover(Point p);
	bool onHoverSlider(Point& p);

public:
	void render();

};

}