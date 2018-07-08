
cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)
project(ContinuousIntegrationSample-CPP)

file(GLOB Sources
	source/*.cpp
	source/*.c
	source/*.cc
	source/*.cxx
)

add_executable(Main ${Sources})
