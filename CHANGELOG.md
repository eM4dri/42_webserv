# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 2023-05-17 - Edu
### Fixed
- Fixed  `gTest` pre/ post scripts to be able to work on MAC/LINUX systems
- Fixed some `conf` parsing errors on methods & default_path without initial `/`, added some unit test for this methods

## 2023-05-15 - Edu
### Added
- Added workaround to allow use unit test on private methods making public at compiling gTest, bases on this scripts `pre/post_gTest.sh`, example on `conf.hpp`,  usage copy `// public:	//	gTest public` before the private methods to test
- Added `valid_redirect` on `conf` to allow every path as `valid_path` and `http/https`, unit test included, also handled circular redirections missing unit test

### Changed
- Log error on `cgi` errors

### Fixed
- Fix `sed` command discrepancies bewteen mac and GNU [Link](https://stackoverflow.com/questions/43171648/sed-gives-sed-cant-read-no-such-file-or-directory)

## 2023-05-12 - Edu
### Added
- Added `conf` unit test, to test `valid_path`, include examples with paremeterized test, currently failed at testing private function properly
- Function to print vector and ending null array on `log`
- New folder `cgi` to store executables & scripts
### Changed
- Added `cgi_script` to cgi constructor to load the script to exec
### Fixed
- Comment set but not used variable `is_dir` on `Response.cpp`
- Comment `Filetypes` unit test on `CMakeList.txt` as pipeline can't open files

## 2023-05-11 - Edu
### Added
- Added `utils` unit test, to test `correct_path`, include examples with paremeterized test

## 2023-05-10 - Edu
### Added
- Added `github-actions` rule to check make all compiles
- Added `Filetypes` unit test

### Changed
- Added `conf` validations for locations methods, refactorize some code
- Added some color alias on `log`

## 2023-05-09 - Edu
### Added
- Added some color logs (background & foreground) to `log.hpp`
- File `TODO.md` added to keep tracking everything we acknowledge as TODO
- File `NOTES.md` added to add general notes that doesn't fit in a README.md
- `conf` added default `\` location for every new server, regardless if it's an actual directive.

### Changed
- Some new `conf` entities such as cgi, file_root, and some rename (default_root & request_path)

## 2023-05-08 - Edu
### Moved
- Move `Filetypes` into `serverconf`to be able too access it from server, relocate class into `conf` directory
### Fixed
- Included `<errno.h>` on `Response.cpp` and `utils.cpp`

## 2023-05-07 - Edu
### Added
- Class `cgi` to handle cgi programs, this version contains response of script `reply.py`, but request and header response is mocked
- Added some sandbox examples to play with cgi

### Removed
- Removed obsolete tests form the `main` and `Makefile`, moved mock early  servers versions to sandbox

### Fixed
- Fixed unit test paths & added some missing includes on `cgi.cpp`

## 2023-05-06 - Jorge
### Added
- More error cases are handled:
	- `400 Bad Request` If the given request's first line is badly formatted.
	- `500 Server Error` If the file containing the file types isn't accessible.
- Function overload for `return_error_message()` so it can print an explicit error message on the default error page.

## 2023-05-05 - Jorge
### Reworked
- Responses are now stored as an object and need to be built as a string with the function `std::string Response::generate_response()` to be returned.
	- Some tests form the `main` turned obsolete, so a few of them were removed.
	- The test `gettest` allows an additional `dir` parameter to test both files and directories.
- Function `correct_path()` now returns a full path without `..` expressions.

### Bug fixes
- The index of files when requesting a directory now hides the `Parent directory` button when found in the root.

## 2023-05-03 - Jorge
- Responses are still being turned into objects. It mostly works except for the cases where a directory is requested instead of a file.

## 2023-05-02 - Edu
### Changed
- Minor changes addded some betterComments class descriptions & mock accepted response every request on server.cpp

## 2023-05-01 - Jorge
### Reworked
- Requests are now stored in an object.
- **[Work in progress]** Responses will also be considered an object and it will recieve the generated request as a parameter.

## 2023-04-30 - Jorge
### Reworked
- The requests will be reprogrammed so they are treated as an object. This might take some days to be completed.

## 2023-04-30 - Edu
### Added
- New `server.hpp` parameters constructor using `serverconf.hpp` (test on main using `./webserv serverconf`)
- Listen directive validation before parsing on `conf.cpp`
### Changed
- Minor changes on `conf.cpp`, name and references instead of copy values
### Fixed
- Close directory on Directories.cpp

## 2023-04-28 - Jorge
### Added
- `method_get()` now identifies if the file given is a file and displays a webpage with all the files inside.
	- We'll need to check if we must show ALL the files in a directory or not (maybe hidden files or files without permission).
	- It doesn't check if the chosen directory allows showing the full list of files or not, which should be configured from `example.conf`.

### Current bugs
- **Segfault** when only a `/` is requested as a path on `getdirtest`.
- `create_directory_index()` is unable to properly identify whether the requested directory is the server's root in order to hide the `parent directory` button.

## 2023-04-25 - Jorge
### Improved
- We now consider the request to start at the established SERVER_ROOT (stored in `general.hpp` for now), and check if the request attempts to exit said ROOT.

*(Not tested on a Linux machine)* Fixed fsanitize crash when executing `./webserv dirpage`.

## 2023-04-24 - Jorge
### Added
- `method_get()` calls `return_content()` and gets the full response for a **GET** request.
	- If the requested file cannot be opened for some reason, it returns a standard `404`/`500`/`501` response.
	- There's a test in `main.cpp` to try it out with the parameter `gettest`. There's still a lot of testing left.
	- **Note:** Only the first line of the request is taken into account for now.

## 2023-04-23 - Jordi 🌹
### Added
- Added some example files and tests in the `main`.

Fixed a few bugs on the path corrector and header parsing.

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

### Fixed
- Include `<cstring> // std::strcmp` & `<iomanip> // std::setprecision` on general.hpp
- Define MACRO `st_mtime` on Directory.hpp to be able to handle time thorugh several OS following [THIS](https://stackoverflow.com/questions/11373505/getting-the-last-modified-date-of-a-file-in-c)
- C function `open` uses const char * as input instead of std::string fixed with c_str

## 2023-04-21 - Jorge
### Added
- Function `to_string()` used to replace C++11's `std::to_string()`.

### Fixed
- Function `create_directory_index()` now shows the correct modification date and file size.

## 2023-04-20 - Jorge
### Added
- Function `create_directory_index()` used to return an `html`-formatted string in case the user requests a directory instead of a file. *[Still work in progress]*

### Changed
- Function `get_file()` now sets a variable indicating the status of the file given (`file not found`, `unauthorized` or `is a directory`).

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
