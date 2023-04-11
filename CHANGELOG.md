# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 2023-04-08 - Edu
### Changed
- PollServer modified with cpp's std::vector instead of c linked list

## 2023-04-09 - Jorge
### Added
- First parsing of the request and error management.
- `general.hpp` file that will be used by the other `.hpp` files to avoid including external functions multiple times.
- Utils file with a C++ equivalent `ft_split` fucntion. More useful functions are expected.

Most things are individual functions, meaning the general program hasn't changed and the functions are not being used.

## 2023-04-08 - Edu
### Added
- Added Synchornous_IO_Multiplexing servers  (SelectServer.hpp, SelectServer.cpp, PollServer.hpp & PollServer.cpp)
### Fixed
- Getters should return const references to avoid making unnecessary copies.

## 2023-04-02 - Edu
### Added
- Added GoogleTest structure.
- Added some unit test (GoogleTest) some refinement is needed.
### Changed
- Some typos, private functions starts with '_'.
- Added some comments.

## 2023-04-01 - Edu
### Added
- Add first version of simple Webserv inspired on https://www.youtube.com/@eom-dev series C++ Web Server from Scratch. Including Makefile, structure files in folders (network, network/server, network/socket).
