# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AlgoVisualizer_autogen"
  "CMakeFiles\\AlgoVisualizer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AlgoVisualizer_autogen.dir\\ParseCache.txt"
  )
endif()
