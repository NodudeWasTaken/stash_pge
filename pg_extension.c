#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include <stdint.h>
#include "out/libgoextension.h"

PG_MODULE_MAGIC;

/*
extern char* goBasename(char*);
extern bool goRegexpMatch(char*,char*);
extern int64_t goPhashDistance(int64_t, int64_t);
*/

PG_FUNCTION_INFO_V1(Basename);

Datum Basename(PG_FUNCTION_ARGS) {
    text *arg1 = PG_GETARG_TEXT_PP(0);
    char *input = text_to_cstring(arg1);

    char *result = goBasename(input);

    text *pg_result = cstring_to_text(result);
    PG_RETURN_TEXT_P(pg_result);
}

PG_FUNCTION_INFO_V1(RegexpMatch);

Datum RegexpMatch(PG_FUNCTION_ARGS) {
    text *arg1 = PG_GETARG_TEXT_PP(0);
    text *arg2 = PG_GETARG_TEXT_PP(2);
    char *input1 = text_to_cstring(arg1);
    char *input2 = text_to_cstring(arg2);

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
