#ifndef _BEEVR_BSTRING_H_
#define _BEEVR_BSTRING_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// TODO: Implement string interns or similar caching mechanism.

typedef struct __b_string bstring;

struct __b_string {
	char *str;
	uint32_t size;
};

bstring *bstring_new(const char *buff);

/*
 *	..._assign requirements: buff != 0
 */
void bstring_assign(bstring *str, const char *buff);

void bstring_reassign(bstring *str, const char *buff);

void bstring_delete(const bstring *str);

char *bstring_get_value(const bstring *str);

bool bstring_cequal(const char *str1, const char *str2);
bool bstring_equal(const bstring *str1, const bstring *str2);

#endif //_BEEVR_BSTRING_H_

