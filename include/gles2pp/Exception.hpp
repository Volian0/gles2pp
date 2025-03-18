#pragma once

#include <stdexcept>
#include <string>

namespace gles2pp
{

class Exception : public std::runtime_error
{
public:
    Exception(const std::string& t_explanation);
};

}