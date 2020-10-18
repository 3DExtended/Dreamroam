cmake_minimum_required(VERSION 3.8)
project(dreamroam)

set(LAVA_LINK_TYPE STATIC CACHE STRING "Defines the build type of libraries (static is default)")
if(MSVC)
    set(LAVA_LINK_TYPE STATIC CACHE STRING "" FORCE) # unfortunately, we need to link statically here
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_STATIC_LIBS ON)

add_compile_definitions(_USE_MATH_DEFINES)
add_compile_definitions(GLM_FORCE_DEPTH_ZERO_TO_ONE)

IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	add_compile_definitions(DR_DEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

# add glm 
add_subdirectory("${PROJECT_SOURCE_DIR}/extern/glm/glm")
target_include_directories(glm_static PUBLIC "extern/glm")

# add glfw
add_subdirectory("extern/glfw")

# create imgui targets
add_library(imgui STATIC
	"extern/imgui/imconfig.h"
	"extern/imgui/imgui.cpp"
	"extern/imgui/imgui.h"
	"extern/imgui/imgui_demo.cpp"
	"extern/imgui/imgui_draw.cpp"
	"extern/imgui/imgui_internal.h"
	"extern/imgui/imgui_widgets.cpp"
	"extern/imgui/imstb_rectpack.h"
	"extern/imgui/imstb_textedit.h"
	"extern/imgui/imstb_truetype.h"
	"extern/lava-extras/imgui/lava-extras/imgui/impl/imgui_impl_lava.cc"
	"extern/lava-extras/imgui/lava-extras/imgui/impl/imgui_impl_lava.hh"
	"extern/lava-extras/imgui/lava-extras/imgui/impl/imgui_impl_glfw.cc"
	"extern/lava-extras/imgui/lava-extras/imgui/impl/imgui_impl_glfw.hh"
)
target_include_directories(imgui PUBLIC
	"extern"
	"extern/imgui"
	"extern/glm"
	)

# create imgui targets
add_library(imguinodeeditor STATIC
	"extern/imgui-node-editor/crude_json.cpp"
	"extern/imgui-node-editor/crude_json.h"
	"extern/imgui-node-editor/imgui_bezier_math.h"
	"extern/imgui-node-editor/imgui_bezier_math.inl"
	"extern/imgui-node-editor/imgui_canvas.cpp"
	"extern/imgui-node-editor/imgui_canvas.h"
	"extern/imgui-node-editor/imgui_extra_math.h"
	"extern/imgui-node-editor/imgui_extra_math.inl"
	"extern/imgui-node-editor/imgui_node_editor.cpp"
	"extern/imgui-node-editor/imgui_node_editor.h"
	"extern/imgui-node-editor/imgui_node_editor_api.cpp"
	"extern/imgui-node-editor/imgui_node_editor_internal.h"
)
target_include_directories(imguinodeeditor PUBLIC
	"extern"
	"extern/imgui"
	"extern/glm"
	)


# add lava
add_subdirectory("extern/lava")

target_link_libraries(imgui PUBLIC lava glfw)

add_subdirectory("extern/lava-extras")

target_include_directories(lava-extras-imgui PUBLIC
	"extern"
	"extern/imgui"
	"extern/glm"
)

# dreamroam definition
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
INCLUDE_DIRECTORIES("extern/glfw/include")

# list all shaders to compile
list(APPEND lava_pack_shaders
        "${CMAKE_CURRENT_LIST_DIR}/src/shaders/cube.vert" "shaders/cube_vert.spv"
        "${CMAKE_CURRENT_LIST_DIR}/src/shaders/cube.frag" "shaders/cube_frag.spv"       
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/output.vert" "shaders/output_vert.spv"
        "${CMAKE_CURRENT_LIST_DIR}/src/shaders/output.frag" "shaders/output_frag.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/plane.frag" "shaders/plane_frag.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/plane.vert" "shaders/plane_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/opaque.frag" "shaders/opaque_frag.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/opaque.vert" "shaders/opaque_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/opaqueTexturedSimple.frag" "shaders/opaqueTexturedSimple_frag.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/opaqueTexturedSimple.vert" "shaders/opaqueTexturedSimple_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/opaqueTexturedInstanced.frag" "shaders/opaqueTexturedInstanced_frag.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/opaqueTexturedInstanced.vert" "shaders/opaqueTexturedInstanced_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/transparent.frag" "shaders/transparent_frag.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/transparent.vert" "shaders/transparent_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/transparentTexturedSimple.frag" "shaders/transparentTexturedSimple_frag.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/transparentTexturedSimple.vert" "shaders/transparentTexturedSimple_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/shadowMapInstanced.vert" "shaders/shadowMapInstanced_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/shadowMap.vert" "shaders/shadowMap_vert.spv"
		"${CMAKE_CURRENT_LIST_DIR}/src/shaders/shadowMap.frag" "shaders/shadowMap_frag.spv"
        )
set(lava_pack_shaders "${lava_pack_shaders}" CACHE INTERNAL "lava_pack_shaders")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_library(dreamroam ${LAVA_LINK_TYPE} ${DREAMROAMSOURCE} ${SHADERS})

target_include_directories(dreamroam PRIVATE ".")
target_compile_options(dreamroam PRIVATE -Wall)
target_link_libraries(
	dreamroam PUBLIC
	glm_static
	lava
	lava-extras-pipeline
	lava-extras-renderer  
	imgui
	glfw
	lava-extras-glfw
	lava-extras-imgui
	imguinodeeditor
	lava-extras-pack-resources
	lava-extras-geometry)

add_subdirectory("examples")
