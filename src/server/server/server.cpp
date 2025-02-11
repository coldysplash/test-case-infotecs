#include "server/server.hpp"

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

enum { BUFFER_SIZE = 64 };

namespace serv {

Server::Server() {
  server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket_ == -1) {
    throw std::runtime_error("Error creating socket!");
  }
  server_address_.sin_family = AF_INET;
  server_address_.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_address_.sin_port = htons(8080);
}

Server::~Server() { close(server_socket_); }

void Server::serv_bind() {
  if (bind(
          server_socket_,
          reinterpret_cast<sockaddr *>(&server_address_),
          sizeof(server_address_)) == -1) {
    throw std::runtime_error("Error binding socket!");
  }
}

void Server::serv_listen() const {
  if (listen(server_socket_, 2) == -1) {
    throw std::runtime_error("Error listening on socket!");
  }
}

int Server::accept_client_connection() const {
  sockaddr_in client_address{};
  socklen_t client_addr_length = sizeof(client_address);
  const int client_socket = accept(
      server_socket_,
      reinterpret_cast<sockaddr *>(&client_address),
      &client_addr_length);

  if (client_socket == -1) {
    throw std::runtime_error("Error accepting connection!");
  }

  return client_socket;
}

std::string Server::recv_message(int client_socket) const noexcept {
  char buff[BUFFER_SIZE];
  memset(buff, 0, BUFFER_SIZE);
  recv(client_socket, &buff, BUFFER_SIZE, 0);

  return {buff};
}

} // namespace serv