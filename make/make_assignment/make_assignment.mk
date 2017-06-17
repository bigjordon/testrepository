V = a
$(warning $$V: $(V))
V  += b
$(warning $$V: $(V))
V = c
$(warning $$V: $(V))
V := d
$(warning $$V: $(V))
V ?= e
$(warning $$V: $(V))


X = ttt
Y := $(X)
X = sss
$(warning $$Y: $(Y))
# Y will be ttt due to :=

x = foo
y = $(x) bar
x = xyz
$(warning $$y: $(y))
# x will be xyz bar dur to =  
# so := will explain the x before where y is assigned
# while = do not explain teh $(x) that is to say y is "$(x) bar" and $(y) is S(S(x) bar)

all:
	
	@echo 
	@echo 
	@echo 
	@more make_assignment.mk
	@echo done;
	
