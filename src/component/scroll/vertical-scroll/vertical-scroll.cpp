#include "vertical-scroll.h"

Kit::VerticalScroll::VerticalScroll(SDL_Renderer* renderer, Rect size, int maxValue, double relSizes)
	: Scroll(renderer, size, maxValue, relSizes) {}

void Kit::VerticalScroll::init()
{
	this->_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _bodySize.w(), _bodySize.h());
	SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);


	_sliderSize = Rect({ 3, 0 }, { _bodySize.w() - 6, (int)(_bodySize.h() * _relSizes) });
}

void Kit::VerticalScroll::shift(int delta)
{
	_nowValue += delta;

	if (_nowValue > _maxValue)
		_nowValue = _maxValue;
	if (_nowValue < 0)
		_nowValue = 0;

	_position = _nowValue / (double)_maxValue;

	_sliderSize.y((_bodySize.h() - _sliderSize.h()) * _position);
}