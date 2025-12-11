#pragma once

#include "Http2Response.h"

#include <memory>
#include <string>

namespace http2server {

class ResponseHandle;

class Response::Impl {
public:
  std::weak_ptr<ResponseHandle> response_handle;
  bool closed = false;

  Impl() = default;

  int status_code = 200;
  std::string body_buffer;
};

} // namespace http2server
