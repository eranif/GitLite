if (UNIX AND NOT APPLE)
    macro( FIND_LIBSSH2_OFFICIAL )
        find_library(LIBSSH2_T
                     NAMES libssh2.so
                     HINTS  
                     /usr/lib 
                     /usr/local/lib 
                     ${CMAKE_INSTALL_LIBDIR})

        find_path(LIBSSH2_INCLUDE_T NAMES libssh2.h
                  HINTS 
                  /usr/include
                  /usr/local/include
                  )

        if ( LIBSSH2_T STREQUAL "LIBSSH2_T-NOTFOUND" OR LIBSSH2_INCLUDE_T STREQUAL "LIBSSH2_INCLUDE_T-NOTFOUND" )
            set(LIBSSH2 "LIBSSH2-NOTFOUND")
            set(LIBSSH2_INCLUDE "LIBSSH2_INCLUDE-NOTFOUND")
            set(LIBSSH2_OFFICIAL_FOUND 0 )
        else()
            set(LIBSSH2_OFFICIAL_FOUND 1 )
            set(LIBSSH2 ${LIBSSH2_T})
            set(LIBSSH2_INCLUDE ${LIBSSH2_INCLUDE_T})
            set(LIBSSH2_INSTALL_NEEDED 0)
        endif()
    endmacro()
endif()
