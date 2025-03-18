#include "gles2pp/Exception.hpp"

namespace gles2pp
{

Exception::Exception(const std::string& t_explanation) : std::runtime_error{t_explanation}
{
}

}