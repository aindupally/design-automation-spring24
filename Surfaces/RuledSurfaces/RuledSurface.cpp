#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Define a Point structure to represent a point in 3D space
struct Point {
    double x, y, z;
};

// Function to generate points along a straight line (generator)
vector<Point> generateLine(Point start, Point end, int numPoints) {
    vector<Point> linePoints;
    double dx = (end.x - start.x) / numPoints;
    double dy = (end.y - start.y) / numPoints;
    double dz = (end.z - start.z) / numPoints;

    for (int i = 0; i <= numPoints; ++i) {
        Point p;
        p.x = start.x + i * dx;
        p.y = start.y + i * dy;
        p.z = start.z + i * dz;
        linePoints.push_back(p);
    }

    return linePoints;
}

// Function to generate the ruled surface by connecting points along generators
vector<Point> generateRuledSurface(vector<Point> generators[], int numGenerators, int numPointsPerGenerator) {
    vector<Point> ruledSurface;
    
    // Connect corresponding points of generators to form line segments
    for (int i = 0; i < numPointsPerGenerator; ++i) {
        for (int j = 0; j < numGenerators - 1; ++j) {
            ruledSurface.push_back(generators[j][i]);
            ruledSurface.push_back(generators[j + 1][i]);
        }
    }

    return ruledSurface;
}

int main() {
    int numGenerators, numPointsPerGenerator;
    cout << "Enter the number of generators: ";
    cin >> numGenerators;
    cout << "Enter the number of points along each generator: ";
    cin >> numPointsPerGenerator;

    // Input the start and end points for each generator
    vector<Point> generators[numGenerators];
    for (int i = 0; i < numGenerators; ++i) {
        Point start, end;
        cout << "Enter the start point (x y z) for generator " << i + 1 << ": ";
        cin >> start.x >> start.y >> start.z;
        cout << "Enter the end point (x y z) for generator " << i + 1 << ": ";
        cin >> end.x >> end.y >> end.z;
        generators[i] = generateLine(start, end, numPointsPerGenerator);
    }

    // Generate the ruled surface
    vector<Point> ruledSurface = generateRuledSurface(generators, numGenerators, numPointsPerGenerator);

    // Write points to files for x, y, and z coordinates
    ofstream xFile("x_coordinates.txt");
    ofstream yFile("y_coordinates.txt");
    ofstream zFile("z_coordinates.txt");
    if (xFile.is_open() && yFile.is_open() && zFile.is_open()) {
        for (const auto& point : ruledSurface) {
            xFile << point.x << " ";
            yFile << point.y << " ";
            zFile << point.z << " ";
        }
        xFile.close();
        yFile.close();
        zFile.close();
        cout << "Coordinates written to x_coordinates.txt, y_coordinates.txt, and z_coordinates.txt successfully." << endl;
    } else {
        cerr << "Unable to open one or more output files." << endl;
    }

    return 0;
}
