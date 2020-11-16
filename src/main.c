#include "include/bstring.h"

int bstring_test() {

	const char *test_str = "asdfasdfasdfasdfasdfasdf\0";
	const char *update = "The quick brown fox jumps over the lazy dog";
	bstring *test[256];

	for (int i = 0; i < 256; i++)
		test[i] = bstring_new(test_str);

	for (int i = 0; i < 256; i++)
		bstring_reassign(test[i], update);

	for (int i = 0; i < 256; i++)
		bstring_delete(test[i]);

	return 0;
}

int main(int argc, const char **argv) { return bstring_test(); }

