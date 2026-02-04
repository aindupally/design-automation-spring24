#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>



using namespace std;

// Represents a control point in 3D space
struct ControlPoint {
    double x, y, z; // Coordinates
    double weight;  // Weight for NURBS
};

// Calculate NURBS basis function
double calculateNURBSBasis(int index, int degree, double param, const vector<double>& knots) {
    if (degree == 0) {
        return (knots[index] <= param && param < knots[index + 1]) ? 1.0 : 0.0;
    }

    double term1 = 0.0, term2 = 0.0;
    double denominator1 = knots[index + degree] - knots[index];
    double denominator2 = knots[index + degree + 1] - knots[index + 1];

    // Handle potential divide-by-zero cases
    if (std::abs(denominator1) > std::numeric_limits<double>::epsilon()) {
        term1 = (param - knots[index]) / denominator1;
    }

    if (std::abs(denominator2) > std::numeric_limits<double>::epsilon()) {
        term2 = (knots[index + degree + 1] - param) / denominator2;
    }

    return term1 * calculateNURBSBasis(index, degree - 1, param, knots) +
           term2 * calculateNURBSBasis(index + 1, degree - 1, param, knots);
}

// Transform parameter from [0, 1] to the original coordinate system
double transformParameter(double param, double minVal, double maxVal) {
    return minVal + param * (maxVal - minVal);
}

// Interpolate a surface point using NURBS
vector<double> interpolateSurface(double u, double v, const vector<ControlPoint>& controlPoints, const vector<double>& uKnots, const vector<double>& vKnots, int uDegree, int vDegree) {
    double uMin = *min_element(uKnots.begin() + uDegree, uKnots.end() - uDegree);
    double uMax = *max_element(uKnots.begin() + uDegree, uKnots.end() - uDegree);
    double vMin = *min_element(vKnots.begin() + vDegree, vKnots.end() - vDegree);
    double vMax = *max_element(vKnots.begin() + vDegree, vKnots.end() - vDegree);

    // Transform parameters back to the original coordinate system
    double originalU = transformParameter(u, uMin, uMax);
    double originalV = transformParameter(v, vMin, vMax);

    vector<double> surfacePoint(3, 0.0); // Initialize to (0, 0, 0)

    size_t uSize = uKnots.size() - uDegree - 1;
    size_t vSize = vKnots.size() - vDegree - 1;

    // Validate knot vector sizes
    if (uSize < uDegree || vSize < vDegree) {
        cerr << "Error: Invalid knot vector sizes." << endl;
        return surfacePoint;
    }

    size_t numControlPoints = controlPoints.size();

    for (size_t i = 0; i <= uSize; ++i) {
        for (size_t j = 0; j <= vSize; ++j) {
            double uBasis = calculateNURBSBasis(i, uDegree, originalU, uKnots);
            double vBasis = calculateNURBSBasis(j, vDegree, originalV, vKnots);
            double basisProduct = uBasis * vBasis;

            double weightSum = 0.0;
            double weightedSumX = 0.0, weightedSumY = 0.0, weightedSumZ = 0.0;

            for (size_t k = 0; k < numControlPoints; ++k) {
                double weightedBasis = basisProduct * controlPoints[k].weight;
                weightSum += weightedBasis;
                weightedSumX += weightedBasis * controlPoints[k].x;
                weightedSumY += weightedBasis * controlPoints[k].y;
                weightedSumZ += weightedBasis * controlPoints[k].z;
            }

            if (std::abs(weightSum) > std::numeric_limits<double>::epsilon()) {
                surfacePoint[0] += weightedSumX / weightSum;
                surfacePoint[1] += weightedSumY / weightSum;
                surfacePoint[2] += weightedSumZ / weightSum;
            }
        }
    }

    return surfacePoint;
}