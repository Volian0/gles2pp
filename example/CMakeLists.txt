cmake_minimum_required(VERSION 3.31)

project(example)

add_subdirectory(.. [EXCLUDE_FROM_ALL])

find_package(SDL3 REQUIRED)

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=include;
    -checks=readability-*,portability-*,performance-*,modernize-*,cppcoreguidelines-*,bugprone-*,-performance-enum-size,-bugprone-suspicious-stringview-data-usage,-readability-inconsistent-declaration-parameter-name,-cppcoreguidelines-pro-type-reinterpret-cast,-performance-no-int-to-ptr,-readability-static-accessed-through-instance,-bugprone-easily-swappable-parameters,-cppcoreguidelines-pro-bounds-pointer-arithmetic;
    -warnings-as-errors=*;)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

file(COPY res/ DESTINATION res/)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} gles2pp::gles2pp SDL3::SDL3)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)