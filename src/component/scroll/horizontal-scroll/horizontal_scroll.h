#pragma once

#include "../scroll.h"

namespace Kit
{
    class horizontal_scroll : public scroll
    {
    public:
        explicit horizontal_scroll(Component* parent_);

    public:
        friend Component;

    public:
        void shift(int delta_) override;

        void setup(const SimpleRect& body_, const SimpleRect& slider_, int maxValue_, int nowValue_,
                   double aspectRatio_, double nowPosition_) override;
    };

}