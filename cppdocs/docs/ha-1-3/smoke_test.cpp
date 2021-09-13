#include <iostream>
#include <set>
#include <cassert>

#include "linked_ptr.hpp" // solution header file

//////////////////////////////////////////////////////
struct Base
{
    virtual void echo()
    {
        std::cout << "base" << std::endl;
    }

    virtual ~Base()
    {
    }
};

struct Derived : Base
{
    virtual void echo()
    {
        std::cout << "derived" << std::endl;
    }
};

using smart_ptr::linked_ptr;


void check_ctor(linked_ptr<int > /*ptr*/)
{
}

void check_ctor(linked_ptr<Base> /*ptr*/)
{
}

void compile_err_ctor()
{
    // This code shouldn't compile

    /*
    int * i = new int(42);
    check_ctor(i);

    linked_ptr<int> j = new int(5);
    */
}

void construct_check()
{
    linked_ptr<Derived> d(new Derived);
    check_ctor(linked_ptr<Base>(d));

    linked_ptr<Derived> d2(d);
    d2 = d;

    linked_ptr<Derived> d3;
    linked_ptr<Base> b2 = d3;
    linked_ptr<Base> b;// = d2;

    assert(d2 != b);
}

void op_check()
{
    linked_ptr<Base> b(new Derived);
    (*b).echo();
    b->echo();
}

void misc_check()
{
    linked_ptr<Base> b;
    linked_ptr<Base> b2(new Base);

    b.swap(b2);
    assert(b.unique());

    b.reset(new Base);
    assert(b);
}

void less_check()
{
    std::set<linked_ptr<int> > pointers;
}

int main()
{
    compile_err_ctor();
    construct_check();
    op_check();
    misc_check();
    less_check();
}
