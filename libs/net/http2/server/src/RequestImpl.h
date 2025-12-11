#pragma once

#include "Http2Request.h"

#include <map>
#include <string>
#include <string_view>
#include <unordered_map>

namespace http2server {

class Request::Impl {
public:
  std::string method;
  std::string path;
  std::string body;
  std::map<std::string, std::string> headers;
  std::unordered_map<std::string_view, std::string_view> path_params;

  Impl() = default;
};

} // namespace http2server
