if (UNIX AND NOT APPLE)
    macro( FIND_LIBGIT2_OFFICIAL )
        find_library(LIBGIT2_T
                     NAMES libgit2.so
                     HINTS  
                     /usr/lib 
                     /usr/local/lib 
                     ${CMAKE_INSTALL_LIBDIR})

        find_path(LIBGIT2_INCLUDE_T NAMES git2.h
                  HINTS 
                  /usr/include
                  /usr/local/include
                  )

        if ( LIBGIT2_T STREQUAL "LIBGIT2_T-NOTFOUND" OR LIBGIT2_INCLUDE_T STREQUAL "LIBGIT2_INCLUDE_T-NOTFOUND" )
            set(LINSSH2_LIBRARY "LIBGIT2-NOTFOUND")
            set(LIBGIT2_INCLUDE "LIBGIT2_INCLUDE-NOTFOUND")
            set(LIBGIT2_OFFICIAL_FOUND 0 )
            message(FATAL_ERROR "-- *** Could not find libgit2 ***")
        else()
            set(LIBGIT2_OFFICIAL_FOUND 1 )
            set(LIBGIT2_LIBRARY ${LIBGIT2_T})
            set(LIBGIT2_INCLUDE ${LIBGIT2_INCLUDE_T})
            set(LIBGIT2_INSTALL_NEEDED 0)
        endif()
    endmacro()
endif()

FIND_LIBGIT2_OFFICIAL()