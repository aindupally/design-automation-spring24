#include "main.h"

using namespace std;
int main() {
    int choice;
    cout << "Select an option:" << endl;
    cout << "1. Curve Operations" << endl;
    cout << "2. Surface Operations" << endl;
    cout << "3. Knot Operations" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            // Curve operations
            int curveType;
            cout << "Select a curve type:" << endl;
            cout << "1. C-Spline Curve" << endl;
            cout << "2. Bezier Curve" << endl;
            cout << "3. Rational Bezier Curve" << endl;
            cout << "4. B-Spline Curve" << endl;
            cout << "5. NURBS Curve" << endl;
            cout << "Enter your choice: ";
            cin >> curveType;
            break;
            switch(curveType)
            {
                case 1:
                {
                    cout << "Open the directory and go to the Curves Folder" << endl;
                    cout << "Run the Curves.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    cout << "Run the 'Curve.m' file to visualize the computed surface" << endl;
                    break;
                }
        
                case 2:
                {
                    cout << "Open the directory and go to the Curves Folder" << endl;
                    cout << "Run the Curves.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    cout << "Run the 'Curve.m' file to visualize the computed surface" << endl;
                    break;
                }
                case 3:
                {
                    cout << "Open the directory and go to the Curves Folder" << endl;
                    cout << "Run the Curves.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    cout << "Run the 'Curve.m' file to visualize the computed surface" << endl;
                    break;
                }
            }
        }
        case 2: {
            // Surface operations
            int surfaceType;
            cout << "Select a surface type:" << endl;
            cout << "1. Bezier Surface" << endl;
            cout << "2. Rational Bezier Surface" << endl;
            cout << "3. B-Spline Surface" << endl;
            cout << "4. NURBS Surface" << endl;
            cout << "Enter your choice: ";
            cin >> surfaceType;

            switch(surfaceType)
            {
                case 1:
                {
                    cout << "Open the directory and go to the Surfaces Folder" << endl;
                    cout << "Move into Bezier Folder" << endl;
                    cout << "Run the BezierSurface.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    cout << "Run the 'beziersurfaceplot.m' file to visualize the computed surface" << endl;
                    break;
                }
                case 2:
                {
                    cout << "Open the directory and go to the Surfaces Folder" << endl;
                    cout << "Move into Rational Bspline Folder" << endl;
                    cout << "Run the RBspline.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    cout << "Run the 'beziersurfaceplot.m' file to visualize the computed surface" << endl;
                    break;
                }
                case 3:
                {
                    cout << "Open the directory and go to the Surfaces Folder" << endl;
                    cout << "Move into B-Spline Folder" << endl;
                    cout << "Run the Bspline.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    cout << "Run the 'bsplinesurfaceplot.m' file to visualize the computed surface" << endl;
                    break;
                }
                 case 4:
                {
                    cout << "Open the directory and go to the Surfaces Folder" << endl;
                    cout << "Move into NURBS Folder" << endl;
                    cout << "Run the NURBs.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    cout << "Run the 'nurbssurface.m' file to visualize the computed surface" << endl;
                    break;
                }
            }    
            break;
        }
        case 3: {
            // Knot operations
            int knotOperation;
            cout << "Select a knot operation:" << endl;
            cout << "1. Knot Insertion" << endl;
            cout << "2. Knot Removal" << endl;
            cout << "3. Knot Refinement" << endl;
            cout << "4. Degree Elevation" << endl;
            cout << "5. Degree Reduction" << endl;
            cout << "Enter your choice: ";
            cin >> knotOperation;
            
            switch(knotOperation)
            {
                case 1:
                {
                    cout << "Open the directory and go to the Knot Operation Folder" << endl;
                    cout << "Run the knotinsertion.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    break;
                }
                case 2:
                {
                    cout << "Open the directory and go to the Knot Operation Folder" << endl;
                    cout << "Run the knotinsertion.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    break;
                }
                case 3:
                {
                    cout << "Open the directory and go to the Knot Operation Folder" << endl;
                    cout << "Run the knotinsertion.cpp program" << endl;
                    cout << "Take the input values from the text file" << endl;
                    cout << "Ensure that program says 'Data Written' " << endl;
                    break;
                }
            break;
        }
        default:
        cout << "Invalid choice!" << endl;
        break;
    }
}