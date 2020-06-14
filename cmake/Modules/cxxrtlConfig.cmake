INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CXXRTL cxxrtl)

FIND_PATH(
    CXXRTL_INCLUDE_DIRS
    NAMES cxxrtl/api.h
    HINTS $ENV{CXXRTL_DIR}/include
        ${PC_CXXRTL_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CXXRTL_LIBRARIES
    NAMES gnuradio-cxxrtl
    HINTS $ENV{CXXRTL_DIR}/lib
        ${PC_CXXRTL_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/cxxrtlTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CXXRTL DEFAULT_MSG CXXRTL_LIBRARIES CXXRTL_INCLUDE_DIRS)
MARK_AS_ADVANCED(CXXRTL_LIBRARIES CXXRTL_INCLUDE_DIRS)
