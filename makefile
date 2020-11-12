main:main.cpp
	g++ -c main.cpp GetHeader.cpp MySocket.cpp  Time.cpp -w
	g++ main.o GetHeader.o MySocket.o Time.o   -lwsock32 -lws2_32 -o main
	del *.o