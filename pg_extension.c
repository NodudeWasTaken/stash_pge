#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/date.h"
#include "utils/datetime.h"
#include <stdint.h>
#include "out/libgoextension.h"

PG_MODULE_MAGIC;

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
