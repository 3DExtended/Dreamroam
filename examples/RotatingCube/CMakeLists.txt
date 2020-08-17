file(GLOB_RECURSE SAMPLEROTATINGCUBESOURCE "*.cc" "*.hh")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(SampleRotatingCube ${SAMPLEROTATINGCUBESOURCE})

target_compile_options(SampleRotatingCube PRIVATE -Wall)
target_link_libraries(
	SampleRotatingCube PUBLIC
	glm_static
	lava
	lava-extras-pipeline
	lava-extras-renderer  
	imgui
	lava-extras-glfw
	lava-extras-imgui
	imguinodeeditor
	lava-extras-pack-resources
	lava-extras-geometry
	dreamroam)

add_custom_command(TARGET SampleRotatingCube POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       "${CMAKE_CURRENT_SOURCE_DIR}/assets/" $<TARGET_FILE_DIR:SampleRotatingCube>/assets/)