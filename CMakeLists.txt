cmake_minimum_required(VERSION 3.13)

project(EdidParser CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(EdidParser
 	calc-gtf-cvt.cpp
	calc-ovt.cpp
	edid-decode.cpp
	parse-base-block.cpp
	parse-cta-block.cpp
	parse-di-ext-block.cpp
	parse-displayid-block.cpp
	parse-ls-ext-block.cpp
	parse-vtb-ext-block.cpp
	parse-if.cpp
	parse-edids-from-dir.cpp)