#pragma once

#include <functional>

namespace zenith::execution {

class IExecutor {
public:
  virtual ~IExecutor() = default;
  virtual void submit(std::function<void()> task) = 0;
};

} // namespace zenith::execution
