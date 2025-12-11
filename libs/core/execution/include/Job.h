#pragma once

#include <obs/Context.h>

#include <any>
#include <cstdint>

namespace zenith::execution {

enum class JobType { TASK };

struct Job {
  JobType type;
  uint64_t session_id;
  std::any payload;
  obs::Context trace_ctx;
};

} // namespace zenith::execution
