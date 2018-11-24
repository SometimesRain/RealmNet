project(RealmXml)

file(GLOB TOP_LEVEL "*.cpp" "*.h")
file(GLOB SRC_HTTPS "./Https/*.cpp" "./Https/*.h")
file(GLOB SRC_PARSER "./Parser/*.cpp" "./Parser/*.h")
file(GLOB SRC_UTIL "./Util/*.cpp" "./Util/*.h")
file(GLOB PROJECT_FILES FILES ${TOP_LEVEL} ${SRC_HTTPS} ${SRC_PARSER} ${SRC_UTIL})

if(MSVC)
    foreach(src_file ${PROJECT_FILES})
        set_source_files_properties(${src_file} PROPERTIES COMPILE_FLAGS "/Yustdafx.h")
    endforeach(src_file ${PROJECT_FILES})
    set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")
endif(MSVC)

include_directories("../include" ".")
add_executable(RealmXml ${PROJECT_FILES})
target_link_libraries(RealmXml RealmLib)

source_group("Https" FILES ${SRC_HTTPS})
source_group("Parser" FILES ${SRC_PARSER})
source_group("Util" FILES ${SRC_UTIL})
source_group("" FILES ${TOP_LEVEL})