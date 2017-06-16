# make -f makefile_origin.mk MY_VAR=aa
FILE_VAR = dd
all:
	@echo USER is: $(origin USER)
	@echo MY_VAR is: $(origin MY_VAR)
	@echo FILE_VAR is: $(origin FILE_VAR)
	@echo CC is: $(origin CC)
	$(warning cc: $CC)
	@echo CURDIR is: $(origin CURDIR)
