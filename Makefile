all:
	clang++ -std=c++14 -g -I. -Wall -lGLU -lGL -lglut main.cpp

run: all
	./a.out

debug: all
	gdb ./a.out

commit:
	git add --a
	git commit
	git push origin master
