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
#  ../src/sandbox/socket/ASocket.hpp
#  ../src/sandbox/socket/ASocket.cpp
#  ../src/sandbox/socket/BindSocket.hpp
#  ../src/sandbox/socket/BindSocket.cpp
#  ../src/sandbox/socket/ListenSocket.hpp
#  ../src/sandbox/socket/ListenSocket.cpp
#  ../src/sandbox/server/AServer.hpp
#  ../src/sandbox/server/AServer.cpp
  ../src/conf/Filetypes.hpp
  ../src/conf/Filetypes.cpp
  ../src/utils/log.hpp
  ../src/general.hpp
  ../src/utils.cpp
  ../src/to_string.cpp
  ../src/conf/conf.hpp
  ../src/conf/conf.cpp

#  test/network/socket/ASocketTest.cc
#  test/network/socket/BindSocketTest.cc
#  test/network/socket/ListenSocketTest.cc
#  test/network/server/AServerTest.cc
#  test/conf/Filetypes.cc
  test/conf/conf.cc
  test/utils.cc

)
target_link_libraries(
  runTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTest)
