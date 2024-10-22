output: social_network.o network.o user.o post.o
	g++ social_network.o network.o user.o post.o -o output

user.o: user.cpp
	g++ user.cpp -c -o user.o

network.o: network.cpp
	g++ network.cpp -c -o network.o
	
social_network.o: social_network.cpp
	g++ social_network.cpp -c -o social_network.o

post.o: post.cpp
	g++ post.cpp -c -o post.o

clean:
	rm *.o output