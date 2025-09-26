#include <regex>
#include <string>
// 2412305 李林 see： https://github.com/linull24/SHU-OOP-25/tree/cpp
#define RAW_REG R"(^\s*([+\-]?\s*\d*\.?\d*)\s*x\^2\s*(?:(\+|-)\s*(\d*\.?\d*)\s*x\s*)?(?:(\+|-)\s*(\d*\.?\d+))?\s*$)"
class parse {
 public:
  double a = 0, b = 0, c = 0;
  std::string input;
  void get(const std::string& in) {
    input = in;
    parseString();
    a = advancedStod(A, true);
    b = advancedStod(B);
    c = advancedStod(C);
    if (a == 0) {
      fail();
    }
  }

 private:
  std::string A, B, C;


  void fail() { throw std::invalid_argument("输入格式错误"); }
  void parseString() {
    static const std::regex reg(RAW_REG);
    std::smatch match;
    if (std::regex_match(input, match, reg)) {
      A = match[1].str();
      if (match[2].matched && match[3].matched) {
        B = match[2].str() + match[3].str();
      }
      if (match[4].matched && match[5].matched) {
        C = match[4].str() + match[5].str();
      }

      static const std::regex whitespace(R"(\s+)");
      A = std::regex_replace(A, whitespace, "");
      B = std::regex_replace(B, whitespace, "");
      C = std::regex_replace(C, whitespace, "");
    }
    else {
      fail();
    }
  }
  double advancedStod(const std::string& str, bool isA = false) const {
    if (str.empty()) {
        return isA ? 1.0 : 0.0;
    }
    if (str == "+" || str == "+.") {
        return 1.0;
    }
    if (str == "-" || str == "-.") {
        return -1.0;
    }
    
    try {
        return std::stod(str);
    } catch (...) {
        return isA ? 1.0 : 0.0;
    }
  }
};
