//ME 8720
//Team 2= Emily petty, Abhisheck Indupally, Stephan Terry
//Curves for the final project
// Proffesor: Dr. Turner
//run with matlab code curvesplotting.mlx


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

//define the data structure to represent a point
struct Point {
    double x, y, w; // w is the weight for rational curves
};

//define a class to handle curve generation
class CurveGenerator {
private:
    vector<Point> controlPoints; //a vector to store the control points
    int numControlPoints; //number of control points entered by the user

    //calculate binomial coefficient (n choose k)
    int binomialCoefficient(int n, int k) {
        if (k == 0 || k == n)
            return 1;
        return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
    }

    //ccalculate Bézier curve point at parameter t
    Point calculateBezierPoint(double t) {
        int n = controlPoints.size() - 1;
        double x = 0, y = 0, w = 0;

        for (size_t i = 0; i <= n; ++i) {
            double b = binomialCoefficient(n, i) * pow(t, i) * pow(1 - t, n - i);
            x += controlPoints[i].x * controlPoints[i].w * b;
            y += controlPoints[i].y * controlPoints[i].w * b;
            w += controlPoints[i].w * b;
        }

        return { x / w, y / w, 1.0 }; // normalize by weight
    }

    // calculate B-spline basis function
    double bsplineBasis(int i, int k, double t, const vector<double>& knots) {
        if (k == 1) {
            if (knots[i] <= t && t < knots[i + 1])
                return 1.0;
            return 0.0;
        }

        double denom1 = knots[i + k - 1] - knots[i];
        double denom2 = knots[i + k] - knots[i + 1];
        double basis1 = 0.0, basis2 = 0.0;

        if (denom1 != 0)
            basis1 = (t - knots[i]) / denom1 * bsplineBasis(i, k - 1, t, knots);
        if (denom2 != 0)
            basis2 = (knots[i + k] - t) / denom2 * bsplineBasis(i + 1, k - 1, t, knots);

        return basis1 + basis2;
    }

    //calculate B-spline curve point at parameter t
    Point calculateBSplinePoint(double t) {
        int n = controlPoints.size() - 1;
        int k = 3; // degree of the B-spline curve
        int m = n + k + 1; //total number of knots
        vector<double> knots(m);

        //generates uniform open knots
        for (int i = 0; i < m; ++i) {
            if (i < k)
                knots[i] = 0.0;
            else if (i <= n)
                knots[i] = static_cast<double>(i - k + 1) / (n - k + 2);
            else
                knots[i] = 1.0;
        }

        double x = 0, y = 0, w = 0;

        for (size_t i = 0; i <= n; ++i) {
            double basis = bsplineBasis(i, k, t, knots);
            x += controlPoints[i].x * controlPoints[i].w * basis;
            y += controlPoints[i].y * controlPoints[i].w * basis;
            w += controlPoints[i].w * basis;
        }

        return { x / w, y / w, 1.0 }; //normalize by the weight
    }

    //calculate cubic spline curve point at parameter t
    Point calculateCubicSplinePoint(double t) {
        size_t n = controlPoints.size() - 1;
        size_t segment = static_cast<size_t>(t * n); //determine which segment the t falls into
        double segmentT = t * n - segment; //normalizes t to the segment

        //linear interpolation between control points
        double x1 = controlPoints[segment].x;
        double y1 = controlPoints[segment].y;
        double x2 = controlPoints[segment + 1].x;
        double y2 = controlPoints[segment + 1].y;

        double x = x1 + segmentT * (x2 - x1);
        double y = y1 + segmentT * (y2 - y1);

        return { x, y, 1.0 }; //for cubic splines, weight is always 1
    }

    //calculate NURBS curve point at parameter t
    Point calculateNURBSPoint(double t) {
        return { 0, 0, 0 }; // this one wasnt working well so this is what i got in here
    }

    // Calculate parabolic blend curve point at parameter t
    Point calculateParabolicBlendPoint(double t) {
        return { 0, 0, 0 }; // this one wasnt working well so this is what i got in here
    }

public:
    // method to set the number of control points
    void setNumControlPoints(int num) {
        numControlPoints = num;
    }

    // method to add a control point
    void addControlPoint(double x, double y, double w = 1.0) {
        controlPoints.push_back({ x, y, w }); // Add a new control point to the vector
    }

    // method to generate and write Bézier curves to a file
    void generateBezierCurves(const string& filename) {
        ofstream file(filename); //opens a file for writing
        if (!file.is_open()) { // checks if the file is successfully opened
            cerr << "Error: Unable to open file '" << filename << "'." << endl; //displays an error message if file failss
            return; // Return from the method
        }

        // generate and write Bézier curves to the file
        for (double t = 0; t <= 1.0; t += 0.01) {
            Point bezierPoint = calculateBezierPoint(t);
            file << bezierPoint.x << " " << bezierPoint.y << endl;
        }

        file.close(); //close the file.
        cout << "Bézier curves data saved to '" << filename << "'." << endl; //prints a message indicating successful save
    }

    //method to generate and write B-spline curves to a file
    void generateBSplineCurves(const string& filename) {
        ofstream file(filename); //open a file for writing
        if (!file.is_open()) { //checks if the file is successfully opened
            cerr << "Error: Unable to open file '" << filename << "'." << endl; //displays an error message if file fails
            return; //returns from the method
        }

        //generates and writes B-spline curves to the file
        for (double t = 0; t <= 1.0; t += 0.01) {
            Point bSplinePoint = calculateBSplinePoint(t);
            file << bSplinePoint.x << " " << bSplinePoint.y << endl;
        }

        file.close(); ///Closes the file
        cout << "B-spline curves data saved to '" << filename << "'." << endl; //print message indicating successful save
    }

    //method to generate and write cubic spline curves to a file
    void generateCubicSplineCurves(const string& filename) {
        ofstream file(filename); //opens a file for writing
        if (!file.is_open()) { //checks if the file is successfully opened
            cerr << "Error: Unable to open file '" << filename << "'." << endl; //display an error message if file fails
            return; //return from the method
        }

        //generate and write cubic spline curves to the file
        for (double t = 0; t <= 1.0; t += 0.01) {
            Point cubicSplinePoint = calculateCubicSplinePoint(t);
            file << cubicSplinePoint.x << " " << cubicSplinePoint.y << endl;
        }

        file.close(); //close the file
        cout << "Cubic spline curves data saved to '" << filename << "'." << endl; //prints message to indicate successful save
    }

    // Method to generate and write NURBS curves to a file
    void generateNURBSCurves(const string& filename) {
    }

    // Method to generate and write rational B-spline curves to a file
    void generateRationalBSplineCurves(const string& filename) {
    }

    // Method to generate and write parabolic blend curves to a file
    void generateParabolicBlendCurves(const string& filename) {
    }
};

int main() {
    //create a CurveGenerator object
    CurveGenerator generator;

    //prompt the user to input the number of control points
    int numControlPoints;
    cout << "Enter the number of control points: ";
    cin >> numControlPoints;
    generator.setNumControlPoints(numControlPoints);

    //prompt the user to input control points
    cout << "Enter control points (x y w for rational curves):" << endl;
    for (int i = 0; i < numControlPoints; ++i) {
        double x, y, w;
        cout << "Control Point " << i + 1 << ": ";
        cin >> x >> y >> w;
        generator.addControlPoint(x, y, w);
    }

    //generate and write curves to files
    generator.generateBezierCurves("bezier_curves.txt");
    generator.generateBSplineCurves("b_spline_curves.txt");
    generator.generateCubicSplineCurves("cubic_spline_curves.txt");
    generator.generateNURBSCurves("nurbs_curves.txt");
    generator.generateRationalBSplineCurves("rational_bspline_curves.txt");
    generator.generateParabolicBlendCurves("parabolic_blend_curves.txt");

    //provide a message to use generated text files in a MATLAB script for plotting
    cout << "Please use the generated text files in a MATLAB script for plotting.\n";

    return 0;
}