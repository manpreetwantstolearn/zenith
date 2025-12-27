#pragma once

#include "IDataServiceAdapter.h"

#include <memory>

#include <IMessageHandler.h>
#include <IQueue.h>

namespace uri_shortener::service {

/// Handler for DataServiceRequest messages on SharedQueue
/// Extracts requests, calls adapter, and submits responses back to StickyQueue
class DataServiceHandler : public zenith::execution::IMessageHandler {
public:
  /// Construct with adapter and response queue
  /// @param adapter The data service adapter to use
  /// @param response_queue Queue to submit responses back to
  DataServiceHandler(IDataServiceAdapter& adapter,
                     std::shared_ptr<zenith::execution::IQueue> response_queue);

  ~DataServiceHandler() override = default;

  /// Handle a message from SharedQueue
  void handle(zenith::execution::Message& msg) override;

private:
  IDataServiceAdapter& m_adapter;
  std::shared_ptr<zenith::execution::IQueue> m_response_queue;
};

} // namespace uri_shortener::service
