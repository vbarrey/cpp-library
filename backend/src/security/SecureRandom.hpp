#pragma once

#include <array>
#include <cstdint>
#include <random>
#include "../domain/Result.hpp"

class SecureRandom {
public:
    template<std::size_t N>
    static Result<std::array<uint8_t, N>> bytes() {
        std::array<uint8_t, N> buffer{};

        std::random_device rd;

        for (auto& byte : buffer) {
            byte = static_cast<uint8_t>(rd());
        }

        return buffer;
    }
};