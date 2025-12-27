#pragma once

#include "DataServiceMessages.h"

#include <memory>
#include <string>
#include <variant>

#include <IRequest.h>
#include <IResponse.h>

namespace uri_shortener {

struct HttpRequestMsg {
  std::shared_ptr<zenith::router::IRequest> request;
  std::shared_ptr<zenith::router::IResponse> response;
};

struct DbQueryMsg {
  std::string operation;
  std::string data;
  std::shared_ptr<zenith::router::IResponse> response;
};

struct DbResponseMsg {
  std::string result;
  bool success;
  std::string error;
  std::shared_ptr<zenith::router::IResponse> response;
};

using UriPayload =
    std::variant<HttpRequestMsg, DbQueryMsg, DbResponseMsg, service::DataServiceResponse>;

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

} // namespace uri_shortener
