#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <tuple>
#include "main.h"

// Function to calculate binomial coefficient (n choose k)
int binomialCoeff(int n, int k) {
    if (k == 0 || k == n) return 1;
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}

// Function prototype
std::tuple<double, double, double> bezierSurfacePoint(const std::vector<std::vector<std::tuple<double, double, double>>>& controlPoints, double u, double v);

// Function to calculate bezier surface point
std::tuple<double, double, double> bezierSurfacePoint(const std::vector<std::vector<std::tuple<double, double, double>>>& controlPoints, double u, double v) {
    int m = controlPoints.size() - 1; // rows
    int n = controlPoints[0].size() - 1; // columns
    double x = 0.0, y = 0.0, z = 0.0;
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            double bi = binomialCoeff(m, i) * pow(u, i) * pow(1 - u, m - i);
            double bj = binomialCoeff(n, j) * pow(v, j) * pow(1 - v, n - j);
            x += std::get<0>(controlPoints[i][j]) * bi * bj;
            y += std::get<1>(controlPoints[i][j]) * bi * bj;
            z += std::get<2>(controlPoints[i][j]) * bi * bj;
        }
    }
    return std::make_tuple(x, y, z);
}