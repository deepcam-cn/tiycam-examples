#THESE VAR should be setted like this:
#cmake -DCROSS_COMPILE=arm-linux-
#CROSS_COMPILE compiler prefix, such as "arm-linux-"

cmake_minimum_required (VERSION 2.6)
# CLDFLAGS is FLAGS that both needed by CC and LD. 
set(CROSS_COMPILE arm-linux-gnueabihf-)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc ${CLDFLAGS})
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++ ${CLDFLAGS})

SET(PROJECTNAME DEMO)
PROJECT (${PROJECTNAME})
set(TOP_BINARY_DIR ${${PROJECTNAME}_BINARY_DIR})
set(TOP_SOURCE_DIR ${${PROJECTNAME}_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${TOP_SOURCE_DIR}/ipk/Hello_RV1126_Linux/usr/bin/)

MESSAGE(STATUS "This is BINARY dir " ${TOP_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${TOP_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX is " ${CMAKE_INSTALL_PREFIX})
MESSAGE(STATUS "INCLUDE_BASE_PATH is " ${INCLUDE_BASE_PATH})
MESSAGE(STATUS "LINK_LIB_PATH is " ${LINK_LIB_PATH})
MESSAGE(STATUS "CMAKE_C_COMPILER is " ${CMAKE_C_COMPILER})
MESSAGE(STATUS "CMAKE_SYSROOT is " ${CMAKE_SYSROOT})

execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpmachine OUTPUT_VARIABLE CMAKE_C_COMPILER_MACHINE)
if(NOT CMAKE_C_COMPILER_MACHINE MATCHES ".*-linux-gnu")
    message(STATUS "Using non-glibc toolchain")
    set(LIBINTL intl)
endif()

add_definitions(${C_CXX_FLAGS})
SET(CMAKE_SHARED_LINKER_FLAGS "${C_CXX_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${C_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_definitions(-Os -g)
add_definitions(-Wall -Wstack-protector -Wtrampolines -Wfloat-equal -Wstrict-overflow=5 -Wformat=0 -Wpointer-arith)
add_definitions(-Wno-strict-aliasing -Wno-format-truncation -Wno-psabi -Wno-unused-function -Wno-cpp -Wno-cast-qual -Wno-strict-overflow)
add_definitions(-fPIC -fstack-protector-all -pipe -funwind-tables -ffunction-sections -fdata-sections)

ADD_SUBDIRECTORY(src)