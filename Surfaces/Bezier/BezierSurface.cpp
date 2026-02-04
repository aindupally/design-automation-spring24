#include "BezierSurface.h"

int main() {
    int numRows, numCols;
    std::cout << "Enter the number of rows for control points: ";
    std::cin >> numRows;
    std::cout << "Enter the number of columns for control points: ";
    std::cin >> numCols;

    // Input control points
    std::vector<std::vector<std::tuple<double, double, double>>> controlPoints(numRows, std::vector<std::tuple<double, double, double>>(numCols));
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            double x, y, z;
            std::cout << "Enter x, y, and z coordinates for control point (" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> x >> y >> z;
            controlPoints[i][j] = std::make_tuple(x, y, z);
        }
    }

    // Input number of points to interpolate on the surface
    int numInterpolatedPointsU, numInterpolatedPointsV;
    std::cout << "Enter the number of points to interpolate along U direction: ";
    std::cin >> numInterpolatedPointsU;
    std::cout << "Enter the number of points to interpolate along V direction: ";
    std::cin >> numInterpolatedPointsV;

    // Calculate points on the Bezier surface
    std::ofstream outFile("bezier_surface_data.txt");
    if (outFile.is_open()) {
        for (int i = 0; i <= numInterpolatedPointsU; ++i) {
            for (int j = 0; j <= numInterpolatedPointsV; ++j) {
                double u = static_cast<double>(i) / numInterpolatedPointsU;
                double v = static_cast<double>(j) / numInterpolatedPointsV;
                std::tuple<double, double, double> point = bezierSurfacePoint(controlPoints, u, v);
                outFile << std::get<0>(point) << " " << std::get<1>(point) << " " << std::get<2>(point) << std::endl;
            }
        }
        outFile.close();
        std::cout << "Data saved to bezier_surface_data.txt" << std::endl;
    } else {
        std::cerr << "Error: Unable to open file for writing!" << std::endl;
    }

    return 0;
}

