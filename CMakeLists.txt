
cmake_minimum_required(VERSION 3.7.0 FATAL_ERROR)

# ==================================================
# Vulkan
# ==================================================
find_package(Vulkan REQUIRED)  # TODO: Use local libraries if not available (CMake < 3.7.0)

# Find GLSL validator for compiling SPIR-V shaders (Included in LunarG SDK)
unset(GlslValidator CACHE)
find_program(GlslValidator "glslangValidator")
if(NOT GlslValidator)
	message(WARNING "No GLSL validator found. SPIR-V shaders will not be compiled!")
endif()


# ==================================================
# OpenGL
# ==================================================
find_package(OpenGL REQUIRED)


# ==================================================
# GLFW
# ==================================================
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)


# ==================================================
# GLM
# ==================================================
include_directories(external/glm/)


set(ProjectDirectoryPattern "Vk-*")
file(GLOB ProjectDirectories RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${ProjectDirectoryPattern})
foreach(ProjectDirectory IN ITEMS ${ProjectDirectories})
	set(ProjectName ${ProjectDirectory})
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${ProjectDirectory}/CMakeLists.txt)
		message(STATUS "Found project ${ProjectDirectory}... Added")
		add_subdirectory(${ProjectDirectory})
	else()
		message(STATUS "Found project ${ProjectDirectory}... Ignoring")
	endif()
endforeach()
