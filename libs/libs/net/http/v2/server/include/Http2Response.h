#pragma once

#include "IResponse.h"

#include <map>
#include <memory>
#include <optional>
#include <string>

#include <IScopedResource.h>

namespace zenith::http2 {

class ResponseHandle;

class ServerResponse final : public zenith::router::IResponse {
public:
  ServerResponse() = default;
  explicit ServerResponse(std::weak_ptr<ResponseHandle> handle);

  ServerResponse(const ServerResponse&) = default;
  ServerResponse& operator=(const ServerResponse&) = default;
  ServerResponse(ServerResponse&&) noexcept = default;
  ServerResponse& operator=(ServerResponse&&) noexcept = default;

  ~ServerResponse() override = default;

  void set_status(int code) noexcept override;
  void set_header(const std::string& key, const std::string& value) override;
  void write(const std::string& data) override;
  void close() override;
  [[nodiscard]] bool is_alive() const noexcept override;

  void add_scoped_resource(std::unique_ptr<zenith::execution::IScopedResource> resource);

private:
  std::optional<int> m_status;
  std::map<std::string, std::string> m_headers;
  std::string m_body;
  std::weak_ptr<ResponseHandle> m_handle;
  bool m_closed = false;
};

} // namespace zenith::http2
