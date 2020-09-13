cmake_minimum_required(VERSION 3.3)
###Set the path to gdcm. GDCM won't be in the default locations and it's location changes due to OS+Arch and Debug/Release.

if(ANDROID_ABI)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message(STATUS "gdcm android arm64 DEBUG")
        SET(GDCM_PATH "C:/programacao/build-GDCM-Android_Qt_5_15_1_Clang_Multi_Abi-Debug")
        SET(GDCM_LIB_LIST gdcmcharls gdcmCommon gdcmDICT gdcmDSED gdcmexpat gdcmIOD gdcmjpeg12 gdcmjpeg16 gdcmjpeg8  gdcmMEXD gdcmMSFF gdcmopenjp2 gdcmuuid gdcmzlib socketxx)
    endif()
    if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        message(STATUS "gdcm android arm64 RELEASE")
        SET(GDCM_PATH "C:/programacao/build-GDCM-Android_Qt_5_15_1_Clang_Multi_Abi-Release")
        SET(GDCM_LIB_LIST gdcmcharls gdcmCommon gdcmDICT gdcmDSED gdcmexpat gdcmIOD gdcmjpeg12 gdcmjpeg16 gdcmjpeg8  gdcmMEXD gdcmMSFF gdcmopenjp2 gdcmuuid gdcmzlib socketxx)

    endif()
elseif(WIN32)
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message(STATUS "gdcm Win32 DEBUG")
        SET(GDCM_PATH "C:/programacao/build-GDCM-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug")
        SET(GDCM_LIB_LIST gdcmcharls gdcmCommon gdcmDICT gdcmDSED gdcmexpat gdcmIOD gdcmjpeg12 gdcmjpeg16 gdcmjpeg8  gdcmMEXD gdcmMSFF gdcmopenjp2 gdcmzlib socketxx)
    endif()
    if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
        message(STATUS "gdcm Win32 RELEASE")
        SET(GDCM_PATH "C:/programacao/build-GDCM-Desktop_Qt_5_15_1_MSVC2019_64bit-Release")
        SET(GDCM_LIB_LIST gdcmcharls gdcmCommon gdcmDICT gdcmDSED gdcmexpat gdcmIOD gdcmjpeg12 gdcmjpeg16 gdcmjpeg8  gdcmMEXD gdcmMSFF gdcmopenjp2 gdcmzlib socketxx)
    endif()
endif()


###Finds GDCM - it should be in GDCM_PATH and since GDCM_LIBRARIES is empty I must specify which libs I want.
find_package(GDCM
    REQUIRED
    NO_DEFAULT_PATH
    PATHS ${GDCM_PATH}
    COMPONENTS  ${GDCM_LIB_LIST})
###Defines the project
project (tomographer)
###Defines the sources
set (SOURCES
    src/tomographer.cpp
    src/LibraryContext.cpp
    src/findAllDicomsInPath.cpp
    src/gdcmUtils.cpp
    src/stringUtils.cpp
    src/datasetUtils.cpp
    src/readDicoms.cpp)
###Defines the library
add_library(tomographer SHARED ${SOURCES})
#Add the includes to the project
target_include_directories(tomographer PRIVATE ${PROJECT_SOURCE_DIR}/includes)
#Add GDCM includes to the project
target_include_directories(tomographer PRIVATE ${GDCM_INCLUDE_DIRS})
#Add GDCM libs to the project
target_link_libraries(tomographer PRIVATE ${GDCM_LIB_LIST})

add_executable(tester ${SOURCES})
target_include_directories(tester PRIVATE ${PROJECT_SOURCE_DIR}/includes)
target_include_directories(tester PRIVATE ${GDCM_INCLUDE_DIRS})
target_link_libraries(tester PRIVATE ${GDCM_LIB_LIST})

#Print all vars
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
