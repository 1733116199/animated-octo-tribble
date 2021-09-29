project(cpen442a1)
cmake_minimum_required(VERSION 3.0.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(q1 
q1.cpp
score.cpp
substitution.cpp)

add_executable(q2 
q2.cpp
score.cpp
playpair.cpp)

target_link_libraries(q1 PRIVATE Threads::Threads)
target_link_libraries(q2 PRIVATE Threads::Threads)