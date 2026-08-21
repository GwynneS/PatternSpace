#include "geometry.h"
#include "pattern.h"
#include "similarity.h"
#include "svg.h"

#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    Measurements measurements;
    measurements.bust = 36.0;
    measurements.waist = 28.0;
    measurements.shoulderWidth = 15.0;
    measurements.backWaistLength = 16.0;
    measurements.neckWidth = 5.5;
    measurements.armholeDepth = 8.0;

    PatternPiece front = generateFrontBodice(measurements);
    PatternPiece back = generateBackBodice(measurements);

    std::vector<PatternExample> library = {
        {"fitted bodice", {0.78, 0.42, 0.22, 0.15}},
        {"relaxed bodice", {0.90, 0.48, 0.30, 0.10}},
        {"high-neck bodice", {0.80, 0.35, 0.10, 0.08}}
    };

    // Placeholder image-derived features: waist/bust ratio, normalized length,
    // neckline depth, and silhouette curvature. A future OpenCV stage will
    // estimate these values from front/back photographs.
    std::vector<double> observedFeatures = {
        measurements.waist / measurements.bust,
        measurements.backWaistLength / measurements.bust,
        0.20,
        0.14
    };

    int match = nearestPattern(observedFeatures, library);

    std::cout << "PatternSpace prototype\n\n";
    std::cout << "Measurements: " << measurements.bust << " in bust, "
              << measurements.waist << " in waist\n";

    if (match >= 0) {
        std::cout << "Nearest feature-space template: " << library[match].name << "\n";
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Front boundary length: " << perimeter(front) << " in\n";
    std::cout << "Back boundary length:  " << perimeter(back) << " in\n";

    // Demonstrate a linear transformation: 2% horizontal grading and
    // 1% vertical grading applied to a copy of the front piece.
    Mat2 grading = scaleMatrix(1.02, 1.01);
    PatternPiece gradedFront = transformPiece(front, grading, {0.0, 0.0});
    std::cout << "Graded front boundary length: " << perimeter(gradedFront) << " in\n";

    writePatternSVG("patternspace_output.svg", {front, back});
    std::cout << "\nGenerated patternspace_output.svg\n";
    return 0;
}
