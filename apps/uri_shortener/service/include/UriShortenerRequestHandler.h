#pragma once

#include <memory>

#include <Context.h>
#include <IMessageHandler.h>
#include <IRequest.h>
#include <IResponse.h>
#include <StickyQueue.h>

namespace uri_shortener {

class UriShortenerRequestHandler {
public:
  explicit UriShortenerRequestHandler(zenith::execution::StickyQueue& pool);

  void handle(std::shared_ptr<zenith::router::IRequest> req,
              std::shared_ptr<zenith::router::IResponse> res);

private:
  zenith::execution::StickyQueue& m_pool;

  uint64_t generate_session_id(zenith::router::IRequest& req);
};

} // namespace uri_shortener
