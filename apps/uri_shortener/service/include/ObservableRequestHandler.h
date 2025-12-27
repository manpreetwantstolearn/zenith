#pragma once

#include "UriShortenerRequestHandler.h"

#include <memory>

#include <Log.h>
#include <MetricsRegistry.h>
#include <Span.h>
#include <Tracer.h>

namespace uri_shortener {

/**
 * @brief Observable decorator for URI Shortener request handler.
 *
 * Wraps the request handler and adds observability.
 */
class ObservableRequestHandler {
public:
  explicit ObservableRequestHandler(UriShortenerRequestHandler& inner);

  void handle(std::shared_ptr<zenith::router::IRequest> req,
              std::shared_ptr<zenith::router::IResponse> res);

private:
  UriShortenerRequestHandler& m_inner;
  std::shared_ptr<obs::Tracer> m_tracer;
  obs::MetricsRegistry m_metrics;
};

} // namespace uri_shortener
