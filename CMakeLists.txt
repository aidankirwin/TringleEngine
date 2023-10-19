cmake_minimum_required (VERSION 3.8)

project ("Tringle")

link_directories("Tringle/vendor/lib/GLFW")

# Link external libraries
include_directories("Tringle/vendor/include/glad")
include_directories("Tringle/vendor/include/KHR")
include_directories("Tringle/vendor/include/GLFW") # This currently does not matter on mac
include_directories("Tringle/vendor/include/glm")
include_directories("Tringle/vendor/include/stb_image")
include_directories("Tringle/vendor/include/imgui")
message(STATUS "[LOG] Linked vendor includes")

# Link header files
# This is a bit hack-y
# Would in theory be "best" to manually link header files but this is easier
file(GLOB HEADERS 
	LIST_DIRECTORIES true
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/src/*
	${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src/*)

message(STATUS "[LOG] Linked header directories:")
foreach(item ${HEADERS})
	if(IS_DIRECTORY ${item})
		include_directories(${item})
		message(STATUS "[LOG] - ${item}")
	endif()
endforeach()
include_directories("Tringle/src")

# Get source files
# Same problem as headers
file(GLOB_RECURSE SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/vendor/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/vendor/*.cpp
)
add_executable(TringleApp ${SOURCES})
message(STATUS "[LOG] Linked source files:")
foreach(item ${SOURCES})
	message(STATUS "[LOG] - ${item}")
endforeach()

if(WIN32)
	# Run cmake modules to find glfw and glm
	list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(APPLE)
	# TODO: add support for x86_64 processors
	set(CMAKE_APPLE_SILICON_PROCESSOR arm)
	# Use cmake -DCMAKE_APPLE_SILICON_PROCESSOR=arm64 if this var definition fails
	target_include_directories(TringleApp PUBLIC ${OPENGL_INCLUDE_DIR})
	target_link_libraries(TringleApp  "-framework Cocoa")
	target_link_libraries(TringleApp  "-framework OpenGL")
	target_link_libraries(TringleApp  "-framework IOKit")
	target_link_libraries(TringleApp glfw ${OPENGL_gl_LIBRARY})
endif()

if(WIN32)
	target_link_libraries(TringleApp PRIVATE ${OPENGL_gl_LIBRARY})
	target_link_libraries(TringleApp PRIVATE ${GLFW3_LIBRARY})
endif()