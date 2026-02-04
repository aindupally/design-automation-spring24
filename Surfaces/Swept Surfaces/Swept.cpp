#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Define a Point structure to represent a point in 3D space
struct Point {
    double x, y, z;
};

// Function to generate points along a path
vector<Point> generatePath(Point start, Point end, int numPoints) {
    vector<Point> pathPoints;
    double dx = (end.x - start.x) / numPoints;
    double dy = (end.y - start.y) / numPoints;
    double dz = (end.z - start.z) / numPoints;

    for (int i = 0; i <= numPoints; ++i) {
        Point p;
        p.x = start.x + i * dx;
        p.y = start.y + i * dy;
        p.z = start.z + i * dz;
        pathPoints.push_back(p);
    }

    return pathPoints;
}

// Function to sweep a curve along a path and generate the swept surface
vector<Point> sweepCurveAlongPath(vector<Point>& curve, vector<Point>& path) {
    vector<Point> sweptSurface;

    // Sweep the curve along the path
    for (const auto& pathPoint : path) {
        for (const auto& curvePoint : curve) {
            Point p;
            p.x = curvePoint.x + pathPoint.x;
            p.y = curvePoint.y + pathPoint.y;
            p.z = curvePoint.z + pathPoint.z;
            sweptSurface.push_back(p);
        }
    }

    return sweptSurface;
}

// Function to write points to a text file
void writePointsToFile(const vector<Point>& points, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& point : points) {
            outFile << point.x << " " << point.y << " " << point.z << endl;
        }
        outFile.close();
        cout << "Coordinates written to " << filename << " successfully." << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

int main() {
    // Input the curve
    int numCurvePoints;
    cout << "Enter the number of points for the curve: ";
    cin >> numCurvePoints;
    vector<Point> curve(numCurvePoints);
    cout << "Enter the points for the curve (x y z):" << endl;
    for (int i = 0; i < numCurvePoints; ++i) {
        cin >> curve[i].x >> curve[i].y >> curve[i].z;
    }

    // Input the path
    int numPathPoints;
    cout << "Enter the number of points for the path: ";
    cin >> numPathPoints;
    vector<Point> path(numPathPoints);
    cout << "Enter the points for the path (x y z):" << endl;
    for (int i = 0; i < numPathPoints; ++i) {
        cin >> path[i].x >> path[i].y >> path[i].z;
    }

    // Sweep the curve along the path to generate the swept surface
    vector<Point> sweptSurface = sweepCurveAlongPath(curve, path);

    // Write points to a file
    writePointsToFile(sweptSurface, "swept_surface_coordinates.txt");

    return 0;
}