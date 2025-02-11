#include "common/parser.hpp"
#include "server/server.hpp"

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  try {
    serv::Server server;
    server.serv_bind();
    server.serv_listen();
    int client_socket = 0;
    std::cout << "Server started!\n";
    while (true) {
      client_socket = server.accept_client_connection();
      const std::string message = server.recv_message(client_socket);
      if (parser::analyze_message(message)) {
        std::cout << "Data received successfully! Message - " << message
                  << '\n';
      } else {
        std::cout << "\nError! Received data does not match format.\n";
      }
      std::cout << "\nWaiting for a message ...\n";
    }
    close(client_socket);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}