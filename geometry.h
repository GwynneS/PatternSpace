#pragma once

#include <vector>

struct Vec2 {
    double x = 0.0;
    double y = 0.0;
};

struct Mat2 {
    double a11 = 1.0;
    double a12 = 0.0;
    double a21 = 0.0;
    double a22 = 1.0;
};

struct BezierCurve {
    Vec2 p0;
    Vec2 p1;
    Vec2 p2;
    Vec2 p3;
};

Vec2 add(const Vec2& a, const Vec2& b);
Vec2 subtract(const Vec2& a, const Vec2& b);
Vec2 multiply(const Mat2& matrix, const Vec2& point);
Vec2 affineTransform(const Vec2& point, const Mat2& matrix, const Vec2& translation);
Mat2 scaleMatrix(double sx, double sy);
Mat2 rotationMatrix(double radians);
double distance(const Vec2& a, const Vec2& b);
Vec2 evaluateBezier(const BezierCurve& curve, double t);
double approximateBezierLength(const BezierCurve& curve, int samples = 100);
std::vector<Vec2> sampleBezier(const BezierCurve& curve, int samples = 30);
