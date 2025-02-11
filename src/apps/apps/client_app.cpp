#include "client/client.hpp"
#include "common/parser.hpp"

#include <iostream>
#include <pthread.h>
#include <string>

void *thread_func_1(void *data) {
  auto *shared_buffer = static_cast<client::SharedBuffer *>(data);
  std::cout << "Enter Digits >> ";
  while (true) {
    std::string input;
    std::getline(std::cin, input);
    if (client::check_text(input)) {
      parser::modify_str(input);
      shared_buffer->set_buff(input);
    } else {
      continue;
    }
  }
  return nullptr;
}

void *thread_func_2(void *data) {
  auto *shared_buffer = static_cast<client::SharedBuffer *>(data);
  while (true) {
    const client::Client client_;
    const std::string buff = shared_buffer->get_buff();
    shared_buffer->clear();
    std::cout << "\nModify input data: " << buff << '\n';
    if (client_.connect_to_server("127.0.0.1", 8080) == 0) {
      client_.send_to_server(parser::total_sum_of_nums(buff));
      std::cout << "Sending completed.\n";
    }
  }
  return nullptr;
}

int main() {
  client::SharedBuffer shared_buff;
  pthread_t thread_1;
  pthread_t thread_2;
  if (pthread_create(&thread_1, nullptr, thread_func_1, &shared_buff) != 0) {
    std::cerr << "Error creating thread" << '\n';
  }
  if (pthread_create(&thread_2, nullptr, thread_func_2, &shared_buff) != 0) {
    std::cerr << "Error creating thread" << '\n';
  }
  pthread_join(thread_1, nullptr);
  pthread_join(thread_2, nullptr);

  return 0;
}