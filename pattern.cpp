#include "pattern.h"

#include <algorithm>

namespace {
void appendCurve(std::vector<Vec2>& boundary, const BezierCurve& curve) {
    std::vector<Vec2> points = sampleBezier(curve, 24);
    if (!boundary.empty() && !points.empty()) {
        points.erase(points.begin());
    }
    boundary.insert(boundary.end(), points.begin(), points.end());
}
}

PatternPiece generateFrontBodice(const Measurements& m) {
    PatternPiece piece;
    piece.name = "Front Bodice";

    double quarterBust = m.bust / 4.0 + 1.0;
    double quarterWaist = m.waist / 4.0 + 0.75;
    double length = m.backWaistLength + 0.5;
    double shoulderHalf = m.shoulderWidth / 2.0;
    double neckHalf = m.neckWidth / 2.0;

    Vec2 centerNeck{0.0, 3.0};
    Vec2 neckShoulder{neckHalf, 0.0};
    Vec2 shoulder{std::min(shoulderHalf, quarterBust - 0.5), 1.0};
    Vec2 underarm{quarterBust, m.armholeDepth};
    Vec2 waistSide{quarterWaist, length};
    Vec2 centerWaist{0.0, length};

    piece.boundary.push_back(centerNeck);

    BezierCurve neckline{
        centerNeck,
        {0.4, 1.4},
        {neckHalf - 0.5, 0.2},
        neckShoulder
    };
    appendCurve(piece.boundary, neckline);

    piece.boundary.push_back(shoulder);

    BezierCurve armhole{
        shoulder,
        {quarterBust - 1.8, 2.2},
        {quarterBust - 0.3, m.armholeDepth - 2.0},
        underarm
    };
    appendCurve(piece.boundary, armhole);

    piece.boundary.push_back(waistSide);
    piece.boundary.push_back(centerWaist);
    piece.boundary.push_back(centerNeck);
    return piece;
}

PatternPiece generateBackBodice(const Measurements& m) {
    PatternPiece piece;
    piece.name = "Back Bodice";

    double quarterBust = m.bust / 4.0 + 0.75;
    double quarterWaist = m.waist / 4.0 + 0.75;
    double length = m.backWaistLength;
    double shoulderHalf = m.shoulderWidth / 2.0;
    double neckHalf = m.neckWidth / 2.0;

    Vec2 centerNeck{0.0, 1.0};
    Vec2 neckShoulder{neckHalf, 0.0};
    Vec2 shoulder{std::min(shoulderHalf, quarterBust - 0.5), 0.8};
    Vec2 underarm{quarterBust, m.armholeDepth};
    Vec2 waistSide{quarterWaist, length};
    Vec2 centerWaist{0.0, length};

    piece.boundary.push_back(centerNeck);

    BezierCurve neckline{
        centerNeck,
        {0.5, 0.5},
        {neckHalf - 0.5, 0.1},
        neckShoulder
    };
    appendCurve(piece.boundary, neckline);

    piece.boundary.push_back(shoulder);

    BezierCurve armhole{
        shoulder,
        {quarterBust - 1.5, 2.5},
        {quarterBust - 0.2, m.armholeDepth - 2.0},
        underarm
    };
    appendCurve(piece.boundary, armhole);

    piece.boundary.push_back(waistSide);
    piece.boundary.push_back(centerWaist);
    piece.boundary.push_back(centerNeck);
    return piece;
}

PatternPiece transformPiece(const PatternPiece& piece, const Mat2& matrix, const Vec2& translation) {
    PatternPiece result;
    result.name = piece.name;
    result.boundary.reserve(piece.boundary.size());
    for (const Vec2& p : piece.boundary) {
        result.boundary.push_back(affineTransform(p, matrix, translation));
    }
    return result;
}

double perimeter(const PatternPiece& piece) {
    double total = 0.0;
    for (std::size_t i = 1; i < piece.boundary.size(); ++i) {
        total += distance(piece.boundary[i - 1], piece.boundary[i]);
    }
    return total;
}
