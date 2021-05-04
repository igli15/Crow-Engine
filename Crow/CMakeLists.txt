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
find_package(Freetype REQUIRED)
find_package(SFML REQUIRED)

find_library(COCOA_LIBRARY Cocoa REQUIRED)
find_library(IOKIT_LIBRARY IOKit REQUIRED)
find_library(COREVID_LIBRARY CoreVideo REQUIRED)
find_library(FREETYPE REQUIRED)

find_library(libIrrXML Required)
find_library(libassimp.5.0.0 Required)
find_library(libassimp.5 Required)
find_library(libassimp Required)

find_package(SFML COMPONENTS audio)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${spdlog_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIR_freetype2})
include_directories(${FREETYPE_INCLUDE_DIR_ft2build})
include_directories(${SFML_INCLUDE_DIR})

add_executable(Crow main.cpp Engine/Debug/Debug.cpp Engine/Debug/Debug.h Engine/Feather/Types.h Engine/Feather/EntityRegistry.cpp Engine/Feather/EntityRegistry.h Engine/Feather/ComponentRegistry.cpp Engine/Feather/ComponentRegistry.h Engine/Feather/System.cpp Engine/Feather/System.h Engine/Feather/SystemRegistry.cpp Engine/Feather/SystemRegistry.h Engine/Feather/World.cpp Engine/Feather/World.h  "OOP Engine/Gameobject.cpp" "OOP Engine/Gameobject.h" Engine/Feather/EntityHandle.cpp Engine/Feather/EntityHandle.h Engine/Rendering/Window.cpp Engine/Rendering/Window.h Engine/Feather/CustomTypeID.h Engine/Core/Game.cpp Engine/Core/Game.h Engine/Rendering/Shader.cpp Engine/Rendering/Shader.h Plugins/stb_image.h Plugins/stb_image.cpp Engine/Core/ResourceManager.cpp Engine/Core/ResourceManager.h Engine/Rendering/Texture.cpp Engine/Rendering/Texture.h Crow.h Engine/Rendering/Mesh.cpp Engine/Rendering/Mesh.h Engine/Rendering/Model.cpp Engine/Rendering/Model.h Engine/Components/Camera.cpp Engine/Components/Camera.h Engine/Components/Transform.cpp Engine/Components/Transform.h Engine/Components/MeshInfo.h Engine/Rendering/AbstractMaterial.cpp Engine/Rendering/AbstractMaterial.h Engine/Rendering/Materials/TranslucentColorMat.h Engine/Rendering/Materials/TranslucentColorMat.cpp SandBox/MyGame.cpp SandBox/MyGame.h Engine/Components/Light.h SandBox/Worlds/TranslucentMaterialTestWorld.cpp SandBox/Worlds/TranslucentMaterialTestWorld.h Engine/EventQueue/Event.h Engine/EventQueue/EventQueue.cpp Engine/EventQueue/EventQueue.h Engine/EventQueue/MemberFunctionHandler.cpp Engine/EventQueue/MemberFunctionHandler.h SandBox/Components/MoveComponent.cpp SandBox/Components/MoveComponent.h Engine/Components/SphereCollider.h Engine/Systems/CollisionDetectionSystem.cpp Engine/Systems/CollisionDetectionSystem.h Engine/Events/CollisionEvent.h Engine/Events/CollisionEnterEvent.h Engine/Events/CollisionExitEvent.h Engine/Systems/TransformHierarchySystem.cpp Engine/Systems/TransformHierarchySystem.h Engine/Events/EntityEvents.h Engine/Events/ComponentAddedEvent.h SandBox/Worlds/XmlTestWorld.cpp SandBox/Worlds/XmlTestWorld.h Engine/Core/Input.cpp Engine/Core/Input.h Engine/Components/Text.h Engine/Systems/TextRenderingSystem.cpp Engine/Systems/TextRenderingSystem.h Engine/Rendering/Font.cpp Engine/Rendering/Font.h Engine/Systems/MeshRendererSystem.cpp Engine/Systems/MeshRendererSystem.h Engine/Rendering/Materials/ColorMaterial.cpp Engine/Rendering/Materials/ColorMaterial.h Engine/Components/SpriteInfo.h Engine/Rendering/Materials/SpriteMaterial.cpp Engine/Rendering/Materials/SpriteMaterial.h Engine/Rendering/Sprite.cpp Engine/Rendering/Sprite.h Engine/Systems/SpriteRendererSystem.cpp Engine/Systems/SpriteRendererSystem.h SandBox/Worlds/SpriteRenderingWorld.cpp SandBox/Worlds/SpriteRenderingWorld.h Engine/Core/Renderer.cpp Engine/Core/Renderer.h Engine/Events/ComponentRemovedEvent.h Engine/Editor/UnitySceneParser.cpp Engine/Editor/UnitySceneParser.h Engine/Events/MeshInfoDirtyEvent.h Engine/Rendering/Materials/TextureMaterial.cpp Engine/Rendering/Materials/TextureMaterial.h Engine/Components/Rigidbody.cpp Engine/Components/Rigidbody.h Engine/Utils/Random.cpp Engine/Utils/Random.h Engine/Rendering/Materials/WaterMaterial.cpp Engine/Rendering/Materials/WaterMaterial.h Engine/Core/AssetParser.h Engine/Rendering/Materials/PortalMaterial.cpp Engine/Rendering/Materials/PortalMaterial.h Engine/Rendering/Materials/UnlitMaterial.cpp Engine/Rendering/Materials/UnlitMaterial.h Engine/Events/OnUnitDefeatedEvent.h Engine/Feather/ComponentSparseSet.cpp Engine/Feather/ComponentSparseSet.h Engine/Feather/IComponentSet.h Engine/Feather/Benchmark.h Engine/Feather/Pool.h Engine/Rendering/Materials/HealthBarMaterial.cpp Engine/Rendering/Materials/HealthBarMaterial.h Engine/Components/AudioSource.h Engine/Components/AudioListener.h Engine/Systems/AudioListenerSystem.cpp Engine/Systems/AudioListenerSystem.h Engine/Systems/AudioSourceSystem.cpp Engine/Systems/AudioSourceSystem.h)

target_link_libraries(Crow ${GLFW_LIBRARIES})
target_link_libraries(Crow ${spdlog_LIBRARIES})
target_link_libraries(Crow ${GLM_LIBRARIES})
target_link_libraries(Crow ${assimp_LIBRARIES})
target_link_libraries(Crow ${libIrrXML_LIBRARY} ${libassimp.5.0.0_LIBRARY} ${libassimp.5_LIBRARY} ${libassimp_LIBRARY})
target_link_libraries(Crow ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${COCOA_LIBRARY} ${COREVID_LIBRARY} ${IOKIT_LIBRARY} )
target_link_libraries(Crow ${FREETYPE_LIBRARIES})
target_link_libraries(Crow ${SFML_LIBRARIES})
