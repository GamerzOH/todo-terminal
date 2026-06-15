#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "app-state.hpp"

using namespace ftxui;

namespace ui{
    class Display {
        public:
            Display();
            void Serve();
    };
}
