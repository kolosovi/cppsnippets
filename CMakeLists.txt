cmake_minimum_required(VERSION 3.10)

project(coroutines)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wpedantic -Werror")
if(NOT disable_sanitizers)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address")
endif()

enable_language(CXX)

include_directories(include)

# Target naming convention: target name corresponds to .cpp filename without the
# src/ prefix, with directory separators converted to hyphens. Everything else
# is left as is.
add_executable(constcast-main.cpp src/constcast/main.cpp)