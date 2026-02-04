#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
};

// Function to perform knot insertion on NURBS curve
vector<Point> knotInsertion(const vector<Point>& controlPoints, const vector<double>& knots, double newKnot) {
    // Insert newKnot into the knots vector
    vector<double> newKnots(knots);
    newKnots.push_back(newKnot);
    sort(newKnots.begin(), newKnots.end());

    // Compute new control points using the knot insertion algorithm
    vector<Point> newControlPoints;
    int degree = knots.size() - controlPoints.size() - 1;
    int k = distance(knots.begin(), lower_bound(knots.begin(), knots.end(), newKnot));
    for (int i = 0; i < controlPoints.size(); ++i) {
        Point p = { 0, 0 };
        for (int j = max(0, i - degree); j <= min(i, (int)k - degree); ++j) {
            double denom = knots[j + degree] - knots[j];
            double alpha = denom != 0 ? (newKnot - knots[j]) / denom : 0; // Avoid division by zero
            p.x += controlPoints[j].x * (1 - alpha);
            p.y += controlPoints[j].y * (1 - alpha);
        }
        for (int j = max(0, i - degree + 1); j <= min(i + 1, (int)k - degree); ++j) {
            double denom = knots[j + degree] - knots[j];
            double alpha = denom != 0 ? (newKnot - knots[j]) / denom : 0; // Avoid division by zero
            p.x += controlPoints[j].x * alpha;
            p.y += controlPoints[j].y * alpha;
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
    cout << "Enter the number of knots: ";
    cin >> numKnots;

    vector<double> knots(numKnots);
    cout << "Enter the knots in non-decreasing order:" << endl;
    for (int i = 0; i < numKnots; ++i) {
        cin >> knots[i];
    }

    double newKnot;
    cout << "Enter the new knot to be inserted: ";
    cin >> newKnot;

    // Perform knot insertion
    vector<Point> newControlPoints = knotInsertion(controlPoints, knots, newKnot);

    // Output the result
    cout << "New control points after knot insertion:" << endl;
    for (const auto& point : newControlPoints) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    return 0;
}
