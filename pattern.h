#pragma once

#include "geometry.h"

#include <string>
#include <vector>

struct Measurements {
    double bust = 36.0;
    double waist = 28.0;
    double shoulderWidth = 15.0;
    double backWaistLength = 16.0;
    double neckWidth = 5.5;
    double armholeDepth = 8.0;
};

struct PatternPiece {
    std::string name;
    std::vector<Vec2> boundary;
};

PatternPiece generateFrontBodice(const Measurements& m);
PatternPiece generateBackBodice(const Measurements& m);
PatternPiece transformPiece(const PatternPiece& piece, const Mat2& matrix, const Vec2& translation);
double perimeter(const PatternPiece& piece);
