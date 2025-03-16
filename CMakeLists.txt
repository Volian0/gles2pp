cmake_minimum_required(VERSION 3.31)

project(gles2pp)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=include;
    -checks=readability-*,portability-*,performance-*,modernize-*,cppcoreguidelines-*,bugprone-*,-performance-enum-size,-bugprone-suspicious-stringview-data-usage,-readability-inconsistent-declaration-parameter-name,-cppcoreguidelines-pro-type-reinterpret-cast,-performance-no-int-to-ptr,-;
    -warnings-as-errors=*;)

add_library(gles2pp STATIC ${SRC_FILES})
add_library(gles2pp::gles2pp ALIAS gles2pp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20) 