#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

// Structure to represent a 3D point
struct Point {
    double x, y, z, w; // w is the weight
};

// Function to calculate B-spline basis function value at parameter t
double basis(int i, int k, double t, const vector<double>& knots) {
    if (k == 1) {
        if (knots[i] <= t && t < knots[i + 1]) return 1.0;
        return 0.0;
    }
    double denom1 = knots[i + k - 1] - knots[i];
    double denom2 = knots[i + k] - knots[i + 1];
    double coeff1 = (denom1 == 0) ? 0 : ((t - knots[i]) / denom1);
    double coeff2 = (denom2 == 0) ? 0 : ((knots[i + k] - t) / denom2);
    return coeff1 * basis(i, k - 1, t, knots) + coeff2 * basis(i + 1, k - 1, t, knots);
}

// Function to compute the B-spline curve point at parameter t
Point bsplineCurvePoint(double t, const vector<double>& knots, const vector<Point>& controlPoints, int degree) {
    Point result = { 0, 0, 0, 0 };
    double w_denominator = 0.0;

    int n = controlPoints.size() - 1;
    for (int i = 0; i <= n; ++i) {
        double blend = basis(i, degree + 1, t, knots);
        double weight = controlPoints[i].w;
        result.x += blend * controlPoints[i].x * weight;
        result.y += blend * controlPoints[i].y * weight;
        result.z += blend * controlPoints[i].z * weight;
        w_denominator += blend * weight;
    }

    // Handle division by zero
    if (w_denominator == 0.0) {
        throw runtime_error("Division by zero error: sum of weights is zero.");
    }

    result.x /= w_denominator;
    result.y /= w_denominator;
    result.z /= w_denominator;
    return result;
}

// Function to write curve data to a file
void writeCurveToFile(const vector<Point>& curvePoints, const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error: Unable to open the file!" << endl;
        return;
    }

    for (const auto& point : curvePoints) {
        outfile << point.x << " " << point.y << " " << point.z << endl;
    }

    outfile.close();
    cout << "Curve data written to " << filename << endl;
}

int main() {
    try {
        // User input for B-spline parameters
        int numControlPoints;
        cout << "Enter the number of control points: ";
        cin >> numControlPoints;
        if (numControlPoints < 2) {
            throw invalid_argument("Number of control points must be at least 2.");
        }

        int degree;
        cout << "Enter the degree of B-spline curve: ";
        cin >> degree;
        if (degree < 1) {
            throw invalid_argument("Degree must be at least 1.");
        }

        // User input for control points
        vector<Point> controlPoints(numControlPoints);
        cout << "Enter the coordinates and weights of control points:" << endl;
        for (int i = 0; i < numControlPoints; ++i) {
            cout << "Control Point " << i + 1 << ": ";
            cin >> controlPoints[i].x >> controlPoints[i].y >> controlPoints[i].z >> controlPoints[i].w;
        }

        // User input for knot vector
        vector<double> knots(numControlPoints + degree + 1);
        cout << "Enter the knot vector:" << endl;
        for (int i = 0; i < numControlPoints + degree + 1; ++i) {
            cout << "Knot " << i + 1 << ": ";
            cin >> knots[i];
        }

        // Generate curve points
        vector<Point> curvePoints;
        for (int i = degree; i <= numControlPoints; ++i) {
            for (double t = knots[i]; t < knots[i + 1]; t += 0.1) {
                curvePoints.push_back(bsplineCurvePoint(t, knots, controlPoints, degree));
            }
        }

        // Write curve data to a file
        writeCurveToFile(curvePoints, "bspline_curve_data.txt");

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
