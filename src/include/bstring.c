#include "bstring.h"
#include <assert.h>
#include <stdlib.h>

bstring *bstring_new(const char *buff) {
	if (!buff)
		return NULL;

	int len = 0;
	const char *begin, *end;
	bstring *retval = malloc(sizeof(bstring));

	begin = buff;
	end	  = buff + (int)strlen(buff);
	len	  = end - begin;

	retval->str	 = malloc(len);
	retval->size = len;

	memcpy(retval->str, begin, len);
	return retval;
}

void bstring_assign(bstring *str, const char *buff) {
	assert(buff != NULL &&
		   "Error: bstring_assign: assignment value 'buff' can not be of type NULL");
	assert(str != NULL && "Error: bstring_assign: assignment value 'str' must be a non-NULL value");

	if (!str)
		// pass it through reassignment.
		bstring_assign(str, buff);
	else
		str = bstring_new(buff);
}

void bstring_reassign(bstring *str, const char *buff) {
	if (!(buff || str))
		return;

	int len = 0;
	const char *begin, *end;
	char *new, *svpt;

	svpt  = str->str;
	begin = buff;
	end	  = buff + strlen(buff);

	len = end - begin;
	new = realloc(str->str, len + sizeof *buff);

	if (new) {
		memcpy(new, begin, len);
		str->str  = new;
		str->size = len;
	} else {
		str->str = svpt;
	}
}

// memory poof
void bstring_delete(bstring *str) {
	if (!str)
		return;
	if (str->str)
		free(str->str);
	free(str);
}

