#!/bin/bash

PGVER ?= 14
PGINC ?= /usr/include/postgresql/$(PGVER)/server
DBNAME ?= stash
DBUSER ?= postgres

export CGO_ENABLED=1
export CGO_CFLAGS=-I$(PGINC)

PG_GO_MOD=$(abspath out/libgoextension.a)
PGMOD=$(abspath out/libpgstash.so)

check_pgincludes:
	@if [ ! -d "$(PGINC)" ]; then \
		echo "ERROR: PGINC directory does not exist: $(PGINC)"; \
		exit 1; \
	fi

all: $(PGMOD)

$(PG_GO_MOD): *.go Makefile
	go build -buildmode=c-archive -o $(PG_GO_MOD) pg_extension.go

$(PGMOD): check_pgincludes $(PG_GO_MOD) *.c Makefile
	gcc -fPIC -shared -o $(PGMOD) pg_extension.c -L./out -lgoextension -I$(PGINC)

install: $(PGMOD)
	sed "s|:MOD|'$(PGMOD)'|g" functions.sql | sudo -u postgres psql $(DBUSER) -d $(DBNAME)

clean:
	rm -rf out
