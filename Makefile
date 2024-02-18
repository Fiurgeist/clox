.PHONY: build
build:
	gcc -std=c99 -Wno-discarded-qualifiers ./src/*.c -o clox

.PHONY: run
run: build
	./clox $(file)

.PHONY: help
help:
	@echo "Please use 'make <target>' where <target> is one of"
	@echo "  run [file=SCRIPT]       run the vm"
	@echo "  build                   build executable"
