#include "similarity.h"

#include <cmath>
#include <limits>
#include <stdexcept>

double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Feature vectors must have the same dimension.");
    }

    double sum = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        double difference = a[i] - b[i];
        sum += difference * difference;
    }
    return std::sqrt(sum);
}

int nearestPattern(const std::vector<double>& query, const std::vector<PatternExample>& examples) {
    if (examples.empty()) return -1;

    int bestIndex = -1;
    double bestDistance = std::numeric_limits<double>::infinity();

    for (std::size_t i = 0; i < examples.size(); ++i) {
        double d = euclideanDistance(query, examples[i].features);
        if (d < bestDistance) {
            bestDistance = d;
            bestIndex = static_cast<int>(i);
        }
    }
    return bestIndex;
}
