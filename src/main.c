
#include "include/bstring.h"
#include "include/cli_parse.h"
#include <stdlib.h>

static const char *name	   = "beevr";
static const char *version = "0.0.1";
static const char *author  = "Dhruv Patel <predaking2612@gmail.com>";
static const char *about   = "An interactive REPL mode for C99.";

static cliparse *args_parse;

static int bstring_test() {

	const char *test_str = "asdfasdfasdfasdfasdfasdf\0";
	const char *update	 = "The quick brown fox jumps over the lazy dog";
	bstring *test[256];

	for (int i = 0; i < 256; i++) test[i] = bstring_new(test_str);
	for (int i = 0; i < 256; i++) bstring_reassign(test[i], update);
	for (int i = 0; i < 256; i++) bstring_delete(test[i]);

	return 0;
}

static void container_free(const clicontainer **cont) {

	int size = cont[0]->size;
	for (int i = 0; i < size; i++) clicontainer_free(cont[i]);
}

// TODO: Fix the parsing error --> double free pointers.
// 		 and some code cleanup.
static void cliparse_test(int argc, const char **argv) {

	args_parse = create_cliargs(name, version, author, about);

	cliparse_push_back(
		args_parse, create_args("flags", "flags", "Set compile flags", "STRING", NULL, 'f', true));
	cliparse_push_back(
		args_parse, create_args("save", "save", "save REPL input", "NO-INPUT", NULL, 's', false));

	const clicontainer **args = (const clicontainer **)cliparse_parse(argc, argv, args_parse);
	char *str				  = clicontainer_match("flag", args);

	container_free(args);
	cliparse_free(args_parse);
}

int main(int argc, const char **argv) {
	cliparse_test(argc, argv);
	return bstring_test();
}

