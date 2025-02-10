#pragma once

#include <string>

namespace client {

bool check_text(const std::string &input);

class Client final {
private:
  int socket_ = 0;

public:
  Client();
  ~Client();
  int connect_to_server(const char *server_ip, int port) const noexcept;
  void send_to_server(const std::string &message) const noexcept;
};

} // namespace client