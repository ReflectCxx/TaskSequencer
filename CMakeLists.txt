cmake_minimum_required(VERSION 3.16)
project(TaskSequencer LANGUAGES CXX)

add_library(TaskSequencer INTERFACE)
add_library(TaskSequencer::TaskSequencer ALIAS TaskSequencer)
target_compile_features(TaskSequencer INTERFACE cxx_std_17)
target_include_directories(TaskSequencer INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/TaskSequencer>
    $<INSTALL_INTERFACE:include>)

option(TASKSEQUENCER_BUILD_EXAMPLE "Build the example" ON)
if(TASKSEQUENCER_BUILD_EXAMPLE)
    add_executable(TSeqTests test-main/main.cpp)
    target_link_libraries(TSeqTests PRIVATE TaskSequencer::TaskSequencer)
endif()

include(GNUInstallDirs)
install(TARGETS TaskSequencer EXPORT TaskSequencerTargets)
install(DIRECTORY TaskSequencer/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/TaskSequencer FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
install(EXPORT TaskSequencerTargets NAMESPACE TaskSequencer:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TaskSequencer)
