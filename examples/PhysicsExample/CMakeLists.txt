file(GLOB_RECURSE PHYSICSEXAMPLESOURCE "*.cc" "*.hh")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(PhysicsExample ${PHYSICSEXAMPLESOURCE})
set_target_properties(PhysicsExample PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:PhysicsExample>"
													VS_DEBUGGER_COMMAND           "$<TARGET_FILE:PhysicsExample>"
                                               		VS_DEBUGGER_ENVIRONMENT       "PATH=%PATH%;${CMAKE_PREFIX_PATH}/bin")

target_compile_options(PhysicsExample PRIVATE -Wall)
target_link_libraries(
	PhysicsExample PUBLIC
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

add_custom_command(TARGET PhysicsExample POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       "${CMAKE_CURRENT_SOURCE_DIR}/assets/" $<TARGET_FILE_DIR:PhysicsExample>/assets/)

