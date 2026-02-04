#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

// Structure to represent a 3D point
struct Point {
    double x, y, z;
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
    Point result = { 0, 0, 0 };
    int n = controlPoints.size() - 1;
    for (int i = 0; i <= n; ++i) {
        double blend = basis(i, degree + 1, t, knots);
        result.x += blend * controlPoints[i].x;
        result.y += blend * controlPoints[i].y;
        result.z += blend * controlPoints[i].z;
    }
    return result;
}

// Function to generate B-spline surface points
vector<vector<Point>> generateBSplineSurface(const vector<vector<Point>>& controlPoints, const vector<double>& knotsU, const vector<double>& knotsV, int degreeU, int degreeV, int resolutionU, int resolutionV) {
    vector<vector<Point>> surfacePoints(resolutionU + 1, vector<Point>(resolutionV + 1));
    for (int u = 0; u <= resolutionU; ++u) {
        double t = knotsU[degreeU] + (u * (knotsU[controlPoints.size()] - knotsU[degreeU])) / resolutionU;
        for (int v = 0; v <= resolutionV; ++v) {
            double s = knotsV[degreeV] + (v * (knotsV[controlPoints[0].size()] - knotsV[degreeV])) / resolutionV;
            surfacePoints[u][v] = bsplineCurvePoint(t, knotsU, controlPoints[v], degreeU);
        }
    }
    return surfacePoints;
}

// Function to write surface data to a file
void writeSurfaceToFile(const vector<vector<Point>>& surfacePoints, const string& filename) {
    ofstream outfileBsplineSurface(filename);
    if (!outfileBsplineSurface) {
        cerr << "Error: Unable to open the file!" << endl;
        return;
    }

    for (const auto& row : surfacePoints) {
        for (const auto& point : row) {
            outfileBsplineSurface << point.x << " " << point.y << " " << point.z << endl;
        }
    }

    outfileBsplineSurface.close();
    cout << "Surface data written to " << filename << endl;
}

int main() {
    try {
        // User input for number of control points
        int numControlPoints;
        cout << "Enter the number of control points: ";
        cin >> numControlPoints;
        if (numControlPoints < 4) {
            throw invalid_argument("Number of control points must be at least 4.");
        }

        // User input for resolution
        int resolutionU, resolutionV;
        cout << "Enter the resolution in U direction: ";
        cin >> resolutionU;
        if (resolutionU < 1) {
            throw invalid_argument("Resolution in U direction must be at least 1.");
        }
        cout << "Enter the resolution in V direction: ";
        cin >> resolutionV;
        if (resolutionV < 1) {
            throw invalid_argument("Resolution in V direction must be at least 1.");
        }

        // User input for control points
        vector<Point> controlPoints(numControlPoints);
        cout << "Enter the coordinates of control points:" << endl;
        for (int i = 0; i < numControlPoints; ++i) {
            cout << "Control Point " << i + 1 << ": ";
            cin >> controlPoints[i].x >> controlPoints[i].y >> controlPoints[i].z;
        }

        // User input for degrees
        int degreeU, degreeV;
        cout << "Enter the degree in U direction: ";
        cin >> degreeU;
        if (degreeU < 1) {
            throw invalid_argument("Degree in U direction must be at least 1.");
        }
        cout << "Enter the degree in V direction: ";
        cin >> degreeV;
        if (degreeV < 1) {
            throw invalid_argument("Degree in V direction must be at least 1.");
        }

        // User input for knot vectors
        vector<double> knotsU(numControlPoints + degreeU + 1);
        cout << "Enter the knot vector for U direction:" << endl;
        for (int i = 0; i < numControlPoints + degreeU + 1; ++i) {
            cout << "Knot " << i + 1 << ": ";
            cin >> knotsU[i];
        }

        vector<double> knotsV(numControlPoints + degreeV + 1);
        cout << "Enter the knot vector for V direction:" << endl;
        for (int i = 0; i < numControlPoints + degreeV + 1; ++i) {
            cout << "Knot " << i + 1 << ": ";
            cin >> knotsV[i];
        }

        // Generating B-spline surface
        vector<vector<Point>> surfacePoints = generateBSplineSurface({controlPoints}, knotsU, knotsV, degreeU, degreeV, resolutionU, resolutionV);

        // Writing surface data to a file
        writeSurfaceToFile(surfacePoints, "bspline_surface_data.txt");

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
