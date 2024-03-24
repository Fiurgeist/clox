.PHONY: build
build:
	gcc -std=c99 -Wno-discarded-qualifiers -O2 ./src/*.c -o clox

.PHONY: build-debug
build-debug:
	gcc -std=c99 -Wno-discarded-qualifiers -g ./src/*.c -o clox

.PHONY: run
run: build-debug
	./clox $(file)

.PHONY: help
help:
	@echo "Please use 'make <target>' where <target> is one of"
	@echo "  run [file=SCRIPT]       run the vm in debug"
	@echo "  build-debug             build debug executable"
	@echo "  build                   build executable"
