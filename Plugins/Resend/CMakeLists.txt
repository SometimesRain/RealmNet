project(Resend)

file(GLOB TOP_LEVEL "*.cpp" "*.h")
file(GLOB PROJECT_FILES FILES ${TOP_LEVEL})

include_directories("../../include" ".")
add_library(Resend SHARED ${PROJECT_FILES})
set_target_properties(Resend PROPERTIES FOLDER "Plugins")
set_target_properties(Resend PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../..")
target_link_libraries(Resend RealmLib)

source_group("" FILES ${TOP_LEVEL})