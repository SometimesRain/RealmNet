project(AbilityTimer)

file(GLOB TOP_LEVEL "*.cpp" "*.h")
file(GLOB PROJECT_FILES FILES ${TOP_LEVEL})

include_directories("../../include" ".")
add_library(AbilityTimer SHARED ${PROJECT_FILES})
set_target_properties(AbilityTimer PROPERTIES FOLDER "Plugins")
set_target_properties(AbilityTimer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../..")
target_link_libraries(AbilityTimer RealmLib)

source_group("" FILES ${TOP_LEVEL})