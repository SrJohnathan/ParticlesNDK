//
// Created by Johnathan on 30/06/2020.
//

#include "Vector4Map.h"

Vector4Map::Vector4Map() {

}

Vector4Map::~Vector4Map() {

}


Effekseer::Matrix44 Vector4Map::map( float_t flat[]) {

    auto vec = Effekseer::Matrix44();

  vec.Values[0][0] = flat[0];
  vec.Values[0][1] = flat[1];
  vec.Values[0][2] = flat[2];
  vec.Values[0][3] = flat[3];
  vec.Values[1][0] = flat[4];
  vec.Values[1][1] = flat[5];
  vec.Values[1][2] = flat[6];
  vec.Values[1][3] = flat[7];
  vec.Values[2][0] = flat[8];
  vec.Values[2][1] = flat[9];
  vec.Values[2][2] = flat[10];
  vec.Values[2][3] = flat[11];
  vec.Values[3][0] = flat[12];
  vec.Values[3][1] = flat[13];
  vec.Values[3][2] = flat[14];
  vec.Values[3][3] = flat[15];


    return vec;
}
