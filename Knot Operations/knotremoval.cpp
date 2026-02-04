#include <iostream>
#include <vector>

using namespace std;

struct Point {
    double x, y;
};

// Function to calculate B-spline's basis function
double basisFunction(int i, int k, double t, const vector<double>& knots) 
{
    if (k == 1) 
    {
        if (knots[i] <= t && t < knots[i+1])
            return 1;
        return 0;
    }

    double denom1 = knots[i+k-1] - knots[i];
    double denom2 = knots[i+k] - knots[i+1];

    double term1 = 0, term2 = 0;

    if (denom1 != 0)
        term1 = ((t - knots[i]) / denom1) * basisFunction(i, k-1, t, knots);
    
    if (denom2 != 0)
        term2 = ((knots[i+k] - t) / denom2) * basisFunction(i+1, k-1, t, knots);

    return term1 + term2;
}

// Function to derive the B-spline curve
Point computeBSplineCurve(int degree, const vector<Point>& controlPoints, const vector<double>& knots, double t) 
{
    Point result = {0, 0};

    int n = controlPoints.size();
    for (int i = 0; i < n; ++i) 
    {
        double basis = basisFunction(i, degree+1, t, knots);
        result.x += basis * controlPoints[i].x;
        result.y += basis * controlPoints[i].y;
    }

    return result;
}

// Function to remove a knot
void removeKnot(vector<Point>& controlPoints, vector<double>& knots, int knotToRemove) 
{
    // Remove knot value
    knots.erase(knots.begin() + knotToRemove);

    // Remove corresponding control point
    controlPoints.erase(controlPoints.begin() + knotToRemove - 1);
}

int main() 
{
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

    int knotToRemove;
    cout << "Enter the index of the knot to remove: ";
    cin >> knotToRemove;

    // Perform knot removal
    removeKnot(controlPoints, knots, knotToRemove);

    // Output the updated control points and knots
    cout << "Updated control points after knot removal:" << endl;
    for (const auto& point : controlPoints) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    cout << "Updated knots after knot removal:" << endl;
    for (const auto& knot : knots) {
        cout << knot << " ";
    }
    cout << endl;

    return 0;
}
