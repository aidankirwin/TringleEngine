cmake_minimum_required (VERSION 3.8)

project ("Tringle")

if(APPLE)
	set(CMAKE_CXX_STANDARD 11)
endif()

link_directories("Tringle/vendor/lib/GLFW")
link_directories("Tringle/vendor/lib/assimp")

# Link external libraries
include_directories("Tringle/vendor/include")
include_directories("Tringle/vendor/include/glad")
include_directories("Tringle/vendor/include/KHR")
include_directories("Tringle/vendor/include/GLFW")
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

# Get shader files
file(GLOB_RECURSE SHADERS
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/assets/*.vert
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/assets/*.frag
	${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/assets/*.vert
	${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/assets/*.frag
)
file(COPY ${SHADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "[LOG] Copied shaders to binary directory:")
foreach(item ${SHADERS})
	message(STATUS "[LOG] - ${item}")
endforeach()

# Get texture files
# Support only jpeg for now
file(GLOB_RECURSE TEXTURES
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/assets/*.jpg
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/assets/*.jpeg
	${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/assets/*.jpg
	${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/assets/*.jpeg
)
file(COPY ${TEXTURES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "[LOG] Copied textures to binary directory:")
foreach(item ${TEXTURES})
	message(STATUS "[LOG] - ${item}")
endforeach()

# Get model files
file(GLOB_RECURSE MODELS
	${CMAKE_CURRENT_SOURCE_DIR}/Tringle/assets/*.obj
	${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/assets/*.obj
)
file(COPY ${MODELS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "[LOG] Copied models to binary directory:")
foreach(item ${MODELS})
	message(STATUS "[LOG] - ${item}")
endforeach()

# Run cmake modules to find glfw and assimp
if(WIN32)
	list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(ASSIMP REQUIRED)

if(APPLE)
	# TODO: add support for x86_64 processors
	set(CMAKE_APPLE_SILICON_PROCESSOR arm)
	# Use cmake -DCMAKE_APPLE_SILICON_PROCESSOR=arm64 if this var definition fails
	target_include_directories(TringleApp PUBLIC ${OPENGL_INCLUDE_DIR})
	target_link_libraries(TringleApp  "-framework Cocoa")
	target_link_libraries(TringleApp  "-framework OpenGL")
	target_link_libraries(TringleApp  "-framework IOKit")
	target_link_libraries(TringleApp glfw ${OPENGL_gl_LIBRARY})
	target_link_libraries(TringleApp assimp ${ASSIMP_LIBRARY})
endif()

if(WIN32)
	target_link_libraries(TringleApp PRIVATE ${OPENGL_gl_LIBRARY})
	target_link_libraries(TringleApp PRIVATE ${GLFW3_LIBRARY})
	target_link_libraries(TringleApp PRIVATE ${ASSIMP_LIBRARY})
endif()