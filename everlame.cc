#include <cassert>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

// Lightweight wrapper around a std::string to allow taking substrings
// without copying.
class StringWrap {
 public:
  StringWrap(const std::string &str,
             std::string::size_type first,
             std::string::size_type last)
      :str_(str), first_(first), last_(last) {
    assert(last <= str.size());
  }
  StringWrap(const std::string &str) :StringWrap(str, 0, str.size()) {}

  std::string::size_type size() const { return last_ - first_; }

  const char& front() const { return str_[first_]; }

  StringWrap substr(std::string::size_type new_first,
                    std::string::size_type new_last) const {
    return {str_, new_first + first_, new_last + first_};
  }

 private:
  const std::string &str_;
  const std::string::size_type first_;
  const std::string::size_type last_;
};

bool check(StringWrap s) {
  if (s.size() == 0) {
    return false;
  }

  const char &f = s.front();
  if (s.size() == 1) {
    return f >= 'a' && f <= 'j';
  }
  if (f == 'Z') {
    return check(s.substr(1, s.size()));
  }
  if (f == 'M' || f == 'K' || f == 'P' || f == 'Q') {
    for (std::string::size_type i = 2; i < s.size(); i++) {
      if (check(s.substr(1, i)) && check(s.substr(i, s.size()))) {
        return true;
      }
    }
  }
  return false;
}

void print_solution(std::stringstream &tokenizer, bool &has_token) {
  if (tokenizer.str().size()) {
    std::string token = tokenizer.str();
    std::cout << token << " " << (check(token) ? "VALID" : "INVALID")
              << "\n";
    tokenizer.str("");
    has_token = false;
  }
}

int main(int argc, char **argv) {
  std::string line;
  std::stringstream tokenizer;
  bool has_token = false;

  while (true) {
    std::getline(std::cin, line);
    if (std::cin.eof() || std::cin.fail()) {
      break;
    }

    // split the line
    for (const char &c : line) {
      if (isspace(c)) {
        print_solution(tokenizer, has_token);
      } else {
        tokenizer.put(c);
        has_token = true;
      }
    }
    print_solution(tokenizer, has_token);
  }
  return 0;
}
