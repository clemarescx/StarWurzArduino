#ifndef _MATHHELPERS_H
#define _MATHHELPERS_H

#include <MatrixMath.h>

namespace Utils
{

struct Point
{
  byte x;
  byte y;
};

// struct Vec3
// {
//   int16_t v[3];

//   Vec3(int16_t _x, int16_t _y, int16_t _z)
//   {
//     v[0] = _x;
//     v[1] = _y;
//     v[2] = _z;
//   }
//   Vec3(int16_t val)
//   {
//     v[0] = val;
//     v[1] = val;
//     v[2] = val;
//   }

//   int16_t x() { return v[0]; }
//   int16_t y() { return v[1]; }
//   int16_t z() { return v[2]; }

//   Vec3 operator+(const Vec3 &rhs)
//   {
//     return Vec3(this->v[0] + rhs.v[0], this->v[1] + rhs.v[1], this->v[2] + rhs.v[2]);
//   }
//   Vec3 operator-(const Vec3 &rhs)
//   {
//     return Vec3(this->v[0] - rhs.v[0], this->v[1] - rhs.v[1], this->v[2] - rhs.v[2]);
//   }
//   Vec3 operator/(const float &scalar)
//   {
//     return Vec3(this->v[0] / scalar, this->v[1] / scalar, this->v[2] / scalar);
//   }
//   Vec3 operator*(const float &scalar)
//   {
//     return Vec3(this->v[0] * scalar, this->v[1] * scalar, this->v[2] * scalar);
//   }
//   Vec3 operator-()
//   {
//     return Vec3(-this->v[0], -this->v[1], -this->v[2]);
//   }
// };
// struct Vec4
// {
//   int16_t v[4];

//   Vec4(int16_t init)
//   {
//     v[0] = init;
//     v[1] = init;
//     v[2] = init;
//     v[3] = 1;
//   }
//   Vec4(int16_t _x, int16_t _y, int16_t _z, int16_t _w = 1)
//   {
//     v[0] = _x;
//     v[1] = _y;
//     v[2] = _z;
//     v[3] = _w;
//   }
//   Vec4(Vec3 _v, int16_t _w = 1)
//   {
//     v[0] = _v.v[0];
//     v[1] = _v.v[1];
//     v[2] = _v.v[2];
//     v[3] = _w;
//   }

//   int16_t x() { return v[0]; }
//   int16_t y() { return v[1]; }
//   int16_t z() { return v[2]; }
//   int16_t w() { return v[3]; }

//   Vec4 operator+(const Vec4 &rhs)
//   {
//     return Vec4(this->v[0] + rhs.v[0], this->v[1] + rhs.v[1], this->v[2] + rhs.v[2], this->v[3]);
//   }
//   Vec4 operator-(const Vec4 &rhs)
//   {
//     return Vec4(this->v[0] - rhs.v[0], this->v[1] - rhs.v[1], this->v[2] - rhs.v[2], this->v[3]);
//   }
//   Vec4 operator/(const float &scalar)
//   {
//     return Vec4(this->v[0] / scalar, this->v[1] / scalar, this->v[2] / scalar, this->v[3] / scalar);
//   }
//   Vec4 operator-()
//   {
//     return Vec4(-this->v[0], -this->v[1], -this->v[2], this->v[3]);
//   }
//   Vec4 operator*(const float &scalar)
//   {
//     return Vec4(this->v[0] * scalar, this->v[1] * scalar, this->v[2] * scalar, this->v[3] * scalar);
//   }
// };
// struct Mat4
// {
//   // float x[4], y[4], z[4], w[4];
//   float m[4][4];

//   Mat4()
//   {
//     initMatrix();
//   }
//   initMatrix()
//   {
//     for (int i = 0; i < 4; i++)
//       for (int j = 0; j < 4; j++)
//         if (i == j)
//           m[i][j] = 1.f;
//         else
//           m[i][j] = 0.f;
//   }

//   float *operator[](int i)
//   {
//     switch (i)
//     {
//     case 0:
//       return m[0];
//     case 1:
//       return m[1];
//     case 2:
//       return m[2];
//     case 3:
//       return m[3];
//     }
//   }
// };
// static Mat4 transpose(Mat4 &m)
// {
//   Mat4 res;
//   Matrix.Transpose((float *)m.m, 4, 4, (float *)res.m);
//   return res;
// }
// static void print(Mat4 &m)
// {
//   Matrix.Print((float *)m.m, 4, 4, "");
// }

// void printVector(const Vec3 &v)
// {
//   Serial.print("[");
//   Serial.print(v.x());
//   Serial.print(", ");
//   Serial.print(v.y());
//   Serial.print(", ");
//   Serial.print(v.z());
//   Serial.println("]");
// }

// void printVector(const Vec4 &v)
// {
//   Serial.print("[");
//   Serial.print(v.x());
//   Serial.print(", ");
//   Serial.print(v.y());
//   Serial.print(", ");
//   Serial.print(v.z());
//   Serial.print(", ");
//   Serial.print(v.w());
//   Serial.println("]");
// }
/*
inline static void drawPointToPoint(const Vec4 &start, const Vec4 &stop, const uint16_t &color)
{
  tft.drawLine(start.x(), start.y(), stop.x(), stop.y(), color);
}

inline static void drawVector(const Vec4 &start, const Vec4 &vec, const uint16_t &color)
{
  tft.drawLine(start.x(), start.y(), start.x() + vec.x(), start.y() + vec.y(), color);
}
*/
}

#endif



















































































