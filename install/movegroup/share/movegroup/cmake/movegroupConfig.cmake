# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_movegroup_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED movegroup_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(movegroup_FOUND FALSE)
  elseif(NOT movegroup_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(movegroup_FOUND FALSE)
  endif()
  return()
endif()
set(_movegroup_CONFIG_INCLUDED TRUE)

# output package information
if(NOT movegroup_FIND_QUIETLY)
  message(STATUS "Found movegroup: 0.0.0 (${movegroup_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'movegroup' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${movegroup_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(movegroup_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${movegroup_DIR}/${_extra}")
endforeach()
