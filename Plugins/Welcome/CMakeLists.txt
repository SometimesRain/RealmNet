project(Welcome)

file(GLOB TOP_LEVEL "*.cpp" "*.h")
file(GLOB PROJECT_FILES FILES ${TOP_LEVEL})

include_directories("../../include" ".")
add_library(Welcome SHARED ${PROJECT_FILES})
set_target_properties(Welcome PROPERTIES FOLDER "Plugins")
target_link_libraries(Welcome RealmLib)

source_group("" FILES ${TOP_LEVEL})