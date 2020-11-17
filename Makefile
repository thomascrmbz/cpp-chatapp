# cpp-websocket(https://github.com/thomascrmbz/cpp-websocket) library path
WEBSOCKET_LIB=../../../thomascrmbz/cpp-websocket

# cpp-http-server(https://github.com/thomascrmbz/cpp-http-server) library path
HTTP_LIB=../../../thomascrmbz/cpp-http-server

DOCKER_CLIENT_NAME=thomascrmbz/cpp-chatapp-client
DOCKER_SERVER_NAME=thomascrmbz/cpp-chatapp-server

all: mkdir dep server client

server:
	g++ -c --std=c++11 src/server/main.cpp -I$(WEBSOCKET_LIB)/src -I$(HTTP_LIB)/src -o bin/server/main.o
	g++ --std=c++11 bin/server/main.o -L$(WEBSOCKET_LIB)/bin -lWebSocketServer -L$(HTTP_LIB)/bin -lHTTP -o server.out

client:
	g++ -c --std=c++11 src/client/main.cpp -I$(WEBSOCKET_LIB)/src -I$(HTTP_LIB)/src -o bin/client/main.o
	g++ --std=c++11 bin/client/main.o -L$(WEBSOCKET_LIB)/bin -lWebSocketClient -L$(HTTP_LIB)/bin -lHTTP -o client.out

dep:
	(cd $(WEBSOCKET_LIB); make)
	(cd $(HTTP_LIB); make)

docker:
	rm -rf .lib/
	mkdir -p .lib .lib/cpp-http-server .lib/cpp-websocket
	cp -r $(HTTP_LIB)/src .lib/cpp-http-server/src
	cp $(HTTP_LIB)/Makefile .lib/cpp-http-server

	cp -r $(WEBSOCKET_LIB)/src .lib/cpp-websocket/src
	cp $(WEBSOCKET_LIB)/Makefile .lib/cpp-websocket

	docker build --target client -t $(DOCKER_CLIENT_NAME) .
	docker build --target server -t $(DOCKER_SERVER_NAME) .
	
	rm -rf .lib/

mkdir:
	mkdir -p bin bin/server bin/client

clean:
	rm -rf bin/