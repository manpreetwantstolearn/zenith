#pragma once

namespace zenith::http2 {

enum class Http2ClientError {
  ConnectionFailed,
  RequestTimeout,
  StreamClosed,
  NotConnected,
  SubmitFailed
};

} // namespace zenith::http2
