all:
	gcc -Wall -shared -fPIC -o libss.so libss.c -ldl
	gcc -Wall -o main main.c -lss -L. -ldl
clean:
	rm main libss.so
