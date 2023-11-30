# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "ArtfulWall_autogen"
  "CMakeFiles\\ArtfulWall_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ArtfulWall_autogen.dir\\ParseCache.txt"
  )
endif()
