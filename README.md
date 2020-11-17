# C++ Chat App

# Getting Started

## Running

A docker image of the server and client is available on Docker Hub.
  - [chatapp-client](https://hub.docker.com/repository/docker/thomascrmbz/chatapp-client/)
  - [chatapp-server](https://hub.docker.com/repository/docker/thomascrmbz/chatapp-server/)

If you run it localy you will need to build the files (see [Building](#building)).
When you have `client.out` and/or `server.out` you can run these commands.

```bash
# to start the server
./server

# to start the client
./client
```

If you want to run the app inside docker you can run:

```bash
# to start the client
docker run -it thomascrmbz/chatapp-client

# to start the server
docker run -d --name chatapp-server thomascrmbz/chatapp-server
```

## Building

### Dependencies

This app has 2 dependencies:
  - [cpp-http-server](https://github.com/thomascrmbz/cpp-http-server/)
  - [cpp-websocket](https://github.com/thomascrmbz/cpp-websocket/)

You need to download the source files and insert them in the build commands.

### Commands

There are 2 options to build this chat app, build it localy or build a docker image (preferred).

**To build it localy**

```bash
# build all
make HTTP_LIB=../cpp-http-server WEBSOCKET_LIB=./cpp-websocket

# build client only
make client HTTP_LIB=../cpp-http-server WEBSOCKET_LIB=./cpp-websocket

# build server only
make server HTTP_LIB=../cpp-http-server WEBSOCKET_LIB=./cpp-websocket
```

**To build the docker image**

```bash
# this wil build a server and a client image
make docker DOCKER_CLIENT_NAME=example/chat-client DOCKER_SERVER_NAME=example/chat-server HTTP_LIB=../cpp-http-server WEBSOCKET_LIB=./cpp-websocket
```

# License

This project is licensed under the MIT License.