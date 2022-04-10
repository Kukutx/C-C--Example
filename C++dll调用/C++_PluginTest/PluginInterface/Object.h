#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object
{
public:
    virtual ~Object() = default;
    virtual int Dump() = 0;
};

#endif //__OBJECT_H__