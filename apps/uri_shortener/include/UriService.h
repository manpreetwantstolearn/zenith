#pragma once

#include "IUriRepository.h"
#include "IUriService.h"

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace uri_shortener {

class UriService final : public IUriService {
public:
  explicit UriService(std::shared_ptr<IUriRepository> repository);
  ~UriService() override = default;

  [[nodiscard]] std::string shorten(std::string_view long_url) override;
  [[nodiscard]] std::optional<std::string> expand(std::string_view short_code) override;

private:
  std::shared_ptr<IUriRepository> repository_;

  // Base62 Logic
  static std::string encode_base62(uint64_t id);
  static const std::string BASE62_ALPHABET;
};

} // namespace uri_shortener
