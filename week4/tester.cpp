#include<iostream>
#include "myString.hpp"
void  TestString( )
{
std::cout << "=== 开始测试 myString 所有功能 ===" << std::endl;
    int passCount = 0, totalCount = 12; // 总测试项数
// 1. 测试默认构造（空字符串）
    std::cout << "\n1. 测试默认构造：";
    myString s1;
    if (s1.isEmpty() && s1.length() == 0 && std::string(s1.c_str()) == "") {
        std::cout << "测试通过";
        passCount++;
    } else {
        std::cout << "测试失败（预期空串，实际：" << s1.c_str() << "）";
    }

    // 2. 测试常量字符串构造（含中文字符）
    std::cout << "\n2. 测试常量构造（中文字符）：";
    myString s2("自定义字符串"); // 测试多字节字符
    if (std::string(s2.c_str()) == "自定义字符串") {
        std::cout << "测试通过（内容：" << s2.c_str() << "）";
        passCount++;
    } else {
        std::cout << "测试失败（预期\"自定义字符串\"，实际：" << s2.c_str() << "）";
    }

    // 3. 测试索引访问（正常+越界）
    std::cout << "\n3. 测试索引访问：";
    myString s3("test");
    const myString s33("test");
    std::cout << s33[1]<<std::endl;
    s3[1] = 'E'; // 修改正常索引
    bool idxOk = (std::string(s3.c_str()) == "tEst") && (s3[100] == s3[0]); // 越界返回首字符
    if (idxOk) {
        std::cout << "测试通过（修改后：" << s3.c_str() << "）";
        passCount++;
    } else {
        std::cout << "测试失败（索引修改/越界处理异常）";
    }


    // 4. 测试拷贝构造（独立内存，修改不影响原对象）
    std::cout << "\n4. 测试拷贝构造：";
    myString s4(s3);
    s4[0] = 'T'; // 修改拷贝对象
    if (std::string(s3.c_str()) == "tEst" && std::string(s4.c_str()) == "TEst") {
        std::cout << "测试通过（原串：" << s3.c_str() << "，拷贝串：" << s4.c_str() << "）";
        passCount++;
    } else {
        std::cout << "测试失败（拷贝后内存未独立）";
    }

    // 5. 测试赋值运算符（自我赋值+普通赋值）
    std::cout << "\n5. 测试赋值运算符：";
    myString s5("old"), s6;
    s5 = s5; // 自我赋值（避免崩溃）
    s6 = s5; // 普通赋值
    s6[0] = 'N';
    bool assignOk = (std::string(s5.c_str()) == "old") && (std::string(s6.c_str()) == "Nld");
    if (assignOk) {
        std::cout << "测试通过（原串：" << s5.c_str() << "，赋值串：" << s6.c_str() << "）";
        passCount++;
    } else {
        std::cout << "测试失败（自我赋值/普通赋值异常）";
    }

    // 6. 测试字符串拼接（空串+非空、非空+非空）
    std::cout << "\n6. 测试字符串拼接：";
    myString s7("Hello"), s8(""), s9(" World");
    myString s10 = s8 + s7; // 空串+非空
    myString s11 = s7 + s9; // 非空+非空
    bool concatOk = (std::string(s10.c_str()) == "Hello") && (std::string(s11.c_str()) == "Hello World");
    if (concatOk) {
        std::cout << "测试通过（空+非空：" << s10.c_str() << "，非空+非空：" << s11.c_str() << "）";
        passCount++;
    } else {
        std::cout << "测试失败（拼接结果异常）";
    }

    // 7. 测试相等/不相等比较
    std::cout << "\n7. 测试比较运算符：";
    myString s12("abc"), s13("abc"), s14("abd");
    bool cmpOk = (s12 == s13) && (s12 != s14);
    if (cmpOk) {
        std::cout << "测试通过（相同相等、不同不相等）";
        passCount++;
    } else {
        std::cout << "测试失败（比较逻辑异常）";
    }

    // 8. 测试子串截取（正常范围、超出范围、起始越界）
    std::cout << "\n8. 测试子串截取：";
    myString s15("abcdefg");
    myString sub1 = s15.substr(2, 3);  // 从索引2取3个字符：cde
    myString sub2 = s15.substr(5, 10); // 超出长度，取到末尾：fg
    myString sub3 = s15.substr(10, 2); // 起始越界，返回空串
    bool substrOk = (std::string(sub1.c_str()) == "cde") && (std::string(sub2.c_str()) == "fg") && (sub3.isEmpty());
    if (substrOk) {
        std::cout << "测试通过（sub1：" << sub1.c_str() << "，sub2：" << sub2.c_str() << "，sub3：空）";
        passCount++;
    } else {
        std::cout << "测试失败（子串截取异常）";
    }

    // 9. 测试字符查找（存在的字符、不存在的字符）
    std::cout << "\n9. 测试字符查找：";
    int pos1 = s15.find('d');  // 存在，预期索引3
    int pos2 = s15.find('x');  // 不存在，预期-1
    if (pos1 == 3 && pos2 == -1) {
        std::cout << "测试通过（'d'在索引" << pos1 << "，'x'未找到）";
        passCount++;
    } else {
        std::cout << "测试失败（查找结果异常，'d'实际：" << pos1 << "，'x'实际：" << pos2 << "）";
    }

    // 10. 测试单字符构造与拼接
    std::cout << "\n10. 测试单字符处理：";
    myString s16("a"), s17("b");
    myString s18 = s16 + s17;
    bool singleOk = (s16.length() == 1) && (std::string(s18.c_str()) == "ab");
    if (singleOk) {
        std::cout << "测试通过（单字符：" << s16.c_str() << "，拼接：" << s18.c_str() << "）";
        passCount++;
    } else {
        std::cout << "测试失败（单字符构造/拼接异常）";
    }

    // 11. 测试长字符串构造（避免内存溢出）
    std::cout << "\n11. 测试长字符串构造：";
    char longStr[1001];
    for (int i = 0; i < 1000; i++) longStr[i] = 'A';
    longStr[1000] = '\0';
    myString s19(longStr);
    if (s19.length() == 1000 && std::string(s19.c_str()).size() == 1000) {
        std::cout << "测试通过（长度：" << s19.length() << "）";
        passCount++;
    } else {
        std::cout << "测试失败（长字符串长度异常，实际：" << s19.length() << "）";
    }

    // 12. 测试析构后二次访问（避免野指针，此处仅验证无崩溃）
    std::cout << "\n12. 测试析构安全性（无崩溃即通过）：";
    {
        myString s20("temp");
    } // s20 在此处析构
    std::cout << "测试通过（析构后无崩溃）";
    passCount++;

    // 最终统计
    std::cout << "\n\n=== 测试结束 ===" << std::endl;
}
int main() {
    TestString( );
    return 0;
}