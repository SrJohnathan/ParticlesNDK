#pragma once

#include <Effekseer.h>
class Vector4Map {


public:
    Vector4Map();
    ~Vector4Map();
    Effekseer::Matrix44 map( float_t flat[]);
};



