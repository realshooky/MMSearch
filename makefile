MMSearch.exe: main.o Monster.o
	clang++ -o MMSearch.exe -std=c++11 main.o Monster.o
	rm *.o
main.o: main.cpp Monster.cpp
	clang++ -c -std=c++11 -g main.cpp
Monster.o: main.cpp Monster.cpp
	clang++ -c -std=c++11 -g Monster.cpp

clean:
	rm *.o *.exe
