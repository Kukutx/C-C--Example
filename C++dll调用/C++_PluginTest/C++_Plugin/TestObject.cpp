#include "TestObject.h"

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� TestObject.h
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

// ���ǵ���������һ��ʾ����
int fntestPlugin1()
{
    return 42;
}

////���������
void* Instance()
{
    return new TestObject;
}
