#include "cli_parse.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

cliparse *
create_cliargs(const char *prgm_name, const char *version, const char *author, const char *about) {

	cliparse *retval;
	retval = malloc(sizeof *retval);
	assert(retval != NULL &&
		   "Error: *create_cliargs failed to allocate memory for the return value.");

	retval->prgm_name = bstring_new(prgm_name);
	retval->version	  = bstring_new(version);
	retval->author	  = bstring_new(author);
	retval->about	  = bstring_new(about);

	return retval;
}

clicontainer *create_args(const char *arg,
						  const char *long_name,
						  const char *help,
						  const char *val_name,
						  const char *value,
						  char short_name,
						  bool takes_value) {

	clicontainer *retval;

	retval = malloc(sizeof *retval);
	assert(retval != NULL && "Error: *create_args failed to allocate memory for the return value");

	retval->arg		  = bstring_new(arg);
	retval->long_name = bstring_new(long_name);
	retval->help	  = bstring_new(help);

	retval->val_name	= bstring_new(val_name);
	retval->value		= bstring_new(value);
	retval->short_name	= short_name;
	retval->takes_value = takes_value;

	return retval;
}

static const char *substr(const char *str, unsigned int begin, unsigned int end) {

	unsigned int len;
	char *retval;

	len	   = (unsigned int)(end - begin);
	retval = malloc(len);
	strncpy(retval, str + begin, end);

	return (const char *)retval;
}

static bool strmch(const char *str, const cliparse *parse) {

	for (unsigned int i = 0; i < parse->args_size; i++) {
		const char *s = parse->args[i]->long_name->str;
		if (bstring_cequal(str, s))
			return true;
	}

	return false;
}

static bool short_match(char ch, const cliparse *parse) {

	for (unsigned int i = 0; i < parse->args_size; i++) {
		char ch1 = parse->args[i]->short_name;
		if (ch1 == ch)
			return true;
	}
	return false;
}

static const char *get_next_arg(int argc, const char **argv, const cliparse *parse) {

	if (argv[argc + 1])
		return argv[argc + 1];
	else {
		cliparse_print_menu(parse);
		exit(-1);
	}
}

static clicontainer *create_clicontainer() {

	clicontainer *retval;

	retval = malloc(sizeof *retval + sizeof *retval);
	assert(retval != NULL &&
		   "Error: *create_clicontainer failed to allocate memory for the retval.");

	return retval;
}

clicontainer **cliparse_parse(int argc, const char **argv, cliparse *parse) {

	if (argc <= 1) {
		cliparse_print_menu(parse);
		exit(-1);
	}

	int index = 0;
	clicontainer **retval;

	for (int i = 1; i < argc; i++) {
		const char *larg;
		char sarg;

		if (argv[i][0] == '-' && argv[i][1] == '-') {
			unsigned int len = (unsigned int)strlen(argv[i]);

			if (len - 2 >= 1) {
				larg = substr(argv[i], 2, len);
				if (strmch(larg, parse)) {

					retval[index++]		   = create_clicontainer();
					retval[index - 1]->arg = bstring_new(larg);

					if (parse->args[i]->takes_value)
						retval[index - 1]->value = bstring_new(get_next_arg(i, argv, parse));
					else
						retval[index - 1]->value = bstring_new(larg);

				} else if (strcmp(larg, "version") == 0) {

					fprintf(stderr, "%s\nVersion: %s\n", bstring_get_value(parse->prgm_name),
							bstring_get_value(parse->version));
					exit(-1);
				} else if (strcmp(larg, "help") == 0) {

					cliparse_print_menu(parse);
					exit(-1);
				} else {

					fprintf(stderr, "[parsing error]: invalid argument value: %s\n", larg);
					cliparse_print_menu(parse);
					exit(-1);
				}
			} else {

				fprintf(stderr, "[parsing error]: required value after '--'\n");
				cliparse_print_menu(parse);
				exit(-1);
			}
		} else if (argv[i][0] == '-' && argv[i][1] != '-' && isalnum(argv[i][1])) {

			sarg = argv[i][1];
			if (short_match(sarg, parse)) {

				retval[index++]		   = create_clicontainer();
				retval[index - 1]->arg = bstring_new(&argv[i + 1][0]);

				if (parse->args[i]->takes_value && argv[i + 1][0] != '-')
					retval[index - 1]->value = bstring_new(get_next_arg(i, argv, parse));
				else
					retval[index - 1]->value = bstring_new(&argv[i + 1][0]);
			} else if (sarg == 'v') {

				fprintf(stderr, "%s\nVersion: %s\n", bstring_get_value(parse->prgm_name),
						bstring_get_value(parse->version));
				exit(-1);
			} else if (sarg == 'h') {

				cliparse_print_menu(parse);
				exit(-1);
			} else {

				fprintf(stderr, "[parsing error]: invalid argument value: %c\n", sarg);
				cliparse_print_menu(parse);
				exit(-1);
			}
		} else {

			fprintf(stderr, "[parsing error]: required arguments after 'beevr'\n");
			cliparse_print_menu(parse);
			exit(-1);
		}
	}

	retval[0]->size = index;
	return retval;
}

char *clicontainer_match(const char *str, const clicontainer **container) {

	char *retval;
	int index = container[0]->size;

	for (int i = 0; i < index; i++) {
		char *val = bstring_get_value(container[i]->arg);
		if (strcmp(str, val) == 0)
			retval = val;
	}

	assert((retval != NULL) && "[Search-Arg Error]: failed to find the search value");
	return retval;
}

void cliparse_print_menu(const cliparse *parse) {

	fprintf(stderr,
			"%s %s\n"
			"%s\n"	 /* Author */
			"%s\n\n" /* Description */
			"USAGE:\n\tbeevr [Flags] [Options] <Input>\n"
			"FLAGS:\n"
			"   -h, --help\t\t\t Prints this message\n"
			"   -v, --version\t\t Prints version information\n"
			"\nOPTIONS:\n",
			bstring_get_value(parse->prgm_name), bstring_get_value(parse->version),
			bstring_get_value(parse->author), bstring_get_value(parse->about));

	for (unsigned int i = 0; i < parse->args_size; i++) {

		char *val, *desc, *valnm, *nll = " ";

		valnm = bstring_get_value(parse->args[i]->val_name);
		val	  = bstring_get_value(parse->args[i]->long_name);
		desc  = bstring_get_value(parse->args[i]->help);

		fprintf(stderr, "   -%c, --%s <%s> %-8s %s\n", val[0], val, valnm, nll, desc);
	}

	fprintf(stderr, "\nARGS:\n"
					"   Input\t\t\t The input options to be used\n\n");
}

void cliparse_push_back(cliparse *parse, clicontainer *container) {

	unsigned int index = parse->args_size;
	if (index < 16)
		parse->args[index++] = container;
	parse->args_size = index;
}

void clicontainer_free(clicontainer *container) {

	bstring_delete(container->arg);
	bstring_delete(container->long_name);
	bstring_delete(container->help);
	bstring_delete(container->val_name);
	bstring_delete(container->value);
}

void cliparse_free(cliparse *parse) {

	bstring_delete(parse->prgm_name);
	bstring_delete(parse->version);
	bstring_delete(parse->author);
	bstring_delete(parse->about);

	unsigned int i = 0;
	while (i != parse->args_size) {
		clicontainer_free(parse->args[i]);
		free(parse->args[i++]);
	}
	free(parse);
}

