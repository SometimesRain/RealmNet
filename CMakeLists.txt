cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(RealmNet)
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS true)
set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

add_subdirectory(RealmLib)
add_subdirectory(RealmNet)

add_subdirectory(Plugins/AbilityTimer)
add_subdirectory(Plugins/AntiLag)
add_subdirectory(Plugins/ClientUpdate)
add_subdirectory(Plugins/Resend)
add_subdirectory(Plugins/Welcome)

add_subdirectory(RealmXml)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT RealmNet)