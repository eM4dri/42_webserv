#!/bin/bash
# Workaround to have unit test for some private functions without refactoring all code, with a better design pattern
# This script make public some private methods for unit test

if [ $(uname -s) = 'Darwin' ]; then
	find ./src -type f -name "*.hpp" -exec sed -i "" "s|// public:	//	gTest public|public:	//	gTest public|" {} +
elif [ $(uname -s) = 'Linux' ]; then
	find ./src -type f -name "*.hpp" -exec sed -i 's|// public:	//	gTest public|public:	//	gTest public|' {} +
else
	echo "This unit test are prepared to run either on Linux or Darwin systems"
fi
