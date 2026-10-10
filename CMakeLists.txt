cmake_minimum_required(VERSION 3.25)
project(TerminalGame)

# Set the standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch nlohmann/json library
include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(TerminalGame main.cpp)

# Link the JSON library to your target
target_link_libraries(TerminalGame PRIVATE nlohmann_json::nlohmann_json)


