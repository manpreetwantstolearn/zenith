#pragma once
#include "ConfigStructs.h"

#include <optional>
#include <stdexcept>
#include <string>

namespace config {

class ConfigValidator {
public:
  static void validateBootstrap(const BootstrapConfig& config);
  static std::optional<std::string> validateOperational(const OperationalConfig& config);
  static std::optional<std::string> validateRuntime(const RuntimeConfig& config);
  static void validate(const Config& config);

private:
  static bool isValidLogLevel(const std::string& level);
  static bool isValidPort(uint16_t port);
  static bool isValidTimeout(int timeout_ms);
};

} // namespace config
