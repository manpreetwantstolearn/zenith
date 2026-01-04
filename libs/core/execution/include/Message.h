#pragma once

#include <any>
#include <cstdint>

#include <Context.h>

namespace zenith::execution {

struct Message {
  uint64_t affinity_key;
  zenith::observability::Context trace_ctx;
  std::any payload;
};

} // namespace zenith::execution
