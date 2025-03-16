#pragma once

#include <stdexcept>
#include <string_view>

namespace gles2pp
{

class Exception : public std::runtime_error
{
public:
    Exception(std::string_view t_explanation);
};

}