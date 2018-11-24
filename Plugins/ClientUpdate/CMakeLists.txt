project(ClientUpdate)

file(GLOB TOP_LEVEL "*.cpp" "*.h")
file(GLOB PROJECT_FILES FILES ${TOP_LEVEL})

include_directories("../../include" ".")
add_library(ClientUpdate SHARED ${PROJECT_FILES})
set_target_properties(ClientUpdate PROPERTIES FOLDER "Plugins")
set_target_properties(ClientUpdate PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../..")
target_link_libraries(ClientUpdate RealmLib)

source_group("" FILES ${TOP_LEVEL})