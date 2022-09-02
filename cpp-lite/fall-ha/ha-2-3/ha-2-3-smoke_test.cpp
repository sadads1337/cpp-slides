// Tests for fn::bind
//
// Based on tests for boost::bind:
// <http://www.boost.org/doc/libs/1_55_0/libs/function/test/>

#include <memory>
#include <string>
#include <cassert>
#include <functional>
#include <type_traits>

#include "bind.hpp"

//#define USE_STD
#if !defined(USE_STD)
    namespace n = fn;
    using fn::_1;
    using fn::_2;
#else
    namespace n = std;
    using std::placeholders::_1;
    using std::placeholders::_2;
#endif

int global_int;
size_t res = 0;
std::string res_str;

void void_f_void()
{
    res = 10;
}

int int_f_void()
{
    return 11;
}

int int_f_void2()
{
    return 12;
}

std::string string_f_void()
{
    return "string_f_void";
}

int const const_int_f_void()
{
    return 31;
}

std::string const string_const_f_void()
{
    return "string_const_f_void";
}

void * void_ptr_f_void()
{
    return reinterpret_cast<void *>(20);
}

int * int_ptr_f_void()
{
    return reinterpret_cast<int *>(21);
}

std::string * string_ptr_f_void()
{
    return reinterpret_cast<std::string *>(22);
}

std::string const * const string_const_ptr_const_f_void()
{
    return reinterpret_cast<std::string *>(52);
}

std::string & string_ref_f_void()
{
    return res_str;
}

std::string const & string_const_ref_f_void()
{
    return res_str;
}

void assign_five(int &v)
{
    v = 5;
}

void rvalue_assign_six(int &&v)
{
    v = 6;
}

void rvalue_assign_six_and_test(int &&v, std::string && s)
{
    v = 6;
    s = "test";
}

std::string const * rvalue_const(std::string const && s)
{
    return &s;
}

std::string const * rvalue_const(std::string &&)
{
    return nullptr;
}

int const * pass_const_reference(int const &v)
{
    return &v;
}

int && return_rvalue()
{
    return std::move(global_int);
}

int const && return_const_rvalue()
{
    return std::move(global_int);
}

int & return_reference()
{
    return global_int;
}

int const & return_const_reference()
{
    return global_int;
}

double assign_five_and_eight(int &a, double &b)
{
    a = 5;
    b = 8;

    return a + b;
}

double assign_one_and_two(int &a, double &b)
{
    a = 1;
    b = 2;

    return a + b;
}

void assign_five_and_test(int &v, std::string & s)
{
    v = 5;
    s = "test";
}

char * void_f_char_array(char s[3])
{
    s[0] = 'a';
    s[1] = 'b';
    s[2] = 0;

    return s;
}

typedef int (*int_f_void_ptr_t)(void);

int_f_void_ptr_t func_ptr(int_f_void_ptr_t f)
{
    return f;
}

double double_f_double(double x)
{
    return x;
}

long f_0()
{
    return 17041L;
}

long f_1(long a)
{
    return a;
}

long f_2(long a, long b)
{
    return a + 10 * b;
}

long global_result;

void fv_0()
{
    global_result = 17041L;
}

void fv_1(long a)
{
    global_result = a;
}

void fv_2(long a, long b)
{
    global_result = a + 10 * b;
}

void function_test()
{
    int const i = 1;

    assert(n::bind(f_0)(i) == 17041L);
    assert(n::bind(f_1, _1)(i) == 1L);
    assert(n::bind(f_2, _1, 2)(i) == 21L);

    assert((n::bind(fv_0)(i), (global_result == 17041L)));
    assert((n::bind(fv_1, _1)(i), (global_result == 1L)));
    assert((n::bind(fv_2, _1, 2)(i), (global_result == 21L)));
}

template<class R, class Func>
R call(Func f)
{
    return f();
}

template<class R, class Func, class Arg>
R call1(Func f, Arg a)
{
    return f(a);
}

template<class R, class Func, class Arg1, class Arg2>
R call2(Func f, Arg1 a1, Arg2 a2)
{
    return f(a1, a2);
}

int type(int &&) { return 0; }
int type(int const &&) { return 1; }
int type(int &) { return 2; }
int type(int const &) { return 3; }

std::string string_copy(std::string const & s)
{
    return s;
}

std::unique_ptr<int> move_unique_ptr(std::unique_ptr<int> up)
{
    return std::move(up);
}

int sum_unique_ptr(std::unique_ptr<int> up1, std::unique_ptr<int> up2)
{
    return *up1 + *up2;
}

int main()
{
    {
        // Return types

        res = 0;
        n::bind(&void_f_void)();
        assert(res == 10);

        assert(n::bind(&int_f_void)() == 11);
        assert(n::bind(&string_f_void)() == "string_f_void");
        assert(n::bind(&const_int_f_void)() == 31);
        assert(n::bind(&string_const_f_void)() == "string_const_f_void");
        assert(n::bind(&void_ptr_f_void)() == reinterpret_cast<void *>(20));
        assert(n::bind(&int_ptr_f_void)() == reinterpret_cast<int *>(21));
        assert(n::bind(&string_ptr_f_void)() == reinterpret_cast<std::string *>(22));
        assert(n::bind(&string_const_ptr_const_f_void)() == reinterpret_cast<std::string *>(52));

        std::string & s1 = n::bind(&string_ref_f_void)();
        assert(&res_str == &s1);

        // TODO: check that result is const
        auto f2 = n::bind(&string_const_ref_f_void);
        std::string const & s2 = f2();
        assert(&res_str == &s2);
    }

    {
        // Placeholders

        struct C
        {
        } c;

        //n::bind(&f_2); // shouldn't compile
        //n::bind(&f_2, 1); // shouldn't compile
        assert(n::bind(&f_2, 1, 2)() == 21);
        assert(n::bind(&f_2, 1, 2)(c) == 21);
        assert(n::bind(&f_2, 1, 2)(c, 6.0) == 21);
        //assert(n::bind(&f_2, 1, _1)() == 21); // shouldn't compile
        assert(n::bind(&f_2, 1, _1)(2) == 21);
        assert(n::bind(&f_2, 1, _1)(2, c) == 21);
        assert(n::bind(&f_2, _1, 1)(2) == 12);
        assert(n::bind(&f_2, _1, 1)(2, c) == 12);
        assert(n::bind(&f_2, 2, _2)(2, 1) == 12); 
        assert(n::bind(&f_2, 2, _2)(c, 1) == 12);
        assert(n::bind(&f_2, _2, 1)(c, 2) == 12);
        assert(n::bind(&f_2, _2, _2)(c, 2) == 22);
        //n::bind(&f_2, _1, _2)(1); // shouldn't compile
        assert(n::bind(&f_2, _1, _2)(1, 2) == 21);
        assert(n::bind(&f_2, _2, _1)(1, 2) == 12);
        //n::bind(&f_2, _1, _1)(); // shouldn't compile
        assert(n::bind(&f_2, _1, _1)(3) == 33);
        assert(n::bind(&f_2, _1, _1)(3, c) == 33);
    }

    {
        // Pass reference

        int x;
        std::string s;

        x = 0;
        n::bind(&assign_five, _1)(x);
        assert(x == 5);

        x = 0;
        n::bind(&assign_five, std::ref(x))();
        assert(x == 5);

        x = 0;
        s.clear();
        n::bind(&assign_five_and_test, _1, _2)(x, s);
        assert(x == 5 && s == "test");

        x = 0;
        s.clear();
        n::bind(&assign_five_and_test, _2, _1)(s, x);
        assert(x == 5 && s == "test");

        x = 0;
        s.clear();
        n::bind(&assign_five_and_test, std::ref(x), _1)(s);
        assert(x == 5 && s == "test");

        x = 0;
        s.clear();
        n::bind(&assign_five_and_test, _1, std::ref(s))(x);
        assert(x == 5 && s == "test");

        x = 0;
        s.clear();
        n::bind(&assign_five_and_test, std::ref(x), std::ref(s))();
        assert(x == 5 && s == "test");
    }

    {
        // Pass rvalue reference

        int x;
        std::string s;

        x = 0;
        n::bind(&rvalue_assign_six, _1)(std::move(x));
        assert(x == 6);

        x = 0;
        s.clear();
        n::bind(&rvalue_assign_six_and_test, _1, _2)(std::move(x), std::move(s));
        assert(x == 6 && s == "test");

        x = 0;
        s.clear();
        n::bind(&rvalue_assign_six, _1)(std::move(x), std::move(5));
        assert(x == 6);

        std::string const s2;
        assert(n::bind((std::string const * (*)(std::string const &&))&rvalue_const, _1)(std::move(s2)) == &s2);
    }

    {
        // Return types

        assert(type(n::bind(&return_rvalue)()) == 0);
        assert(type(n::bind(&return_const_rvalue)()) == 1);
        assert(type(n::bind(&return_reference)()) == 2);
        assert(type(n::bind(&return_const_reference)()) == 3);
    }

    {
        // Pass object without copy constructor

        std::unique_ptr<int> up;

        assert(n::bind(&int_f_void)(up) == 11);
        assert(n::bind(&int_f_void)(up, up) == 11);
        assert(n::bind(&f_1, _1)(1, up) == 1);
        assert(n::bind(&f_1, _2)(up, 1) == 1);

        up.reset(new int(7));
        assert(*n::bind(&move_unique_ptr, _1)(std::move(up)) == 7);

        std::unique_ptr<int> up1(new int(2));
        std::unique_ptr<int> up2(new int(3));
        assert(n::bind(&sum_unique_ptr, _1, _2)(std::move(up1), std::move(up2)) == 5);
    }

    {
        char s[3];

        s[0] = 0;
        assert(n::bind(&void_f_char_array, _1)(s) == s);
        assert(std::string(s) == "ab");

        s[0] = 0;
        assert(n::bind(&void_f_char_array, s)() == s);
        assert(std::string(s) == "ab");

        assert(n::bind(&func_ptr, &int_f_void)() == &int_f_void);
        assert(n::bind(&func_ptr, _1)(&int_f_void) == &int_f_void);

        assert(n::bind(&double_f_double, 0.25f)() == 0.25);

        int const & x = 5;
        assert(n::bind(&pass_const_reference, _1)(x) == &x);

        auto f = n::bind(&string_copy, std::move(std::string(8000, 'A')));
        std::string tmp(8000, 'B');
        assert(f() == std::string(8000, 'A'));
    }

    {
        // Copy constructor

        auto f1 = n::bind(&int_f_void);
        assert(call<int>(f1) == 11);
        assert(call<int>(std::move(f1)) == 11);

        auto f2 = n::bind(&f_1, _1);
        assert(call1<long>(f2, 3) == 3);

        auto f3 = n::bind(&f_2, _1, _2);
        assert(call2<long>(f3, 3, 4) == 43);
    }

#if !defined(USE_STD)
    // std::bind cannot be copied

    {
        // Copy

        auto f1 = n::bind(&int_f_void);
        assert(f1() == 11);

        auto f2 = n::bind(&int_f_void2);
        assert(f2() == 12);

        f1 = f2;
        assert(f1() == 12);
        assert(f2() == 12);

        f1 = f1;
        assert(f1() == 12);

        int a, c;
        double b, d;

        a = b = 0;
        auto f3 = n::bind(&assign_five_and_eight, std::ref(a), _1);
        assert(f3(b) == 13 && a == 5 && b == 8);

        c = d = 0;
        auto f4 = n::bind(&assign_one_and_two, std::ref(c), _1);
        assert(f4(d) == 3 && c == 1 && d == 2);

        auto tmp = f3;
        f3 = f4;
        f4 = tmp;

        a = b = 0;
        c = d = 0;
        assert(f3(d) == 3 && c == 1 && d == 2);
        assert(f4(b) == 13 && a == 5 && b == 8);
    }
#endif // !defined(USE_STD)

    {
        // Move

        auto f1 = n::bind(&int_f_void);
        assert(f1() == 11);

        auto f2 = std::move(f1);
        assert(f2() == 11);
    }

    // Boost tests
    function_test();
}
