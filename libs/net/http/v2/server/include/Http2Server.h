#pragma once

#include "Http2ServerError.h"
#include "Router.h"
#include "http2server.pb.h"

#include <functional>
#include <memory>
#include <string>

#include <Result.h>

namespace zenith::http2 {

class Http2Request;
class Http2Response;

class Http2Server {
public:
  explicit Http2Server(const ServerConfig& config);
  ~Http2Server();

  Http2Server(const Http2Server&) = delete;
  Http2Server& operator=(const Http2Server&) = delete;

  using Handler = zenith::router::Handler;

  void handle(const std::string& method, const std::string& path, Handler handler);

  zenith::outcome::Result<void, Http2ServerError> start();
  zenith::outcome::Result<void, Http2ServerError> join();
  zenith::outcome::Result<void, Http2ServerError> stop();

  [[nodiscard]] zenith::router::Router& router() {
    return m_router;
  }

private:
  class Impl;
  std::unique_ptr<Impl> m_impl;
  zenith::router::Router m_router;
};

} // namespace zenith::http2
