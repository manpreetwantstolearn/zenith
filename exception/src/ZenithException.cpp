#include "exception/ZenithException.hpp"

namespace exception {

ZenithException::ZenithException(const std::string& message)
    : std::runtime_error(message) {}

} // namespace exception
