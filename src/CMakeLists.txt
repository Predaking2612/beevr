
set (beevr_executable beevr)
add_subdirectory (include)

include_directories (${BV_ROOT_SRC_DIR})
add_executable (${beevr_executable}
				main.c)

target_link_libraries (${beevr_executable}
				PUBLIC
				BvrLib)
