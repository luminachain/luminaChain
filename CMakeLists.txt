cmake_minimum_required(VERSION 3.10)
project(LuminaChain VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Define the executable
add_executable(lumina_wallet ${SOURCES})

# Link libraries
target_link_libraries(lumina_wallet)

# Install
install(TARGETS lumina_wallet DESTINATION bin)