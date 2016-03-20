cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(GitLiteLib)

find_package(wxWidgets COMPONENTS std REQUIRED)
include( "${wxWidgets_USE_FILE}" )

# Include paths
include_directories(${LIBSSH2_INCLUDE})
include_directories(${LIBGIT2_INCLUDE_INCLUDE})

FILE(GLOB SRCS "*.cpp")

add_library(GitLiteLib SHARED ${SRCS})
target_link_libraries(GitLiteLib 
                        ${LIBSSH2_LIBRARY}
                        ${LIBGIT2_LIBRARY})


