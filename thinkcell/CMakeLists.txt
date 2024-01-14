cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
# add_library(Catch2::Catch IMPORTED INTERFACE)
# set_property(Catch2::Catch PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIR}")

project(TestProject VERSION 0.1.0 LANGUAGES CXX)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

include(CTest)
enable_testing()

add_executable(TestProject main.cpp)
target_link_libraries(TestProject PRIVATE Catch2::Catch2WithMain)
