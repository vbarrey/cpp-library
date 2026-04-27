#include "PasswordHasher.hpp"
#include "SecureRandom.hpp"
#include "../domain/Result.hpp"
#include <argon2.h>
#include <array>

Result<std::string> PasswordHasher::hash(const std::string& password) {
    constexpr uint32_t t_cost = 2;
    constexpr uint32_t m_cost = 1 << 16;
    constexpr uint32_t parallelism = 1;

    constexpr size_t salt_len = 16;
    constexpr size_t hash_len = 32;

    auto saltResult = SecureRandom::bytes<salt_len>();

    if (!saltResult) {
        return std::unexpected(saltResult.error());
    }

    auto salt = saltResult.value();

    std::array<char, 128> encoded{};

    auto result = argon2id_hash_encoded(
        t_cost,
        m_cost,
        parallelism,
        password.data(),
        password.size(),
        salt.data(),
        salt_len,
        hash_len,
        encoded.data(),
        encoded.size()
    );

    if (result != ARGON2_OK) {
        return std::unexpected(
            DomainError{ argon2_error_message(result) }
        );
    }

    return std::string(encoded.data());
}

Result<bool> PasswordHasher::verify(
    const std::string& password,
    const std::string& hash
) {
    auto result = argon2id_verify(
        hash.c_str(),
        password.data(),
        password.size()
    );

    if (result == ARGON2_OK) {
        return true;
    }

    if (result == ARGON2_VERIFY_MISMATCH) {
        return false;
    }

    return std::unexpected(
        DomainError{ argon2_error_message(result) }
    );
}