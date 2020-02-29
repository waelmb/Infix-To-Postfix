proj5: wmobei2Proj5.o proj5Stack.o
	g++ -g -o proj5 wmobei2Proj5.o proj5Stack.o

wmobei2Proj5.o: wmobei2Proj5.cpp proj5.h
	g++ -g -c wmobei2Proj5.cpp

proj5Stack.o: proj5Stack.cpp proj5.h
	g++ -g -c proj5Stack.cpp

clean:
	rm wmobei2Proj5.o proj5Stack.o proj5