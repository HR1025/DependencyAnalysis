cmake_minimum_required(VERSION 3.5)
project(DependencyAnalysis)

# import poco from source (static)
set(BUILD_SHARED_LIBS NO)
add_subdirectory(SubMoudule/poco)

# environment
set(SRCS)
set(INCS)
list(APPEND INCS ${CMAKE_CURRENT_SOURCE_DIR}/inc)
list(APPEND SRCS 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ObjdumpHelper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FileSearch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DependencyCache.cpp
)

# generate Executable
add_executable(DependencyAnalysis ${SRCS})
target_include_directories(DependencyAnalysis PUBLIC ${INCS})
target_include_directories(DependencyAnalysis PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_link_libraries(DependencyAnalysis Poco::Foundation Poco::Foundation Poco::Util Poco::JSON)

