#pragma once

#include <vector>

#include "../rect/simple-rect/simple-rect.h"
#include "../point/simple-point/simple-point.h"
#include "../point/extended-point/extended-point.h"
#include "../font/font.h"
#include "../css/color/color.h"

#include "text_align.h"
#include "text_line.h"

namespace Kit
{
    using std::vector;
    using std::string;

    using color = CSS::Color;

    class Component;

    class text
    {
    public: // Constructor & Destructor
        text(Component* parent_, const string& text_, SimplePoint start_,
             const class font& font_, size_t font_size_, const color& font_color_, const double& line_height_);
        ~text();


    public:
        void render();

        void withText(const string& text);
        void useFont(const class font& newFont);
        void fontSize(const size_t& newFontSize);
        void useColor(const color& newColor);
        void lineHeight(const double& lineHeight);
        void textHorizontalAlign(const string& align);
        void textVerticalAlign(const string& align);
        void focus(bool focus);

    private: // SDL Part
        SDL_Renderer* _renderer;
        SDL_Texture* _texture;


    private: // Parent Part
        Component* _parent;


    private:
        string _text;


    private:
        font _font;
        size_t _font_size;
        TTF_Font* _ttf;
        color _color;

        double _line_height;


    private:
        vector <text_line> _lines;

        bool _is_one_line_text;

    private: // Align Part
        text_horizontal_align _horizontal_align;
        text_vertical_align _vertical_align;


    private:
        SimpleRect _size;
        SimpleRect _text_size;


    private:
        bool _need_update;


    private:
        int marginTop;
        int marginBottom;
        int marginLeft;
        int marginRight;

    private: // Cursor
        cursor_position _cursor_position;

        bool _is_select;
        bool _is_mouse_pushed;

        cursor_position _start_select;
        cursor_position _end_select;

        bool _is_focused;

    private:
        void setup();

        void splitByLines();
        void setupSize();

        void update();
        void renderCursor();

        cursor_position whereIsCursor(const SimplePoint& p);

        void dropSelection();
        void handleSelection();
        string copySelection();
        void deleteSelection();

        void mouseButtonDown(SDL_Event* e_, const Point& mouse);
        void mouseButtonUp(SDL_Event* e_, const Point& mouse);
        void mouseMotion(SDL_Event* e_, const Point& mouse);
        void textInput(SDL_Event* e_);
        void keyDown(SDL_Event* e_);

        void textMargin(const string& side, int value);

    private:
        friend text_line;
        friend Component;
    };




}