cmake_minimum_required(VERSION 3.14)
project(component_sdl2_cmake)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME component_sdl2_cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)




include_directories(src)
include_directories(src/component)
include_directories(src/component/animation)
include_directories(src/component/components)
include_directories(src/component/navigator)
include_directories(src/component/scroll)
include_directories(src/component/scroll/horizontal-scroll)
include_directories(src/component/scroll/vertical-scroll)
include_directories(src/event)
include_directories(src/tools/color)
include_directories(src/tools/css)
include_directories(src/tools/css/color)
include_directories(src/tools/css/css_variant)
include_directories(src/tools/css/utils)
include_directories(src/tools/font)
include_directories(src/tools/font/font-find)
include_directories(src/tools/image)
include_directories(src/tools/point/extended-point)
include_directories(src/tools/point/simple-point)
include_directories(src/tools/rect/extended-rect)
include_directories(src/tools/rect/simple-rect)
include_directories(src/tools/size/extended-size)
include_directories(src/tools/size/simple-size)
include_directories(src/tools/text)
include_directories(src/tools/utils)
include_directories(src/window)
include_directories(src/std_components/button)
include_directories(src/std_components/checkbox)
include_directories(src/std_windows/simple_window)

add_executable(component_sdl2_cmake
        src/component/animation/animation.h
        src/component/animation/animation_variant.cpp
        src/component/animation/animation_variant.h
        src/component/components/components.cpp
        src/component/components/components.h
        src/component/navigator/navigator.cpp
        src/component/navigator/navigator.h
        src/component/scroll/horizontal-scroll/horizontal-scroll.cpp
        src/component/scroll/horizontal-scroll/horizontal-scroll.h
        src/component/scroll/vertical-scroll/vertical-scroll.cpp
        src/component/scroll/vertical-scroll/vertical-scroll.h
        src/component/scroll/scroll.cpp
        src/component/scroll/scroll.h
        src/component/component-header.h
        src/component/component.cpp
        src/component/component.h
        src/event/event.h
        src/tools/css/color/color.cpp
        src/tools/css/color/color.h
        src/tools/css/css_variant/css_variant.cpp
        src/tools/css/css_variant/css_variant.h
        src/tools/css/utils/css_utils.cpp
        src/tools/css/utils/utils.h
        src/tools/css/css-attributes.cpp
        src/tools/css/css-attributes.h
        src/tools/css/css.cpp
        src/tools/css/css.h
        src/tools/css/css_block.cpp
        src/tools/css/css_block.h
        src/tools/css/css_block_state.cpp
        src/tools/css/css_block_state.h
        src/tools/css/css_parse.cpp
        src/tools/css/css_parse.h
        src/tools/font/font-find/font-find.cpp
        src/tools/font/font-find/font-find.h
        src/tools/font/font.cpp
        src/tools/font/font.h
        src/tools/image/image.cpp
        src/tools/image/image.h
        src/tools/point/extended-point/extended-point.cpp
        src/tools/point/extended-point/extended-point.h
        src/tools/point/simple-point/simple-point.h
        src/tools/rect/extended-rect/extended-rect.cpp
        src/tools/rect/extended-rect/extended-rect.h
        src/tools/rect/simple-rect/simple-rect.h
        src/tools/size/extended-size/extended-size.cpp
        src/tools/size/extended-size/extended-size.h
        src/tools/size/simple-size/simple-size.cpp
        src/tools/size/simple-size/simple-size.h
        src/tools/text/text.cpp
        src/tools/text/text.h
        src/tools/text/text_line.cpp
        src/tools/text/text_line.h
        src/tools/utils/utils.cpp
        src/tools/utils/utils.h
        src/window/window.cpp
        src/window/window.h
        src/kit-enter-point.h
        src/kit-main.cpp
        src/kit-main.h
        src/kit.h
        src/std_components/button/button.h
        src/std_components/button/button.cpp
        src/std_components/checkbox/checkbox.h
        src/std_components/checkbox/checkbox.cpp
        src/std_windows/simple_window/simple-window.cpp
        src/std_windows/simple_window/simple-window.h
        main.cpp)



# Set up SDL2
set(SDL2_PATH "C:\\SDL2")
set(SDL2_IMAGE_PATH "C:\\SDL2\\SDL2_image-2.0.4")
set(SDL2_TTF_PATH "C:\\SDL2\\SDL2_ttf-2.0.15")
set(SDL2_GFX_PATH "C:\\SDL2\\SDL2_gfx")

# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_gfx REQUIRED)

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF SDL2::GFX)


