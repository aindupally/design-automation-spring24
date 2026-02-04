#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

// Function to calculate the Bernstein polynomial value
double bernstein(int degree, int i, const vector<double>& knots, int knotIndex) {
    if (degree == 0) {
        return (knots[knotIndex] <= knots[i] && knots[i] < knots[knotIndex + 1]) ? 1.0 : 0.0;
    }
    double t = knots[knotIndex];
    double t1 = knots[i];
    double t2 = knots[i + degree];
    double denom1 = (t2 - t);
    double denom2 = (t2 - t1);
    double b1 = (denom1 != 0) ? ((t - t1) / denom1) : 0.0;
    double b2 = (denom2 != 0) ? ((t2 - t) / denom2) : 0.0;
    return b1 * bernstein(degree - 1, i, knots, knotIndex) + b2 * bernstein(degree - 1, i + 1, knots, knotIndex);
}

// Function to perform knot refinement on NURBS curve
vector<Point> knotRefinement(const vector<Point>& controlPoints, const vector<double>& knots, const vector<double>& newKnots) {
    // Combine original knots with new knots
    vector<double> refinedKnots(knots);
    refinedKnots.insert(refinedKnots.end(), newKnots.begin(), newKnots.end());
    sort(refinedKnots.begin(), refinedKnots.end());

    // Compute new control points using the knot refinement algorithm
    vector<Point> newControlPoints;
    int degree = knots.size() - controlPoints.size() - 1;
    for (size_t i = 0; i < controlPoints.size(); ++i) {
        Point p = { 0, 0 };
        for (size_t j = 0; j <= i; ++j) {
            p.x += controlPoints[j].x * bernstein(degree, j, refinedKnots, i);
            p.y += controlPoints[j].y * bernstein(degree, j, refinedKnots, i);
        }
        newControlPoints.push_back(p);
    }

    return newControlPoints;
}

int main() {
    int numControlPoints;
    cout << "Enter the number of control points: ";
    cin >> numControlPoints;

    vector<Point> controlPoints(numControlPoints);
    cout << "Enter the control points (format: x y):" << endl;
    for (int i = 0; i < numControlPoints; ++i) {
        cin >> controlPoints[i].x >> controlPoints[i].y;
    }

    int numKnots;
    cout << "Enter the number of initial knots: ";
    cin >> numKnots;

    vector<double> knots(numKnots);
    cout << "Enter the initial knots in non-decreasing order:" << endl;
    for (int i = 0; i < numKnots; ++i) {
        cin >> knots[i];
    }

    int numNewKnots;
    cout << "Enter the number of new knots for refinement: ";
    cin >> numNewKnots;

    vector<double> newKnots(numNewKnots);
    cout << "Enter the new knots for refinement in non-decreasing order:" << endl;
    for (int i = 0; i < numNewKnots; ++i) {
        cin >> newKnots[i];
    }

    // Perform knot refinement
    vector<Point> newControlPoints = knotRefinement(controlPoints, knots, newKnots);

    // Output the result
    cout << "New control points after knot refinement:" << endl;
    for (const auto& point : newControlPoints) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    return 0;
}
