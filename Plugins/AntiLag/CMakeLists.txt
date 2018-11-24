project(AntiLag)

file(GLOB TOP_LEVEL "*.cpp" "*.h")
file(GLOB PROJECT_FILES FILES ${TOP_LEVEL})

include_directories("../../include" ".")
add_library(AntiLag SHARED ${PROJECT_FILES})
set_target_properties(AntiLag PROPERTIES FOLDER "Plugins")
target_link_libraries(AntiLag RealmLib)

source_group("" FILES ${TOP_LEVEL})