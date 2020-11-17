# cpp-websocket(https://github.com/thomascrmbz/cpp-websocket) library path
WEBSOCKET_LIB=../../../thomascrmbz/cpp-websocket

# cpp-http-server(https://github.com/thomascrmbz/cpp-http-server) library path
HTTP_LIB=../../../thomascrmbz/cpp-http-server

DOCKER_CLIENT_NAME=thomascrmbz/cpp-chatapp-client
DOCKER_SERVER_NAME=thomascrmbz/cpp-chatapp-server

CLIENT_SOURCES := $(wildcard src/client/*.cpp)
CLIENT_NAMES := $(CLIENT_SOURCES:src/%.cpp=%)

SERVER_SOURCES := $(wildcard src/server/*.cpp)
SERVER_NAMES := $(SERVER_SOURCES:src/%.cpp=%)

all: mkdir dep server client

server: mkdir dep $(SERVER_NAMES)
	g++ --std=c++11 $(SERVER_NAMES:%=bin/%.o) -L$(WEBSOCKET_LIB)/bin -lWebSocketServer -L$(HTTP_LIB)/bin -lHTTP -o server.out

client: mkdir dep $(CLIENT_NAMES)
	g++ --std=c++11 $(CLIENT_NAMES:%=bin/%.o) -L$(WEBSOCKET_LIB)/bin -lWebSocketClient -L$(HTTP_LIB)/bin -lHTTP -o client.out

client/%:
	g++ -c --std=c++11 -I$(WEBSOCKET_LIB)/src -I$(HTTP_LIB)/src src/$@.cpp$< -o bin/$@.o

server/%:
	g++ -c --std=c++11 -I$(WEBSOCKET_LIB)/src -I$(HTTP_LIB)/src src/$@.cpp$< -o bin/$@.o

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