﻿cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 20)

project ("FaunaExplorer")

file (GLOB SRCS ${CMAKE_CURRENT_LIST_DIR}/srcs/*.cpp)
set (GLAD_SRCS ${CMAKE_CURRENT_LIST_DIR}/glad/src/glad.c)
set (STBI_SRCS ${CMAKE_CURRENT_LIST_DIR}/stbi/src/stb_image.cpp)

set (INCL ${CMAKE_CURRENT_LIST_DIR}/incl)
set (GLFW_INCL ${CMAKE_CURRENT_LIST_DIR}/glfw/include/)
set (GLAD_INCL ${CMAKE_CURRENT_LIST_DIR}/glad/include/)
set (GLM_INCL ${CMAKE_CURRENT_LIST_DIR}/glm/)
set (STBI_INCL ${CMAKE_CURRENT_LIST_DIR}/stbi/include/)
set (ASSIMP_INCL ${CMAKE_CURRENT_LIST_DIR}/assimp/include/)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/brick.jpg
   ${CMAKE_CURRENT_BINARY_DIR}/brick.jpg COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/models/dog_image.obj
   ${CMAKE_CURRENT_BINARY_DIR}/models/dog_image.obj COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/models/dog_image.mtl
${CMAKE_CURRENT_BINARY_DIR}/models/dog_image.mtl COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/models/diffuse.jpeg
${CMAKE_CURRENT_BINARY_DIR}/models/diffuse.jpeg COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/models/cube.obj
   ${CMAKE_CURRENT_BINARY_DIR}/models/cube.obj COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/models/cube.mtl
${CMAKE_CURRENT_BINARY_DIR}/models/cube.mtl COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.vertex
    ${CMAKE_CURRENT_BINARY_DIR}/shaders/default.vertex COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.fragment
    ${CMAKE_CURRENT_BINARY_DIR}/shaders/default.fragment COPYONLY)

add_subdirectory(glfw)
add_subdirectory(assimp)

add_executable (FaunaExplorer ${SRCS} ${GLAD_SRCS} ${STBI_SRCS})

target_link_libraries(FaunaExplorer PUBLIC glfw assimp)

target_include_directories(FaunaExplorer PUBLIC ${INCL} ${GLFW_INCL} ${GLAD_INCL} ${GLM_INCL} ${STBI_INCL})