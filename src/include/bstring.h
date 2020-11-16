#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-reserved-identifier"
#ifndef _BEEVR_BSTRING_H_
#define _BEEVR_BSTRING_H_

#include <stdint.h>
#include <string.h>

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

void bstring_delete(bstring *str);

#endif //_BEEVR_BSTRING_H_

