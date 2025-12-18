#pragma once

#include <stdexcept>
#include <string>

namespace zenith::resilience {

struct LoadShedderPolicy {
  size_t max_concurrent{0};
  std::string name{};

  static LoadShedderPolicy create(size_t max_concurrent, std::string name) {
    if (max_concurrent == 0) {
      throw std::invalid_argument("max_concurrent must be greater than 0");
    }
    return LoadShedderPolicy{max_concurrent, std::move(name)};
  }
};

} // namespace zenith::resilience
