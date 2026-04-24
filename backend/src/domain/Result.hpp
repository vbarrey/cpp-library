#pragma once

#include <expected>
#include "DomainError.hpp"

template<typename T>
using Result = std::expected<T, DomainError>;

using VoidResult = std::expected<void, DomainError>;