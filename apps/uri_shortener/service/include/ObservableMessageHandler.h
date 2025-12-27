#pragma once

#include <memory>

#include <IMessageHandler.h>
#include <Log.h>
#include <MetricsRegistry.h>
#include <Span.h>
#include <Tracer.h>

namespace uri_shortener {

/**
 * @brief Observable decorator for message handler.
 *
 * Adds observability (spans, metrics) to message handling.
 */
class ObservableMessageHandler : public zenith::execution::IMessageHandler {
public:
  explicit ObservableMessageHandler(zenith::execution::IMessageHandler& inner);

  void handle(zenith::execution::Message& msg) override;

private:
  zenith::execution::IMessageHandler& m_inner;
  std::shared_ptr<obs::Tracer> m_tracer;
  obs::MetricsRegistry m_metrics;
};

} // namespace uri_shortener
