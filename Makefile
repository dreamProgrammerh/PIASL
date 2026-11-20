CSTD ?= c11

platform-%:
	@clang -std=$(CSTD) --target="$*" -O0 -Iinclude -o /tmp/$@ tests/platform_macros.c
	@/tmp/$@
	@rm /tmp/$@
