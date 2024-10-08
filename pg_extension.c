#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include <stdint.h>
#include "out/libgoextension.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(Basename);

Datum Basename(PG_FUNCTION_ARGS) {
	char *input = text_to_cstring(PG_GETARG_TEXT_PP(0));

	char *val = goBasename(input);

	text *result = cstring_to_text(val);
	PG_RETURN_TEXT_P(result);
}

PG_FUNCTION_INFO_V1(RegexpMatch);

Datum RegexpMatch(PG_FUNCTION_ARGS) {
	char *input1 = text_to_cstring(PG_GETARG_TEXT_PP(0));
	char *input2 = text_to_cstring(PG_GETARG_TEXT_PP(1));

	bool result = goRegexpMatch(input1, input2);
	PG_RETURN_BOOL(result);
}

PG_FUNCTION_INFO_V1(PhashDistance);

Datum PhashDistance(PG_FUNCTION_ARGS) {
	int64_t arg1 = PG_GETARG_INT64(0);
	int64_t arg2 = PG_GETARG_INT64(1);
	int64_t val = goPhashDistance(arg1, arg2);
	PG_RETURN_INT64(val);
}

void _PG_init(void) {
    elog(INFO, "Stash PGE extension loaded and initialized");
	goInit();
}