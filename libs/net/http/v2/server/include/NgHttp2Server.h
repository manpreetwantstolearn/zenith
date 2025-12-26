#pragma once

#include "Http2Server.h"
#include "Http2ServerError.h"

#include <nghttp2/asio_http2_server.h>

#include <atomic>
#include <string>

#include <Result.h>

namespace zenith::http2 {

class NgHttp2Server {
public:
  NgHttp2Server(const ServerConfig& config);
  ~NgHttp2Server();

  void handle(const std::string& method, const std::string& path, Http2Server::Handler handler);

  zenith::outcome::Result<void, Http2ServerError> start();
  zenith::outcome::Result<void, Http2ServerError> join();
  zenith::outcome::Result<void, Http2ServerError> stop();

private:
  ServerConfig m_config;
  std::atomic<bool> m_is_running{false};
  nghttp2::asio_http2::server::http2 m_server;
};

} // namespace zenith::http2
