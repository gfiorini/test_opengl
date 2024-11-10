//
// Created by gfiorini on 11/10/24.
//
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>
#include "../Tests.h"


namespace Test {
    class BaseTest;
}

class SimpleClass {
    public:
        SimpleClass(int x) : m_Value(x){}
        SimpleClass() : m_Value(69) {}
    private:
    int m_Value;

    public:
        [[nodiscard]] int get_m_value() const {
            return m_Value;
        }
};
template<typename T>
T add(T a, T b) {
    return a + b;
}

template<typename T>
T* create() {
    return new T();
}

template<typename T>
T* create(int x) {
    return new T(x);
}

void testLambda() {

    SimpleClass* c1 = create<SimpleClass>(55);
    std::cout << "SimpleClass c1 value: " << c1->get_m_value() << std::endl;

    //SimpleClass *(* f)() ;
    SimpleClass *(* gen2)() = create<SimpleClass>;
    //SimpleClass *(* func)(int x)
    SimpleClass *(* gen3)(int x) = create<SimpleClass>;

    SimpleClass* c2 = gen2();
    std::cout << "c2 value: " << c2->get_m_value() << std::endl;

    SimpleClass* c3 = gen3(123);
    std::cout << "c3 value: " << c3->get_m_value() << std::endl;

    std::vector<std::pair<std::string, std::function<Test::BaseTest*()>>> v;



}
