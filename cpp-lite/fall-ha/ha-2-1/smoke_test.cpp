#include <cassert>
#include <string>

#include "lazy_string.hpp"

int main()
{
    // Template arguments
    std_utils::lazy_basic_string<char, std::char_traits<char>> ss1;
    std_utils::lazy_basic_string<char> ss2;
    std_utils::lazy_basic_string<wchar_t> ss3;

    // Constructors
    std_utils::lazy_string s1;
    std_utils::lazy_string s2("Test");
    std_utils::lazy_string s3 = "Test";
    std_utils::lazy_string s4(s3);
    std_utils::lazy_string s5(3, 'X');
    std_utils::lazy_string const s6(0, 'A');
    std_utils::lazy_string const s7;
    std_utils::lazy_string s8(s7);

    // Read-only operations
    assert("Test" == s2);
    assert(s3 == "Test");
    assert("Test" == s4);
    assert(s4.c_str() == s3.c_str());
    assert(std::string(s4.c_str()) == "Test");
    assert(s4.size() == 4);
    assert(s5 == "XXX");
    assert(s5 != "XXY");
    assert("XXY" != s5);
    assert(s5 < "XXx");
    assert("XX" < s5);
    assert(s6.empty());
    assert(s6 == "");
    assert(s6 == s1);
    assert(s6.size() == 0);

    // String modification
    s4.swap(s1);
    assert(s4 == "");
    assert(s1.c_str() == s3.c_str());
    s4 = "abc";
    s1 = s4;
    assert(s1.c_str() == s4.c_str());
    assert(s3 == "Test");
    assert(s1 == "abc");
    swap(s3, s1);
    swap(s3, s1);
    assert(s1.c_str() == s4.c_str());

    assert(s1[0] == 'a');
    assert(s1[1] == 'b');
    assert(s1[2] == 'c');
    assert(s1[3] == 0);
    assert(s1.c_str() == s4.c_str());

    s1[1] = 'X';
    assert(s1 == "aXc");
    assert(s4 == "abc");
    (s1[2] = 'Y') = 'Z';
    assert(s1 == "aXZ");

    s5 = s4;
    s5 += 'a';
    assert(s4 == "abc");
    assert(s5 == "abca");

    s5 += "ABC";
    assert(s5 == "abcaABC");
    assert(("[" + s4) + ']' == ('[' + s4) + "]");
    assert(s4 + s5 == "abcabcaABC");
    assert(s4 + s5 == s4 + s5);
    assert(s4 + s5 != s5 + s4);
    assert(!(s4 < s4));

//    s1 = s5;
//    s4 = std::move(s5);
//    assert(s4 == "abcaABC");
//    assert(s1.c_str() == s4.c_str());
//    s5.size();
//    s5.empty();
//    std::string(s5.c_str());

    // Wide string
    std_utils::lazy_wstring const ws1;
    std_utils::lazy_wstring ws2(L"Тест");
    std_utils::lazy_wstring ws3 = L"Тест";
    std_utils::lazy_wstring ws4(ws1);
    std_utils::lazy_wstring ws5(3, L'Я');

    // Insert same read-only and modification tests for wide string here...

    // Case insensitive string
    std_utils::lazy_istring const is1;
    std_utils::lazy_istring is2("Test");
    std_utils::lazy_istring is3 = "Test";
    std_utils::lazy_istring is4(is1);
    std_utils::lazy_istring is5(3, 'X');

    assert(is5 == "xxx");
    assert(!(is5 < "xxx"));
}
