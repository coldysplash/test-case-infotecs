#include "client/client.hpp"

#include <arpa/inet.h>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace client {

bool check_text(const std::string &input) {
  if (input.size() > 64) {
    std::cout << "Error! Max string size 64.\n";
    return false;
  }
  for (const auto &ch : input) {
    if (isdigit(ch) == 0) {
      std::cout << "Error! Input must consist of digits only..\n";
      return false;
    }
  }
  return true;
}

Client::Client() {
  socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_ < 0) {
    throw std::runtime_error("Error creating socket!");
  }
}

Client::~Client() { close(socket_); }

int Client::connect_to_server(const char *server_ip, int port) const noexcept {
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(server_ip);
  address.sin_port = htons(port);

  const int status =
      connect(socket_, reinterpret_cast<sockaddr *>(&address), sizeof(address));

  if (status != 0) {
    std::cout
        << "Error connecting to server! Please restart the server or client.\n"
        << "Waiting for connection ...\n";
  } else {
    std::cout << "\nConnection complete!! ";
  }
  return status;
}

void Client::send_to_server(const std::string &message) const noexcept {
  send(socket_, message.c_str(), message.size(), 0);
}

} // namespace client