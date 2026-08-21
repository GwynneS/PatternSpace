#pragma once

#include <string>
#include <vector>

struct PatternExample {
    std::string name;
    std::vector<double> features;
};

double euclideanDistance(const std::vector<double>& a, const std::vector<double>& b);
int nearestPattern(const std::vector<double>& query, const std::vector<PatternExample>& examples);
