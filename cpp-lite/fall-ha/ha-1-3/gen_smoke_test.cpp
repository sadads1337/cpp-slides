#include <cassert>
#include <map>
#include <string>
#include <initializer_list>

#include "linked_ptr.hpp"

struct Cnt
{
public:
    Cnt(char const * name)
        : name_(name)
    {
        add_this();
    }

    virtual ~Cnt()
    {
        remove_this();
    }

    Cnt const * get_this() const
    {
        return this;
    }

    std::string get_name() const
    {
        return name_;
    }

private:
    typedef std::map<std::string, Cnt *> objects_map_t;

    static objects_map_t & objects()
    {
        static objects_map_t objects;
        return objects;
    }

    void add_this()
    {
        objects_map_t & objs = objects();

        assert(objs.find(name_) == objs.end());

        objs.insert(std::make_pair(name_, this));
    }

    void remove_this()
    {
        objects_map_t & objs = objects();

        auto it = objs.find(name_);

        assert(it != objs.end());
        assert(it->second == this);

        objs.erase(it);
    }

public:
    static void verify_state(
        std::initializer_list<char const *> should_be_objects)
    {
        // Get copy of objects map
        objects_map_t stored_objs = objects();
        for (char const * name: should_be_objects)
        {
            auto it = stored_objs.find(name);
            assert(it != stored_objs.end());
            stored_objs.erase(it);
        }

        assert(stored_objs.empty());
    }

private:
    std::string name_;
};

struct CntD : Cnt
{
    CntD(char const * name)
        : Cnt(name)
    {
        (void)fill_;
    }

private:
    int fill_;
};

typedef smart_ptr::linked_ptr<Cnt> cptr_t;
typedef smart_ptr::linked_ptr<CntD> cdptr_t;

int main()
{
    // Generated tests
    cdptr_t * p0 = new cdptr_t();
    Cnt::verify_state({});
    assert(true && !*p0);
    assert(true && (*p0).get() == nullptr);
    assert(true);
    assert(true && !(*p0).unique());

    cdptr_t * p1 = new cdptr_t();
    Cnt::verify_state({});
    assert(true && !*p0 && !*p1);
    assert(true && (*p0).get() == nullptr && (*p1).get() == nullptr);
    assert(true);
    assert(true && !(*p0).unique() && !(*p1).unique());

    cptr_t * p2 = new cptr_t();
    Cnt::verify_state({});
    assert(true && !*p2 && !*p0 && !*p1);
    assert(true && (*p2).get() == nullptr && (*p0).get() == nullptr && (*p1).get() == nullptr);
    assert(true);
    assert(true && !(*p2).unique() && !(*p0).unique() && !(*p1).unique());

    delete p2; p2 = nullptr;
    Cnt::verify_state({});
    assert(true && !*p0 && !*p1);
    assert(true && (*p0).get() == nullptr && (*p1).get() == nullptr);
    assert(true);
    assert(true && !(*p0).unique() && !(*p1).unique());

    cptr_t * p3 = new cptr_t(*p0);
    Cnt::verify_state({});
    assert(true && !*p3 && !*p0 && !*p1);
    assert(true && (*p3).get() == nullptr && (*p0).get() == nullptr && (*p1).get() == nullptr);
    assert(true);
    assert(true && !(*p3).unique() && !(*p0).unique() && !(*p1).unique());

    delete p3; p3 = nullptr;
    Cnt::verify_state({});
    assert(true && !*p0 && !*p1);
    assert(true && (*p0).get() == nullptr && (*p1).get() == nullptr);
    assert(true);
    assert(true && !(*p0).unique() && !(*p1).unique());

    delete p1; p1 = nullptr;
    Cnt::verify_state({});
    assert(true && !*p0);
    assert(true && (*p0).get() == nullptr);
    assert(true);
    assert(true && !(*p0).unique());

    cptr_t * p4 = new cptr_t(new Cnt("obj0"));
    Cnt::verify_state({"obj0"});
    assert(true && *p4 && !*p0);
    assert(true && (*p4)->get_this() == (*p4).get() && (*(*p4)).get_name() == "obj0" && (*p0).get() == nullptr);
    assert(true && *p4 == *p4);
    assert(true && (*p4).unique() && !(*p0).unique());

    delete p4; p4 = nullptr;
    Cnt::verify_state({});
    assert(true && !*p0);
    assert(true && (*p0).get() == nullptr);
    assert(true);
    assert(true && !(*p0).unique());

    delete p0; p0 = nullptr;
    Cnt::verify_state({});
    assert(true);
    assert(true);
    assert(true);
    assert(true);

    cptr_t * p5 = new cptr_t(new Cnt("obj1"));
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cdptr_t * p6 = new cdptr_t();
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p6);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p6).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p6).unique());

    delete p6; p6 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cdptr_t * p7 = new cdptr_t();
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p7);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p7).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p7).unique());

    delete p7; p7 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cptr_t * p8 = new cptr_t(new CntD("obj2"));
    Cnt::verify_state({"obj2", "obj1"});
    assert(true && *p5 && *p8);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p8)->get_this() == (*p8).get() && (*(*p8)).get_name() == "obj2");
    assert(true && *p8 == *p8 && *p5 == *p5 && *p5 != *p8);
    assert(true && (*p5).unique() && (*p8).unique());

    cptr_t * p9 = new cptr_t(*p5);
    Cnt::verify_state({"obj2", "obj1"});
    assert(true && *p8 && *p9 && *p5);
    assert(true && (*p8)->get_this() == (*p8).get() && (*(*p8)).get_name() == "obj2" && (*p9)->get_this() == (*p9).get() && (*(*p9)).get_name() == "obj1" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p8 == *p8 && *p9 == *p9 && *p9 != *p8);
    assert(true && (*p8).unique() && !(*p9).unique() && !(*p5).unique());

    delete p9; p9 = nullptr;
    Cnt::verify_state({"obj2", "obj1"});
    assert(true && *p8 && *p5);
    assert(true && (*p8)->get_this() == (*p8).get() && (*(*p8)).get_name() == "obj2" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p8 == *p8 && *p5 == *p5 && *p5 != *p8);
    assert(true && (*p8).unique() && (*p5).unique());

    delete p8; p8 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cptr_t * p10 = new cptr_t(new CntD("obj3"));
    Cnt::verify_state({"obj3", "obj1"});
    assert(true && *p10 && *p5);
    assert(true && (*p10)->get_this() == (*p10).get() && (*(*p10)).get_name() == "obj3" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p10 == *p10 && *p5 == *p5 && *p5 != *p10);
    assert(true && (*p10).unique() && (*p5).unique());

    delete p10; p10 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    *p5 = *p5;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cptr_t * p11 = new cptr_t(new CntD("obj4"));
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && (*p11).unique() && (*p5).unique());

    cptr_t * p12 = new cptr_t(*p11);
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p12);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p12)->get_this() == (*p12).get() && (*(*p12)).get_name() == "obj4");
    assert(true && *p11 == *p12 && *p5 == *p5 && *p5 != *p11);
    assert(true && !(*p11).unique() && (*p5).unique() && !(*p12).unique());

    cptr_t * p13 = new cptr_t(*p5);
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p12 && *p13);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p12)->get_this() == (*p12).get() && (*(*p12)).get_name() == "obj4" && (*p13)->get_this() == (*p13).get() && (*(*p13)).get_name() == "obj1");
    assert(true && *p12 == *p11 && *p5 == *p13 && *p13 != *p11);
    assert(true && !(*p11).unique() && !(*p5).unique() && !(*p12).unique() && !(*p13).unique());

    delete p13; p13 = nullptr;
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p12);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p12)->get_this() == (*p12).get() && (*(*p12)).get_name() == "obj4");
    assert(true && *p12 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && !(*p11).unique() && (*p5).unique() && !(*p12).unique());

    cptr_t * p14 = new cptr_t();
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p12 && !*p14);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p12)->get_this() == (*p12).get() && (*(*p12)).get_name() == "obj4" && (*p14).get() == nullptr);
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p12);
    assert(true && !(*p11).unique() && (*p5).unique() && !(*p12).unique() && !(*p14).unique());

    delete p14; p14 = nullptr;
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p12);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p12)->get_this() == (*p12).get() && (*(*p12)).get_name() == "obj4");
    assert(true && *p11 == *p12 && *p5 == *p5 && *p5 != *p12);
    assert(true && !(*p11).unique() && (*p5).unique() && !(*p12).unique());

    cdptr_t * p15 = new cdptr_t();
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p12 && !*p15);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p12)->get_this() == (*p12).get() && (*(*p12)).get_name() == "obj4" && (*p15).get() == nullptr);
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p12);
    assert(true && !(*p11).unique() && (*p5).unique() && !(*p12).unique() && !(*p15).unique());

    delete p15; p15 = nullptr;
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p12);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p12)->get_this() == (*p12).get() && (*(*p12)).get_name() == "obj4");
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && !(*p11).unique() && (*p5).unique() && !(*p12).unique());

    delete p12; p12 = nullptr;
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && (*p11).unique() && (*p5).unique());

    cdptr_t * p16 = new cdptr_t(new CntD("obj5"));
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p11 && *p5 && *p16);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p5 == *p5 && *p5 != *p11);
    assert(true && (*p11).unique() && (*p5).unique() && (*p16).unique());

    cptr_t * p17 = new cptr_t(*p5);
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p11 && *p5 && *p17 && *p16);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p5 == *p17 && *p17 != *p11);
    assert(true && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && (*p16).unique());

    cptr_t * p18 = new cptr_t(*p5);
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p18 && *p11 && *p5 && *p17 && *p16);
    assert(true && (*p18)->get_this() == (*p18).get() && (*(*p18)).get_name() == "obj1" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p5 == *p18 && *p5 != *p11);
    assert(true && !(*p18).unique() && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && (*p16).unique());

    cdptr_t * p19 = new cdptr_t();
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p18 && *p11 && *p5 && *p17 && !*p19 && *p16);
    assert(true && (*p18)->get_this() == (*p18).get() && (*(*p18)).get_name() == "obj1" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p19).get() == nullptr && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p17 == *p17 && *p18 != *p11);
    assert(true && !(*p18).unique() && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && !(*p19).unique() && (*p16).unique());

    cptr_t * p20 = new cptr_t(*p16);
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p18 && *p20 && *p11 && *p5 && *p17 && !*p19 && *p16);
    assert(true && (*p18)->get_this() == (*p18).get() && (*(*p18)).get_name() == "obj1" && (*p20)->get_this() == (*p20).get() && (*(*p20)).get_name() == "obj5" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p19).get() == nullptr && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p20 && *p5 == *p18 && *p18 != *p11);
    assert(true && !(*p18).unique() && !(*p20).unique() && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && !(*p19).unique() && !(*p16).unique());

    delete p20; p20 = nullptr;
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p18 && *p11 && *p5 && *p17 && !*p19 && *p16);
    assert(true && (*p18)->get_this() == (*p18).get() && (*(*p18)).get_name() == "obj1" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p19).get() == nullptr && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p5 == *p5 && *p17 != *p11);
    assert(true && !(*p18).unique() && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && !(*p19).unique() && (*p16).unique());

    delete p19; p19 = nullptr;
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p18 && *p11 && *p5 && *p17 && *p16);
    assert(true && (*p18)->get_this() == (*p18).get() && (*(*p18)).get_name() == "obj1" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p17 == *p18 && *p17 != *p11);
    assert(true && !(*p18).unique() && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && (*p16).unique());

    cptr_t * p21 = new cptr_t(*p16);
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p18 && *p21 && *p11 && *p5 && *p17 && *p16);
    assert(true && (*p18)->get_this() == (*p18).get() && (*(*p18)).get_name() == "obj1" && (*p21)->get_this() == (*p21).get() && (*(*p21)).get_name() == "obj5" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p21 == *p16 && *p11 == *p11 && *p11 != *p21 && *p17 == *p18 && *p17 != *p11);
    assert(true && !(*p18).unique() && !(*p21).unique() && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && !(*p16).unique());

    delete p21; p21 = nullptr;
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p18 && *p11 && *p5 && *p17 && *p16);
    assert(true && (*p18)->get_this() == (*p18).get() && (*(*p18)).get_name() == "obj1" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p17 == *p17 && *p18 != *p11);
    assert(true && !(*p18).unique() && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && (*p16).unique());

    delete p18; p18 = nullptr;
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p11 && *p5 && *p17 && *p16);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p17)->get_this() == (*p17).get() && (*(*p17)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p17 == *p17 && *p5 != *p11);
    assert(true && (*p11).unique() && !(*p5).unique() && !(*p17).unique() && (*p16).unique());

    delete p17; p17 = nullptr;
    Cnt::verify_state({"obj5", "obj4", "obj1"});
    assert(true && *p11 && *p5 && *p16);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p16)->get_this() == (*p16).get() && (*(*p16)).get_name() == "obj5");
    assert(true && *p16 == *p16 && *p11 == *p11 && *p11 != *p16 && *p5 == *p5 && *p5 != *p11);
    assert(true && (*p11).unique() && (*p5).unique() && (*p16).unique());

    delete p16; p16 = nullptr;
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && (*p11).unique() && (*p5).unique());

    cptr_t * p22 = new cptr_t(*p5);
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5 && *p22);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p22)->get_this() == (*p22).get() && (*(*p22)).get_name() == "obj1");
    assert(true && *p11 == *p11 && *p5 == *p22 && *p22 != *p11);
    assert(true && (*p11).unique() && !(*p5).unique() && !(*p22).unique());

    delete p22; p22 = nullptr;
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && (*p11).unique() && (*p5).unique());

    cptr_t * p23 = new cptr_t(*p11);
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p23 && *p11 && *p5);
    assert(true && (*p23)->get_this() == (*p23).get() && (*(*p23)).get_name() == "obj4" && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && !(*p23).unique() && !(*p11).unique() && (*p5).unique());

    delete p23; p23 = nullptr;
    Cnt::verify_state({"obj4", "obj1"});
    assert(true && *p11 && *p5);
    assert(true && (*p11)->get_this() == (*p11).get() && (*(*p11)).get_name() == "obj4" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p11 == *p11 && *p5 == *p5 && *p5 != *p11);
    assert(true && (*p11).unique() && (*p5).unique());

    delete p11; p11 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cptr_t * p24 = new cptr_t(new Cnt("obj6"));
    Cnt::verify_state({"obj6", "obj1"});
    assert(true && *p24 && *p5);
    assert(true && (*p24)->get_this() == (*p24).get() && (*(*p24)).get_name() == "obj6" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p24 == *p24 && *p5 == *p5 && *p5 != *p24);
    assert(true && (*p24).unique() && (*p5).unique());

    delete p24; p24 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cdptr_t * p25 = new cdptr_t();
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p25);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p25).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p25).unique());

    delete p25; p25 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cptr_t * p26 = new cptr_t();
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique());

    cdptr_t * p27 = new cdptr_t();
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5 && !*p27);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p27).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique() && !(*p27).unique());

    delete p27; p27 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique());

    cptr_t * p28 = new cptr_t(*p26);
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5 && !*p28);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p28).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique() && !(*p28).unique());

    p5->swap(*p5);
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5 && !*p28);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p28).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique() && !(*p28).unique());

    delete p28; p28 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique());

    cptr_t * p29 = new cptr_t();
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5 && !*p29);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p29).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique() && !(*p29).unique());

    delete p29; p29 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique());

    cptr_t * p30 = new cptr_t(new CntD("obj7"));
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p30 == *p30 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && (*p30).unique() && (*p5).unique());

    cptr_t * p31 = new cptr_t(*p30);
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p31 == *p30 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique());

    cdptr_t * p32 = new cdptr_t();
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5 && !*p32);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p32).get() == nullptr);
    assert(true && *p31 == *p30 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique() && !(*p32).unique());

    delete p32; p32 = nullptr;
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p31 == *p31 && *p5 == *p5 && *p5 != *p31);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique());

    cdptr_t * p33 = new cdptr_t();
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5 && !*p33);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p33).get() == nullptr);
    assert(true && *p31 == *p31 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique() && !(*p33).unique());

    delete p33; p33 = nullptr;
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p30 == *p31 && *p5 == *p5 && *p5 != *p31);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique());

    cptr_t * p34 = new cptr_t(*p30);
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && *p34 && !*p26 && *p30 && *p31 && *p5);
    assert(true && (*p34)->get_this() == (*p34).get() && (*(*p34)).get_name() == "obj7" && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p30 == *p31 && *p5 == *p5 && *p5 != *p31);
    assert(true && !(*p34).unique() && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique());

    delete p34; p34 = nullptr;
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p30 == *p31 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique());

    cptr_t * p35 = new cptr_t(*p30);
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5 && *p35);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p35)->get_this() == (*p35).get() && (*(*p35)).get_name() == "obj7");
    assert(true && *p30 == *p35 && *p5 == *p5 && *p5 != *p31);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique() && !(*p35).unique());

    delete p35; p35 = nullptr;
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p31 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p31)->get_this() == (*p31).get() && (*(*p31)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p31 == *p31 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && !(*p30).unique() && !(*p31).unique() && (*p5).unique());

    delete p31; p31 = nullptr;
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p30 == *p30 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && (*p30).unique() && (*p5).unique());

    cptr_t * p36 = new cptr_t(*p26);
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p36 && !*p26 && *p30 && *p5);
    assert(true && (*p36).get() == nullptr && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p30 == *p30 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p36).unique() && !(*p26).unique() && (*p30).unique() && (*p5).unique());

    delete p36; p36 = nullptr;
    Cnt::verify_state({"obj7", "obj1"});
    assert(true && !*p26 && *p30 && *p5);
    assert(true && (*p26).get() == nullptr && (*p30)->get_this() == (*p30).get() && (*(*p30)).get_name() == "obj7" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p30 == *p30 && *p5 == *p5 && *p5 != *p30);
    assert(true && !(*p26).unique() && (*p30).unique() && (*p5).unique());

    delete p30; p30 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && !*p26 && *p5);
    assert(true && (*p26).get() == nullptr && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && !(*p26).unique() && (*p5).unique());

    delete p26; p26 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    cdptr_t * p37 = new cdptr_t();
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique());

    cdptr_t * p38 = new cdptr_t(*p37);
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    cdptr_t * p39 = new cdptr_t(*p37);
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38 && !*p39);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr && (*p39).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique() && !(*p39).unique());

    cdptr_t * p40 = new cdptr_t(*p39);
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p40 && !*p38 && !*p39);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p40).get() == nullptr && (*p38).get() == nullptr && (*p39).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p40).unique() && !(*p38).unique() && !(*p39).unique());

    cptr_t * p41 = new cptr_t(new Cnt("obj8"));
    Cnt::verify_state({"obj8", "obj1"});
    assert(true && *p41 && *p5 && !*p37 && !*p40 && !*p38 && !*p39);
    assert(true && (*p41)->get_this() == (*p41).get() && (*(*p41)).get_name() == "obj8" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p40).get() == nullptr && (*p38).get() == nullptr && (*p39).get() == nullptr);
    assert(true && *p41 == *p41 && *p5 == *p5 && *p5 != *p41);
    assert(true && (*p41).unique() && (*p5).unique() && !(*p37).unique() && !(*p40).unique() && !(*p38).unique() && !(*p39).unique());

    delete p41; p41 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p40 && !*p38 && !*p39);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p40).get() == nullptr && (*p38).get() == nullptr && (*p39).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p40).unique() && !(*p38).unique() && !(*p39).unique());

    delete p40; p40 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38 && !*p39);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr && (*p39).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique() && !(*p39).unique());

    cptr_t * p42 = new cptr_t(*p5);
    Cnt::verify_state({"obj1"});
    assert(true && *p42 && *p5 && !*p37 && !*p38 && !*p39);
    assert(true && (*p42)->get_this() == (*p42).get() && (*(*p42)).get_name() == "obj1" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr && (*p39).get() == nullptr);
    assert(true && *p42 == *p5);
    assert(true && !(*p42).unique() && !(*p5).unique() && !(*p37).unique() && !(*p38).unique() && !(*p39).unique());

    delete p42; p42 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38 && !*p39);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr && (*p39).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique() && !(*p39).unique());

    delete p39; p39 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    cdptr_t * p43 = new cdptr_t(*p37);
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p43 && !*p37 && !*p38);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p43).get() == nullptr && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p43).unique() && !(*p37).unique() && !(*p38).unique());

    delete p43; p43 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    cptr_t * p44 = new cptr_t(new Cnt("obj9"));
    Cnt::verify_state({"obj9", "obj1"});
    assert(true && *p44 && *p5 && !*p37 && !*p38);
    assert(true && (*p44)->get_this() == (*p44).get() && (*(*p44)).get_name() == "obj9" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p44 == *p44 && *p5 == *p5 && *p5 != *p44);
    assert(true && (*p44).unique() && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    cdptr_t * p45 = new cdptr_t(*p37);
    Cnt::verify_state({"obj9", "obj1"});
    assert(true && *p44 && *p5 && !*p37 && !*p45 && !*p38);
    assert(true && (*p44)->get_this() == (*p44).get() && (*(*p44)).get_name() == "obj9" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p45).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p44 == *p44 && *p5 == *p5 && *p5 != *p44);
    assert(true && (*p44).unique() && (*p5).unique() && !(*p37).unique() && !(*p45).unique() && !(*p38).unique());

    cptr_t * p46 = new cptr_t(*p45);
    Cnt::verify_state({"obj9", "obj1"});
    assert(true && !*p46 && *p44 && *p5 && !*p37 && !*p45 && !*p38);
    assert(true && (*p46).get() == nullptr && (*p44)->get_this() == (*p44).get() && (*(*p44)).get_name() == "obj9" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p45).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p44 == *p44 && *p5 == *p5 && *p5 != *p44);
    assert(true && !(*p46).unique() && (*p44).unique() && (*p5).unique() && !(*p37).unique() && !(*p45).unique() && !(*p38).unique());

    delete p46; p46 = nullptr;
    Cnt::verify_state({"obj9", "obj1"});
    assert(true && *p44 && *p5 && !*p37 && !*p45 && !*p38);
    assert(true && (*p44)->get_this() == (*p44).get() && (*(*p44)).get_name() == "obj9" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p45).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p44 == *p44 && *p5 == *p5 && *p5 != *p44);
    assert(true && (*p44).unique() && (*p5).unique() && !(*p37).unique() && !(*p45).unique() && !(*p38).unique());

    delete p45; p45 = nullptr;
    Cnt::verify_state({"obj9", "obj1"});
    assert(true && *p44 && *p5 && !*p37 && !*p38);
    assert(true && (*p44)->get_this() == (*p44).get() && (*(*p44)).get_name() == "obj9" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p44 == *p44 && *p5 == *p5 && *p5 != *p44);
    assert(true && (*p44).unique() && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    delete p44; p44 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    cptr_t * p47 = new cptr_t(new Cnt("obj10"));
    Cnt::verify_state({"obj10", "obj1"});
    assert(true && *p47 && *p5 && !*p37 && !*p38);
    assert(true && (*p47)->get_this() == (*p47).get() && (*(*p47)).get_name() == "obj10" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p47 == *p47 && *p5 == *p5 && *p5 != *p47);
    assert(true && (*p47).unique() && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    cptr_t * p48 = new cptr_t(*p47);
    Cnt::verify_state({"obj10", "obj1"});
    assert(true && *p47 && *p5 && *p48 && !*p37 && !*p38);
    assert(true && (*p47)->get_this() == (*p47).get() && (*(*p47)).get_name() == "obj10" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p48)->get_this() == (*p48).get() && (*(*p48)).get_name() == "obj10" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p47 == *p47 && *p5 == *p5 && *p5 != *p48);
    assert(true && !(*p47).unique() && (*p5).unique() && !(*p48).unique() && !(*p37).unique() && !(*p38).unique());

    delete p48; p48 = nullptr;
    Cnt::verify_state({"obj10", "obj1"});
    assert(true && *p47 && *p5 && !*p37 && !*p38);
    assert(true && (*p47)->get_this() == (*p47).get() && (*(*p47)).get_name() == "obj10" && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p47 == *p47 && *p5 == *p5 && *p5 != *p47);
    assert(true && (*p47).unique() && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    delete p47; p47 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37 && !*p38);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr && (*p38).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique() && !(*p38).unique());

    delete p38; p38 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5 && !*p37);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1" && (*p37).get() == nullptr);
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique() && !(*p37).unique());

    delete p37; p37 = nullptr;
    Cnt::verify_state({"obj1"});
    assert(true && *p5);
    assert(true && (*p5)->get_this() == (*p5).get() && (*(*p5)).get_name() == "obj1");
    assert(true && *p5 == *p5);
    assert(true && (*p5).unique());

    delete p5; p5 = nullptr;
    Cnt::verify_state({});
    assert(true);
    assert(true);
    assert(true);
    assert(true);
}
