cmake_minimum_required(VERSION 3.12)
project(Crow)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package (OpenGL REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(spdlog REQUIRED)
find_package(GLM REQUIRED)
find_package(assimp REQUIRED)

find_library(COCOA_LIBRARY Cocoa REQUIRED)
find_library(IOKIT_LIBRARY IOKit REQUIRED)
find_library(COREVID_LIBRARY CoreVideo REQUIRED)

find_library(libIrrXML Required)
find_library(libassimp.5.0.0 Required)
find_library(libassimp.5 Required)
find_library(libassimp Required)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${spdlog_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})

add_executable(Crow main.cpp Debug/Debug.cpp Debug/Debug.h Feather/Types.h Feather/EntityManager.cpp Feather/EntityManager.h Feather/ComponentArray.cpp Feather/ComponentArray.h Feather/ComponentManager.cpp Feather/ComponentManager.h Feather/System.cpp Feather/System.h Feather/SystemManager.cpp Feather/SystemManager.h Feather/World.cpp Feather/World.h Tests/FeatherTest.h "OOP Engine/Gameobject.cpp" "OOP Engine/Gameobject.h" "OOP Engine/Component.cpp" "OOP Engine/Component.h" "OOP Engine/OOPEngine.cpp" "OOP Engine/OOPEngine.h" Tests/OOPEngineTest.h Feather/EntityHandle.cpp Feather/EntityHandle.h Feather/ComponentHandle.cpp Feather/ComponentHandle.h Rendering/Window.cpp Rendering/Window.h Feather/CustomTypeID.h Core/Game.cpp Core/Game.h SandBox/MainWorld.cpp SandBox/MainWorld.h SandBox/Systems/TestSystem.cpp SandBox/Systems/TestSystem.h Rendering/Shader.cpp Rendering/Shader.h Plugins/stb_image.h Plugins/stb_image.cpp Core/ResourceLoader.cpp Core/ResourceLoader.h Rendering/Texture.cpp Rendering/Texture.h Crow.h Rendering/Mesh.cpp Rendering/Mesh.h Rendering/Model.cpp Rendering/Model.h)

target_link_libraries(Crow ${GLFW_LIBRARIES})
target_link_libraries(Crow ${spdlog_LIBRARIES})
target_link_libraries(Crow ${GLM_LIBRARIES})
target_link_libraries(Crow ${assimp_LIBRARIES})
target_link_libraries(Crow ${libIrrXML_LIBRARY} ${libassimp.5.0.0_LIBRARY} ${libassimp.5_LIBRARY} ${libassimp_LIBRARY})
target_link_libraries(Crow ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY} )

