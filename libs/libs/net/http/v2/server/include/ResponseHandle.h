#pragma once

#include <boost/asio/io_context.hpp>

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <IScopedResource.h>

namespace zenith::http2 {

class ResponseHandle : public std::enable_shared_from_this<ResponseHandle> {
public:
  using SendFunction =
      std::function<void(int status, std::map<std::string, std::string> headers, std::string body)>;

  ResponseHandle(SendFunction send_fn, boost::asio::io_context& io_ctx);

  void send(int status, std::map<std::string, std::string> headers, std::string body);

  void mark_closed() noexcept;

  [[nodiscard]] bool is_alive() const noexcept;

  void add_scoped_resource(std::unique_ptr<zenith::execution::IScopedResource> resource) {
    m_scoped_resources.push_back(std::move(resource));
  }

private:
  SendFunction m_send_fn;
  boost::asio::io_context& m_io_ctx;
  std::atomic<bool> m_stream_alive{true};
  std::vector<std::unique_ptr<zenith::execution::IScopedResource>> m_scoped_resources;
};

} // namespace zenith::http2
