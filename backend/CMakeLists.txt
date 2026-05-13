cmake_minimum_required(VERSION 3.20)

project(omnedia-backend)

# =========================================================
# C++ Configuration
# =========================================================

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_compile_definitions(_WIN32_WINNT=0x0A00)

add_compile_options(/std:c++latest)

# =========================================================
# Dependencies
# =========================================================

find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(unofficial-argon2 CONFIG REQUIRED)

# =========================================================
# Domain (headers only for now)
# =========================================================

add_library(omnedia-domain INTERFACE)

target_include_directories(omnedia-domain INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# =========================================================
# Infrastructure
# =========================================================

add_library(omnedia-infrastructure
    src/security/PasswordHasher.cpp
    src/config/ConfigLoader.cpp
)

target_include_directories(omnedia-infrastructure PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(omnedia-infrastructure PUBLIC
    libpqxx::pqxx
    unofficial::argon2::libargon2
    nlohmann_json::nlohmann_json
)

# =========================================================
# API Executable
# =========================================================

add_executable(omnedia-api
    src/apps/api/main.cpp
)

target_link_libraries(omnedia-api PRIVATE
    Crow::Crow
    omnedia-domain
    omnedia-infrastructure
)

# =========================================================
# Worker Executable
# =========================================================

add_executable(omnedia-worker
    src/apps/worker/main.cpp
)

target_link_libraries(omnedia-worker PRIVATE
    omnedia-domain
    omnedia-infrastructure
)

# =========================================================
# Copy config.json after build
# =========================================================

add_custom_command(TARGET omnedia-api POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/../config.json
    $<TARGET_FILE_DIR:omnedia-api>
)

add_custom_command(TARGET omnedia-worker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/../config.json
    $<TARGET_FILE_DIR:omnedia-worker>
)