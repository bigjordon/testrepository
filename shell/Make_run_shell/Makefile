OUTPUT= 
all:
	@echo pwd:`pwd` # do not purse softlink
	@echo pwd: $(shell pwd)  # really really absolute dir
	@echo realpath: $(realpath .)
	@echo abspath: $(abspath .)
test: 
# can use but not purse softlink
	OUTPUT=$(shell pwd) 
	@echo $(OUTPUT)
# it seams good
	OUTPUT=$(shell echo `pwd`)  
	@echo $(OUTPUT)
# can use but not purse softlink
	OUTPUT=$(realpath .) 
	@echo $(OUTPUT)
# can use but not purse softlink
	OUTPUT=$(dir . ) 
	@echo $(OUTPUT)
