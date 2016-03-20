cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(GitLite)

find_package(wxWidgets COMPONENTS std stc REQUIRED)
include( "${wxWidgets_USE_FILE}" )

FILE(GLOB SRCS "*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/GitLiteLib)
add_executable(GitLite ${SRCS})
target_link_libraries(GitLite GitLiteLib ${wxWidgets_LIBRARIES})