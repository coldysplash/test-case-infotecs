#include <common/parser.hpp>

#include <algorithm>
#include <cctype>
#include <string>
#include <utility>

namespace parser {

void modify_str(std::string &str) {
  std::sort(str.begin(), str.end(), [](auto l, auto r) { return l > r; });

  std::string modify_text;
  for (const auto &it : str) {
    if ((it - '0') % 2 == 0) {
      modify_text.append("KB");
    } else {
      modify_text.append(&it, 1);
    }
  }
  str = std::move(modify_text);
}

std::string total_sum_of_nums(const std::string &str) {
  int sum = 0;
  for (const auto &ch : str) {
    if (isdigit(ch) == 1) {
      sum += ch - '0';
    }
  }

  return std::to_string(sum);
}

bool analyze_message(const std::string &message) {
  return message.length() > 2 && std::stoi(message) % 32 == 0;
}
} // namespace parser