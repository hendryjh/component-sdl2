#include "navigator.h"
#include "../../window/window.h"

Lib::Navigator::Navigator(Window* parent)
	: Component("#navigator", { 1, 1, parent->width() - 2, parent->height() - 2 }, ".navigator")
{
	this->_window = parent;
	this->_renderer = parent->getRenderer();
}

void Lib::Navigator::update()
{
	if (_window != nullptr)
	{
		_window->render();
	}
}
