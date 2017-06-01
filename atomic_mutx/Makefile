all: cas fetch_and_add mutux

cas:
	g++ cas.cpp timer.cpp -lpthread -o cas

fetch_and_add:
	g++ fetch_and_add.cpp timer.cpp -lpthread -o fetch_and_add
mutux:
	g++ mutux.cpp timer.cpp -lpthread -o mutux
clean:
	rm cas fetch_and_add mutux
