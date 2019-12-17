#include "window.h"
#include "../kit-main.h"

void Kit::Window::handleStyles()
{
	for (auto& component : allComponents)
	{
		CSS::css* component_css = component.second->getComponentStyles();
		if (component_css == nullptr)
			continue;

		for (auto& css_block : component_css->getStyles())
		{
			allComponentsStyles[css_block.first] = css_block.second;
		}
	}


	for (auto& style : allComponentsStyles)
	{
		string className = style.first;

		for (auto& component : allComponents)
		{
			if (component.second->hasClass(className))
			{
				component.second->_cssBlock.mergeWith(style.second);
			}
		}

	}
}

Kit::Component* Kit::Window::addElement(Component* component)
{
	if (component == nullptr)
		return nullptr;

	string objectID = component->id();

	if (allComponents.find(objectID) != allComponents.end())
	{
		cout << "������� � id = " << objectID << " ��� ����������!" << endl;
		return nullptr;
	}
	else
	{
		allComponents.insert(make_pair(objectID, component));
	}

	return allComponents[objectID];
}

Kit::Component* Kit::Window::getElementById(string id) const
{
	Component* component = allComponents.at(id);
	if (component == nullptr)
	{
		cout << "������� � id = " << id << " �� ����������!" << endl;
		return nullptr;
	}
	else
	{
		return component;
	}
}

Kit::Components Kit::Window::getElementsByClassName(string className) const
{
	vector<Component*>* �omponentVector = new vector<Component*>;
	for (auto& �omponent : allComponents)
	{
		if (�omponent.second->hasClass(className))
		{
			�omponentVector->push_back(�omponent.second);
		}
	}

	return Components(�omponentVector);
}

CSS::css_block* Kit::Window::addStyle(string className, CSS::css_block style)
{
	allComponentsStyles.insert(make_pair(className, style));
	return &allComponentsStyles[className];
}

Kit::Window::Window(string title, SimpleRect size)
{
	this->title = title;
	this->_size = size;

	this->window = nullptr;
	this->renderer = nullptr;

	this->is_display = true;

	this->wasSetupStyle = false;
	this->wasSetupComponents = false;

	this->need_close = false;

	this->init();
}

Kit::Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	for (auto& element : allComponents)
	{
		delete element.second;
	}


}

void Kit::Window::init()
{
	this->window = SDL_CreateWindow(title.c_str(),
		_size.x == -1 ? SDL_WINDOWPOS_CENTERED : _size.x,
		_size.y == -1 ? SDL_WINDOWPOS_CENTERED : _size.y,
		_size.w, _size.h, SDL_WINDOW_BORDERLESS); //SDL_WINDOW_RESIZABLE

	if (window == nullptr)
	{
		cout << "Error of initialize new Window: " << SDL_GetError() << endl;
		return;
	}

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
		return;
	}

	preSetup();
}

void Kit::Window::preSetup()
{
	navigator = $$ = new Navigator(this);
	Window::addElement(navigator);
}

void Kit::Window::render()
{
	if (!wasSetupStyle)
	{
		Window::handleStyles();
		wasSetupStyle = true;
	}

	if (!wasSetupComponents)
	{
		navigator->setupComponents();
		wasSetupComponents = true;
	}

	SDL_SetRenderTarget(renderer, NULL);

	SDL_SetRenderDrawColor(renderer,  0x00, 0x00, 0x00, 0xff );
	SDL_RenderFillRect(renderer, NULL);

	SDL_SetRenderDrawColor(renderer,  0xff, 0xff, 0xff, 0x00 );
	SDL_RenderDrawRect(renderer, NULL);



	navigator->render();


	SDL_RenderPresent(renderer);
}

void Kit::Window::onEvent(Event* e)
{
	if (need_close)
	{
		Window* temp = parent->at(1);
		parent->count_deleted_windows++;
		parent->getWindows()->erase(parent->getWindows()->end() - 1);

		delete temp;

		Component::_hoverComponent = nullptr;
		return;
	}

	switch (e->type)
	{

	case SDL_MOUSEMOTION:
	{
		mouseMotion(e);
		break;
	}

	case SDL_MOUSEBUTTONDOWN:
	{
		mouseButtonDown(e);

		break;
	}

	case SDL_MOUSEBUTTONUP:
	{
		mouseButtonUp(e);

		if (need_close)
		{
			Window* temp = parent->at(1);
			parent->count_deleted_windows++;
			parent->getWindows()->erase(parent->getWindows()->end() - 1);

			delete temp;

			Component::_hoverComponent = nullptr;
			return;
		}
		break;
	}

	case SDL_MOUSEWHEEL:
	{
		mouseWheel(e);
		break;
	}

	case SDL_KEYDOWN:
	{
		keyDown(e);
		break;
	}

	case SDL_KEYUP:
	{
		keyUp(e);
		break;
	}

	/*case SDL_WINDOWEVENT:
	{
		switch (e->window.event) {
		case SDL_WINDOWEVENT_MINIMIZED:
		case SDL_WINDOWEVENT_MAXIMIZED:
		case SDL_WINDOWEVENT_RESTORED:
		case SDL_WINDOWEVENT_ENTER:
		case SDL_WINDOWEVENT_LEAVE:
		case SDL_WINDOWEVENT_SHOWN:
		{
			render();
			break;
		}
		}

		break;
	}*/

	break;

	default:
	{
		
		break;
	}
		
	}
}

void Kit::Window::show()
{
	render();

	is_display = true;

	SDL_ShowWindow(window);
}

void Kit::Window::hide()
{

	is_display = false;

	SDL_HideWindow(window);
}

bool Kit::Window::isShow()
{
	return is_display;
}

void Kit::Window::collapse()
{
	SDL_MinimizeWindow(window);
}

void Kit::Window::close()
{
	this->need_close = true;
}

void Kit::Window::include(string path)
{
	main_css.open(path);
	Window::allComponentsStyles = main_css.getStyles();
}

int Kit::Window::width() const
{
	return _size.w;
}

int Kit::Window::height() const
{
	return _size.h;
}

int Kit::Window::top() const
{
	return _size.y;
}

int Kit::Window::left() const
{
	return _size.x;
}

Kit::SimpleRect Kit::Window::size() const
{
	return _size;
}

SDL_Renderer* Kit::Window::getRenderer() const
{
	return renderer;
}

SDL_Window* Kit::Window::getWindow() const
{
	return window;
}

void Kit::Window::setDraggableArea(SimpleRect area_)
{
	SimpleRect* size = new SimpleRect;
	*size = area_;

	SDL_SetWindowHitTest(window, [](SDL_Window* win, const SDL_Point* area, void* callback_data) -> SDL_HitTestResult
	{
		SimpleRect rect = *(SimpleRect*)callback_data;

		SDL_Rect rec = { 0, 0, rect.w, rect.h };


		if (SDL_PointInRect(area, &rec))
			return SDL_HITTEST_DRAGGABLE;

		return SDL_HITTEST_NORMAL;
	}
	, size);

}

void Kit::Window::mouseButtonDown(SDL_Event* e)
{
	Component* hover = navigator->onComponentHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseButtonDown(e);
	}

	render();
}

void Kit::Window::mouseButtonUp(SDL_Event* e)
{
	Component* hover = navigator->onComponentHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseButtonUp(e);
	}

	render();
}

void Kit::Window::mouseMotion(SDL_Event* e)
{
	Component* hover = navigator->onComponentHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseMotion(e);
	}

	render();
}

void Kit::Window::mouseWheel(SDL_Event* e)
{
	const int scrollDirection = e->wheel.y;

	if (e->motion.x == -1 || e->motion.y == -1 || e->motion.x == 1 || e->motion.y == 1)
	{
		SDL_GetMouseState(&e->motion.x, &e->motion.y);
	}

	Component* hover = navigator->onComponentHover({ e->motion.x, e->motion.y });

	if (hover != nullptr)
	{
		hover->mouseScroll(e, scrollDirection);
	}

	render();
}

void Kit::Window::keyDown(SDL_Event* e)
{
}

void Kit::Window::keyUp(SDL_Event* e)
{
}
