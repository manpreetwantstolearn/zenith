#pragma once

// Main observability API - Provider pattern
#include "Context.h"
#include "Log.h"
#include "Metrics.h"
#include "MetricsRegistry.h"
#include "Provider.h"
#include "Span.h"
#include "Tracer.h"

namespace zenith::observability {

// Convenience initialization functions
// Usage (C++17):
//   ::observability::Config config;
//   config.set_service_name("my_service");
//   config.set_otlp_endpoint("http://localhost:4317");
//   zenith::observability::init(config);
//
//   auto tracer = zenith::observability::Provider::instance().get_tracer("my_service");
//   auto span = tracer->start_span("operation");
//   span->attr("key", "value");
//   span->end();
//
//   zenith::observability::info("Log message");
//

} // namespace zenith::observability

// Backward compatibility alias - allows existing code using obs:: to continue working
namespace obs = zenith::observability;
