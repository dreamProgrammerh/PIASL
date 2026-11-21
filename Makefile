CSTD ?= c11

target_triple = $(shell python3 scripts/target_matrix.py $(1))

platform-%:
	@clang -std=$(CSTD) --target="$(call target_triple,$*)" -O0 -Iinclude \
	        -o /tmp/$@.exe tests/platform_macros.c
	@/tmp/$@.exe

T-%:
	@echo $(call target_triple,$*)
