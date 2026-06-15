cmake_minimum_required(VERSION 3.14)

project(todoTerm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG         v7.0.0
)

FetchContent_MakeAvailable(ftxui)

add_executable(todoTerm src/main.cpp src/io.cpp src/ui-comp.cpp)

target_include_directories(todoTerm PRIVATE include)

target_link_libraries(todoTerm PUBLIC
  ftxui::screen
  ftxui::dom
  ftxui::component
)
