all: test0 test1 test2 test3 test4 test5
test0:
	gcc -o test0 attribute_constructor.c con1.c con2.c
test1:
	gcc -o test1 attribute_constructor.c con2.c con1.c 
test2:
	gcc -o test2 con1.c attribute_constructor.c con2.c
test3:
	gcc -o test3 con2.c attribute_constructor.c con1.c
test4:
	gcc -o test4 con1.c con2.c attribute_constructor.c
test5:
	gcc -o test5 con2.c con1.c attribute_constructor.c

clean:
	rm *.o test?
