cmake_minimum_required(VERSION 3.10)

# Set the project name
project(tlpi VERSION 1.0)

#configure_file(tlpi.h.in tlpi.h)

# Add the executables
add_executable(tee file_io/tee/src/tee.cpp)
add_executable(cp file_io/cp/src/cp.cpp)
add_executable(id 9_credentials/id/src/id.cpp)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")