#!/bin/bash
# Script to enable throwing exception on src/conf/conf.hpp

if [ $(uname -s) = 'Darwin' ]; then
while cat ./src/conf/conf.cpp | grep '// throw std::invalid_argument' &> /dev/null;
do
	find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|// throw std::invalid_argument|throw std::invalid_argument|" {} +
done
	find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|LOG_ERROR_CONF(|// LOG_ERROR_CONF(|" {} +
	find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|#define // LOG_ERROR_CONF|#define LOG_ERROR_CONF|" {} +
elif [ $(uname -s) = 'Linux' ]; then
while cat ./src/conf/conf.cpp | grep '// throw std::invalid_argument' &> /dev/null;
do
	find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|// throw std::invalid_argument|throw std::invalid_argument|" {} +
done
	find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|LOG_ERROR_CONF(|// LOG_ERROR_CONF(|" {} +
	find ./src/conf -type f -name "conf.cpp" -exec sed -i "" "s|#define // LOG_ERROR_CONF|#define LOG_ERROR_CONF|" {} +
else
	echo "This script is prepared to run either on Linux or Darwin systems"
fi
