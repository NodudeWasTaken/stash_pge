CREATE OR REPLACE FUNCTION phash_distance(int8, int8) RETURNS int8
	AS :MOD, 'PhashDistance'
	LANGUAGE C STRICT;
