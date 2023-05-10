**To add general notes that doesn't fit in a README.md**
## Ubuntu on 42 for testing webserv
To test the project on ubuntu docker with las versions of GCC, Clang & Valgrind. We can use `https://github.com/yeta1990/docker-gcc-clang`. Steps:
1. Launch docker and waits till is running susccessfully. If not use [https://github.com/irodrigo-42Mad/repair_Docker.git]: https://github.com/irodrigo-42Mad/repair_Docker.git
2. We can use comand `docker run -it --rm -v $PWD:/home/marvin/docker yeta1990/gcc-clang-42` we can add -p HOST_PORT:DOCKER_PORT to expose some port for testing `docker run -p 8081:8080 -it --rm -v $PWD:/home/marvin/docker yeta1990/gcc-clang-42`, on host you can make calls to 8081 to get to 8080 on docker
3. Use `make re` everytime you want to switch between mac/ubuntu run time