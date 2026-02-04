#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <tuple>
#include <stdexcept>

using namespace std;

/* Rational Bezier Surface 
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
        Point bsplineCurvePoint(double t, const vector<double>& knots, const vector<Point>& controlPointsBspline, int degree);
        // Function to write curve data to a file
        void writeCurveToFile(const vector<Point>& curvePoints, const string& filename);

        // Bspline Surface 
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
        Point bsplineCurvePoint(double t, const vector<double>& knots, const vector<Point>& controlPointsBspline, int degree) {
            Point result = { 0, 0, 0 };
            int n = controlPointsBspline.size() - 1;
            for (int i = 0; i <= n; ++i) {
                double blend = basis(i, degree + 1, t, knots);
                result.x += blend * controlPointsBspline[i].x;
                result.y += blend * controlPointsBspline[i].y;
                result.z += blend * controlPointsBspline[i].z;
            }
            return result;
        }
        // Function to generate B-spline surface points
        vector<vector<Point>> generateBSplineSurface(const vector<vector<Point>>& controlPointsBspline, const vector<double>& knotsU, const vector<double>& knotsV, int degreeU, int degreeV, int resolutionU, int resolutionV) {
            vector<vector<Point>> surfacePoints(resolutionU + 1, vector<Point>(resolutionV + 1));
            for (int u = 0; u <= resolutionU; ++u) {
                double t = knotsU[degreeU] + (u * (knotsU[controlPointsBspline.size()] - knotsU[degreeU])) / resolutionU;
                for (int v = 0; v <= resolutionV; ++v) {
                    double s = knotsV[degreeV] + (v * (knotsV[controlPointsBspline[0].size()] - knotsV[degreeV])) / resolutionV;
                    surfacePoints[u][v] = bsplineCurvePoint(t, knotsU, controlPointsBspline[v], degreeU);
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
*/;
#endif