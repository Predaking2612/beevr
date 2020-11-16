
get_filename_component (ROOT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

set (BV_ROOT_DIR ${ROOT_DIRECTORY} CACHE INTERNAL "Beevr source root")
set (BV_INCLUDE_DIR ${BV_ROOT_DIR}/src/include CACHE INTERNAL "Beevr include root")
set (BV_ROOT_SRC_DIR ${BV_ROOT_DIR}/src CACHE INTERNAL "Beevr src root")

