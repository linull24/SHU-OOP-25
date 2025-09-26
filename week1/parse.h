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

  // 这个东西，我也是被迫去复习了C++中的Regex用法。这里应该是ECMA风格。
  // ^ $用于强制规定卡在首尾；第一个返回的是二次项的参数
  // 第二部分可选，返回符号和一次项系数
  // 第三部分可选，返回符号和常数
  void fail() { throw std::invalid_argument("输入格式错误"); }
  void parseString() {
    static const std::regex reg(RAW_REG);
    std::smatch match;  // 用cstring是cmatch
    if (std::regex_match(input, match, reg)) {
      A = match[1].str();
      if (match[2].matched && match[3].matched) {
        B = match[2].str() + match[3].str(); 
      } else if (match[2].matched) {
        B = match[2].str() + "1";  
      } else if (match[3].matched) {
        B = "+" + match[3].str();  
      }
      if (match[4].matched && match[5].matched) {
        C = match[4].str() + match[5].str(); 
      } else if (match[4].matched) {
        C = match[4].str() + "1";  
      } else if (match[5].matched) {
        C = "+" + match[5].str();  
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
    if (str.empty() || str == "+" || str == "+." || str == ".") {
        return 1.0;
    }
    if (str == "-" || str == "-.") {
        return -1.0;
    }
    if (isA && (str.empty() || (str.find_first_not_of(" \t") == std::string::npos))) {
        return 1.0;
    }
    
    try {
        return std::stod(str);
    } catch (...) {
        return 0.0;
    }
}
};
