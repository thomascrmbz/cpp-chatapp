#include <websocket.h>

int main() {
  
  WebSocket::Server server;

  server.listen(3000);

  return 0;
}