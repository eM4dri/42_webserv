#!/bin/bash
# Workaround to have unit test for some private functions without refactoring all code, with a better design pattern
# This script return to private some public methods post unit test

find ./src -type f -name "*.hpp" -exec sed -i 's|public:	//	gTest public|// public:	//	gTest public|' {} +
