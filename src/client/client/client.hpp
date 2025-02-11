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

class SharedBuffer {
private:
  std::string buffer_;
  pthread_mutex_t lock_ = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t cond_ = PTHREAD_COND_INITIALIZER;

  bool buff_ready_ = false;

public:
  SharedBuffer() = default;
  std::string get_buff() noexcept;
  void set_buff(std::string buff) noexcept;
  void clear() noexcept { buffer_.clear(); }
};

} // namespace client