# algorithms-c/CMakeLists.txt
#
# Usage:
# cmake ..
# make
#

cmake_minimum_required (VERSION 2.8)

project (algorithms-c C)

include(GNUInstallDirs ${PROJECT_SOURCE_DIR})

# Folder alias
set (SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Set the include directories
include_directories(/usr/include ${SRC_DIR})

# TODO -- make into lib

# Build the examples
subdirs(examples)
