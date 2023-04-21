# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 2023-04-22 - Edu
### Added
- `example.conf` a configuration file structured following ningx conf file structure rules.
- `src/conf` directory including:
-- `location.hpp` struct with every directive of a server location in the configuration file
-- `serverconf.hpp` class with every directive of a server in the configuration file
-- `conf.hpp` & `conf.cpp` class to parse the configuration file, handling errors properly
- Added some test on main to show it working `./webser conf`
### Changed
- Makefile now include con compile `mkdir -p $(@D)` wich creates directories needed by itself without asking explicit
- Makefile now include flag `-MMD` wich created d files in ./obj with the list of files needed to compile every object

## 2023-04-16 - Jorge
### Added
- `Filetypes::get_suffix()` will now get the file suffix directly. It's been applied to the header generator.
	(!) We need to decide what to return if the file type isn't known.
- `return_error_message()` recieves an error code and will generate a whole response for it.
- `file_reader()` in `utils.cpp`.
Moved `Filetypes.*pp`to the `responses` directory.

## 2023-04-15 - Jorge
### Added
- `responses/responses.cpp` has some functions to retrieve files and generate a valid header to be sent to the client.
- New class `Filetypes` used to retrieve the appropriate `Content-Type` parameter for the HTTP/1.1 header.

## 2023-04-13 - Edu
### Changed
- Made cast explicit on server (`server.cpp` & `server.hpp`)

## 2023-04-09 - Edu
## Added
- Added `utils/log.hpp` to handle logs
### Changed
- Simplifying server (`server.cpp` & `server.hpp`) contains a version of pollserver including socket, ipaddress, port, and backlog and handle the process of `socket`>`bind`>`listen` as starting the server

## 2023-04-08 - Edu
### Changed
- PollServer modified with cpp's std::vector instead of c linked list

## 2023-04-09 - Jorge
### Added
- First parsing of the request and error management.
- `general.hpp` file that will be used by the other `.hpp` files to avoid including external functions multiple times.
- Utils file with a C++ equivalent `ft_split` function. More useful functions are expected.

Most things are individual functions, meaning the general program hasn't changed and the functions are not being used.

## 2023-04-08 - Edu
### Added
- Added Synchornous_IO_Multiplexing servers  (`SelectServer.hpp`, `SelectServer.cpp`, `PollServer.hpp` & `PollServer.cpp`)
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
