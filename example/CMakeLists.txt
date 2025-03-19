cmake_minimum_required(VERSION 3.31)

project(example)

add_subdirectory(.. [EXCLUDE_FROM_ALL])

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
    GIT_TAG         main
)

FetchContent_MakeAvailable(SDL3) 

set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    -header-filter=include;
    -checks=readability-*,portability-*,performance-*,modernize-*,cppcoreguidelines-*,bugprone-*,-performance-enum-size,-bugprone-suspicious-stringview-data-usage,-readability-inconsistent-declaration-parameter-name,-cppcoreguidelines-pro-type-reinterpret-cast,-performance-no-int-to-ptr,-readability-static-accessed-through-instance,-bugprone-easily-swappable-parameters,-cppcoreguidelines-pro-bounds-pointer-arithmetic;
    -warnings-as-errors=*;)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

file(COPY res/ DESTINATION res/)

if(EMSCRIPTEN)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sUSE_SDL=3 -s USE_WEBGL2=1 -s FULL_ES2=1 -s MAX_WEBGL_VERSION=2 --preload-file res") 
endif()
 
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} gles2pp::gles2pp SDL3::SDL3)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)