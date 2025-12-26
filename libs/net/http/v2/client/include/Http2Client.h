#pragma once

#include "Http2ClientError.h"
#include "Http2ClientResponse.h"
#include "http2client.pb.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

#include <Result.h>

namespace zenith::http2 {

using ResponseHandler =
    std::function<void(zenith::outcome::Result<Http2ClientResponse, Http2ClientError>)>;

class Http2Client {
public:
  explicit Http2Client(const ClientConfig& config);
  ~Http2Client();

  Http2Client(const Http2Client&) = delete;
  Http2Client& operator=(const Http2Client&) = delete;

  void submit(const std::string& host, uint16_t port, const std::string& method,
              const std::string& path, const std::string& body,
              const std::map<std::string, std::string>& headers, ResponseHandler handler);

private:
  class Impl;
  std::unique_ptr<Impl> m_impl;
};

} // namespace zenith::http2
