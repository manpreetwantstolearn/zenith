#pragma once

#include "Message.h"

namespace zenith::execution {

class IExecutor {
public:
  virtual ~IExecutor() = default;

  virtual void submit(Message msg) = 0;
};

} // namespace zenith::execution
