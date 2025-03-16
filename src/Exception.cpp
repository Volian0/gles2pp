#include "gles2pp/Exception.hpp"

namespace gles2pp
{

Exception::Exception(std::string_view t_explanation) : std::runtime_error{t_explanation.data()}
{
}

}