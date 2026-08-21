#include "geometry.h"

#include <cmath>

Vec2 add(const Vec2& a, const Vec2& b) {
    return {a.x + b.x, a.y + b.y};
}

Vec2 subtract(const Vec2& a, const Vec2& b) {
    return {a.x - b.x, a.y - b.y};
}

Vec2 multiply(const Mat2& m, const Vec2& p) {
    return {
        m.a11 * p.x + m.a12 * p.y,
        m.a21 * p.x + m.a22 * p.y
    };
}

Vec2 affineTransform(const Vec2& p, const Mat2& m, const Vec2& translation) {
    return add(multiply(m, p), translation);
}

Mat2 scaleMatrix(double sx, double sy) {
    return {sx, 0.0, 0.0, sy};
}

Mat2 rotationMatrix(double radians) {
    double c = std::cos(radians);
    double s = std::sin(radians);
    return {c, -s, s, c};
}

double distance(const Vec2& a, const Vec2& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

Vec2 evaluateBezier(const BezierCurve& c, double t) {
    double u = 1.0 - t;
    double b0 = u * u * u;
    double b1 = 3.0 * u * u * t;
    double b2 = 3.0 * u * t * t;
    double b3 = t * t * t;

    return {
        b0 * c.p0.x + b1 * c.p1.x + b2 * c.p2.x + b3 * c.p3.x,
        b0 * c.p0.y + b1 * c.p1.y + b2 * c.p2.y + b3 * c.p3.y
    };
}

double approximateBezierLength(const BezierCurve& curve, int samples) {
    double length = 0.0;
    Vec2 previous = curve.p0;
    for (int i = 1; i <= samples; ++i) {
        Vec2 current = evaluateBezier(curve, static_cast<double>(i) / samples);
        length += distance(previous, current);
        previous = current;
    }
    return length;
}

std::vector<Vec2> sampleBezier(const BezierCurve& curve, int samples) {
    std::vector<Vec2> points;
    points.reserve(samples + 1);
    for (int i = 0; i <= samples; ++i) {
        points.push_back(evaluateBezier(curve, static_cast<double>(i) / samples));
    }
    return points;
}
