#pragma once

#include <stdexcept>
#include <string>

namespace exception {

class ZenithException : public std::runtime_error {
public:
    explicit ZenithException(const std::string& message);
    ~ZenithException() override = default;
};

} // namespace exception
