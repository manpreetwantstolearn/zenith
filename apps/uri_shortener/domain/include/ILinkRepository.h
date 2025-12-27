#pragma once

#include "DomainErrors.h"
#include "Result.h"
#include "ShortCode.h"
#include "ShortLink.h"

#include <memory>

namespace uri_shortener::domain {

class ILinkRepository {
public:
  virtual ~ILinkRepository() = default;
  virtual zenith::outcome::Result<void, DomainError> save(const ShortLink& link) = 0;
  virtual zenith::outcome::Result<void, DomainError> remove(const ShortCode& code) = 0;
  virtual zenith::outcome::Result<ShortLink, DomainError> find_by_code(const ShortCode& code) = 0;
  virtual bool exists(const ShortCode& code) = 0;
};

} // namespace uri_shortener::domain
