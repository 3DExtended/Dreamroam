cmake_minimum_required(VERSION 3.0)
project(Dreamroam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_STATIC_LIBS ON)

add_compile_definitions(_USE_MATH_DEFINES)

# add glm 
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/glm/glm")
target_include_directories(glm_static PUBLIC "extern/glm")

# add glfw
add_subdirectory("extern/glfw")

# add lava
add_subdirectory("extern/lava")
add_subdirectory("extern/lava-extras")

# Dreamroam definition
file(GLOB_RECURSE DREAMROAMSOURCE "src/*.cc" "src/*.hh")
file(GLOB_RECURSE SHADERS "src/shaders/*")

# for vsstudio: 
# group src files into logical folders for the .sln file
macro(GroupSources curdir)
	file(GLOB children RELATIVE "${PROJECT_SOURCE_DIR}/${curdir}" "${PROJECT_SOURCE_DIR}/${curdir}/*")
	foreach(child ${children})
		if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/${curdir}/${child}")
			GroupSources("${curdir}/${child}")
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
			source_group(${groupname} FILES "${PROJECT_SOURCE_DIR}/${curdir}/${child}")
		endif()
	endforeach()
endmacro()
GroupSources(src)

INCLUDE_DIRECTORIES("src/")
INCLUDE_DIRECTORIES("extern/")

# list all shaders to compile
list(APPEND lava_pack_shaders
        "${CMAKE_CURRENT_LIST_DIR}/src/shaders/cube.vert" "cube_vert.spv"
        "${CMAKE_CURRENT_LIST_DIR}/src/shaders/cube.frag" "cube_frag.spv"
        )
set(lava_pack_shaders "${lava_pack_shaders}" CACHE INTERNAL "lava_pack_shaders")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(Dreamroam ${DREAMROAMSOURCE} ${SHADERS})

target_include_directories(Dreamroam PRIVATE ".")
target_compile_options(Dreamroam PRIVATE -Wall)
target_link_libraries(
	Dreamroam PUBLIC
	glm_static
	lava
	lava-extras-pipeline
	lava-extras-renderer  
	lava-extras-glfw
	lava-extras-pack-resources
	lava-extras-geometry)