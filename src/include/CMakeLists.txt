
set (TARGET_LIB BvrLib)

add_library (${TARGET_LIB}
		STATIC
		cli_parse.c
		bstring.c)

