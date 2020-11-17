#ifndef _BEEVR_CLI_PARSE_H_
#define _BEEVR_CLI_PARSE_H_

#include "bstring.h"
#include <stdbool.h>

typedef struct __cli_parse cliparse;
typedef struct __cli_container clicontainer;

struct __cli_container {
	const bstring *arg;
	const bstring *long_name;
	const bstring *help;
	char short_name;

	const bstring *val_name;
	const bstring *value;
	bool takes_value;
	int size;
};

struct __cli_parse {
	const bstring *prgm_name;
	const bstring *version;
	const bstring *author;
	const bstring *about;
	struct __cli_container *args[16];
	unsigned int args_size;
};

clicontainer *create_args(const char *arg,
						  const char *long_name,
						  const char *help,
						  const char *val_name,
						  const char *value,
						  char short_name,
						  bool takes_value);

cliparse *
create_cliargs(const char *prgm_name, const char *version, const char *author, const char *about);

clicontainer **cliparse_parse(int argc, const char **argv, cliparse *parse);

char *clicontainer_match(const char *str, const clicontainer **container);

void clicontainer_free(clicontainer *container);

void cliparse_print_menu(const cliparse *parse);

void cliparse_free(cliparse *parse);

void cliparse_push_back(cliparse *parse, clicontainer *container);

#endif // _BEEVR_CLI_PARSE_H_
