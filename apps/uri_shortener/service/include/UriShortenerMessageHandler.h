#pragma once

#include "DataServiceMessages.h"
#include "IDataServiceAdapter.h"

#include <memory>

#include <Context.h>
#include <IMessageHandler.h>
#include <IQueue.h>
#include <IRequest.h>
#include <IResponse.h>

namespace uri_shortener {

class UriShortenerMessageHandler : public zenith::execution::IMessageHandler {
public:
  UriShortenerMessageHandler(std::shared_ptr<service::IDataServiceAdapter> adapter,
                             std::shared_ptr<zenith::execution::IQueue> response_queue);

  void setResponseQueue(std::shared_ptr<zenith::execution::IQueue> queue);

  void handle(zenith::execution::Message& msg) override;

private:
  void processHttpRequest(std::shared_ptr<zenith::router::IRequest> req,
                          std::shared_ptr<zenith::router::IResponse> res, uint64_t session_id,
                          obs::Context& trace_ctx);

  void processDataServiceResponse(service::DataServiceResponse& resp);

  std::string determine_operation(const std::string& method, const std::string& path);
  service::DataServiceOperation to_data_service_op(const std::string& operation);

  std::shared_ptr<service::IDataServiceAdapter> m_adapter;
  std::shared_ptr<zenith::execution::IQueue> m_response_queue;
};

} // namespace uri_shortener
