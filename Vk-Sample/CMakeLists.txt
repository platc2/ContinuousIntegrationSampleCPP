project(${ProjectName})

file(GLOB VulkanShaders
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/resources/shaders/vulkan/*.vert"
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/resources/shaders/vulkan/*.frag"
)
if(VulkanShaders)
	source_group("Vulkan Shaders" FILES ${VulkanShaders})
endif()


file(GLOB GLSLShaders
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/resources/shaders/glsl/*.vert"
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/resources/shaders/glsl/*.frag"
)
if(GLSLShaders)
	source_group("Shaders" FILES ${GLSLShaders})
endif()


file(GLOB Configs
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/resources/configs/json/*.json"
)
if(Configs)
	source_group("Configs" FILES ${Configs})
endif()


set(IncludeDirectories "include/")
unset(HeaderGlobs)
foreach(IncludeDirectory IN ITEMS ${IncludeDirectories})
	include_directories(${IncludeDirectory})
	list(APPEND HeaderGlobs "${CMAKE_SOURCE_DIR}/${ProjectDirectory}/${IncludeDirectory}/*.h" "${CMAKE_SOURCE_DIR}/${ProjectDirectory}/${IncludeDirectory}/.hpp")
endforeach()
file(GLOB HeaderFiles ${HeaderGlobs})
if(HeaderFiles)
	source_group("Headers" FILES ${HeaderFiles})
endif()

file(GLOB SourceFiles
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/source/*.c"
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/source/*.cpp"
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/source/*.cc"
	"${CMAKE_SOURCE_DIR}/${ProjectDirectory}/source/*.cxx"
)
if(SourceFiles)
	source_group("Sources" FILES ${SourceFiles})
endif()

set(Dependencies ${SourceFiles} ${HeaderFiles} ${VulkanShaders} ${GLSLShaders} ${Configs})
if(Dependencies)
	set(OutputDirectory "${CMAKE_SOURCE_DIR}/${ProjectDirectory}/bin/")
	add_executable(${ProjectDirectory} ${SourceFiles} ${HeaderFiles} ${VulkanShaders} ${GLSLShaders})
	set_property(TARGET ${ProjectDirectory} PROPERTY CXX_STANDARD 11)
	set_property(TARGET ${ProjectDirectory} PROPERTY CXX_STANDARD_REQUIRED TRUE)
	set_property(TARGET ${ProjectDirectory} PROPERTY RUNTIME_OUTPUT_DIRECTORY "${OutputDirectory}")
	target_link_libraries(${ProjectDirectory} glfw Vulkan::Vulkan)

	# Compile SPIR-V shaders
	# Based on: https://gist.github.com/vlsh/a0d191701cb48f157b05be7f74d79396
	unset(SpirvShaders)
	foreach(VulkanShader IN ITEMS ${VulkanShaders})
		get_filename_component(VulkanShaderFile ${VulkanShader} NAME)
		set(SpirvShader "${OutputDirectory}/${VulkanShaderFile}.spv")

		add_custom_command(
			OUTPUT ${SpirvShader}
			COMMAND ${CMAKE_COMMAND} -E make_directory ${OutputDirectory}
			COMMAND ${GlslValidator} -V ${VulkanShader} -o ${SpirvShader}
			DEPENDS ${VulkanShader}
		)
		list(APPEND SpirvShaders ${SpirvShader})
	endforeach()

	add_custom_target(
		${ProjectName}-CompileSpirvShaders
		DEPENDS ${SpirvShaders}
	)
	add_dependencies(${ProjectDirectory} ${ProjectName}-CompileSpirvShaders)
endif()
