CREATE OR REPLACE FUNCTION basename(text) RETURNS text
	AS :MOD, 'Basename'
	LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION phash_distance(int8, int8) RETURNS int8
	AS :MOD, 'PhashDistance'
	LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION regexp(text, text) RETURNS boolean 
	AS :MOD,'RegexpMatch'
	LANGUAGE C STRICT;
