#pragma once

#include "IDataServiceAdapter.h"

#include <memory>

#include <IExecutor.h>
#include <IMessageHandler.h>

namespace uri_shortener::service {

/// Handler for DataServiceRequest messages
/// Extracts requests, calls adapter, and submits responses back to executor
class DataServiceHandler : public zenith::execution::IMessageHandler {
public:
  /// Construct with adapter and response executor
  /// @param adapter The data service adapter to use
  /// @param response_executor Executor to submit responses back to
  DataServiceHandler(IDataServiceAdapter& adapter, zenith::execution::IExecutor& response_executor);

  ~DataServiceHandler() override = default;

  /// Handle a message
  void handle(zenith::execution::Message& msg) override;

private:
  IDataServiceAdapter& m_adapter;
  zenith::execution::IExecutor& m_response_executor;
};

} // namespace uri_shortener::service
