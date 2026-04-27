#pragma once

enum class Role {
    User,
    Admin
};

inline std::string to_string(Role role) {
    switch (role) {
        case Role::User: return "user";
        case Role::Admin: return "admin";
    }
    return "user";
}