#!/bin/bash
# Script to disable throwing exception on src/conf/conf.hpp, instead is used log std::cerr

if [ $(uname -s) = 'Darwin' ]; then
	while cat ./src/conf/conf.cpp | grep '// LOG_ERROR_CONF(' &> /dev/null;
	do
		find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|// LOG_ERROR_CONF(|LOG_ERROR_CONF(|" {} +
	done
		find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|throw std::invalid_argument|// throw std::invalid_argument|" {} +
elif [ $(uname -s) = 'Linux' ]; then
	while cat ./src/conf/conf.cpp | grep '// LOG_ERROR_CONF(' &> /dev/null;
	do
		find ./src/conf -type f -name "conf.cpp" -exec sed -i 's|// LOG_ERROR_CONF(|LOG_ERROR_CONF(|' {} +
	done
		find ./src/conf -type f -name "conf.cpp" -exec sed -i 's|throw std::invalid_argument|// throw std::invalid_argument|' {} +
else
	echo "This script is prepared to run either on Linux or Darwin systems"
fi
