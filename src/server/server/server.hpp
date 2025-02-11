#pragma once

#include <arpa/inet.h>
#include <string>

namespace serv {

class Server {
private:
  int server_socket_ = 0;
  sockaddr_in server_address_{};

public:
  Server();
  ~Server();
  void serv_bind();
  void serv_listen() const;
  int accept_client_connection() const;
  std::string recv_message(int client_socket) const noexcept;
};
} // namespace serv