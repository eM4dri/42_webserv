cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  runTest
  ../src/network/socket/ASocket.hpp
  ../src/network/socket/ASocket.cpp
  ../src/network/socket/BindSocket.hpp
  ../src/network/socket/BindSocket.cpp
  ../src/network/socket/ListenSocket.hpp
  ../src/network/socket/ListenSocket.cpp
  ../src/network/server/AServer.hpp
  ../src/network/server/AServer.cpp

  test/network/socket/ASocketTest.cc
  test/network/socket/BindSocketTest.cc
  test/network/socket/ListenSocketTest.cc
  test/network/server/AServerTest.cc
  
)
target_link_libraries(
  runTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTest)
