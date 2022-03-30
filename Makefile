client: client
	g++ client.cpp -Wall -o client

server: server
	g++ server.cpp  -Wall -o server

clean:
	rm -f client client core
	rm -f server server core