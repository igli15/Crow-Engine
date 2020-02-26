cmake_minimum_required(VERSION 3.12)
project(Crow)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package(SFML REQUIRED COMPONENTS system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})

add_executable(Crow main.cpp Debug/Debug.cpp Debug/Debug.h Feather/Types.h Feather/EntityManager.cpp Feather/EntityManager.h Feather/ComponentArray.cpp Feather/ComponentArray.h Feather/ComponentManager.cpp Feather/ComponentManager.h Feather/System.cpp Feather/System.h Feather/SystemManager.cpp Feather/SystemManager.h Feather/Feather.cpp Feather/Feather.h Tests/FeatherTest.h "OOP Engine/Gameobject.cpp" "OOP Engine/Gameobject.h" "OOP Engine/Component.cpp" "OOP Engine/Component.h" "OOP Engine/OOPEngine.cpp" "OOP Engine/OOPEngine.h" Tests/OOPEngineTest.h)

target_link_libraries(Crow ${SFML_LIBRARIES})
