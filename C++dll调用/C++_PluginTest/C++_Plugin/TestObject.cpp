#include "TestObject.h"

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 TestObject.h
int TestObject::Dump()
{
    this->ntestPlugin1 = 2021;
    std::cout << "class name : TestObject   function name:Dump() " << this->ntestPlugin1 << std::endl;
    return 0;
}

int add(int a, int b)
{
    return a + b;
}
int sub(int a, int b)
{
    return a - b;
}

// 这是导出函数的一个示例。
int fntestPlugin1()
{
    return 42;
}

////返回类对象
void* Instance()
{
    return new TestObject;
}
