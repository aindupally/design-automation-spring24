#include "nurbs.h"

int main() {
    vector<ControlPoint> controlPoints;
    size_t numberOfPoints;
    cout << "Enter the number of control points: ";
    cin >> numberOfPoints;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int resolution;
    cout << "Enter the resolution for surface plotting: ";
    cin >> resolution;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < numberOfPoints; ++i) {
        double x, y, z, weight;
        cout << "Enter x, y, z, and weight for control point " << i + 1 << ": ";
        cin >> x >> y >> z >> weight;
        controlPoints.push_back({x, y, z, weight});
        /*controlPoints.push_back(x);
        controlPoints.push_back(y);
        controlPoints.push_back(z);
        controlPoints.push_back(weight);*/

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<double> uKnots, vKnots;
    int uDegree, vDegree;

    cout << "Enter the degree for the u-direction: ";
    cin >> uDegree;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the degree for the v-direction: ";
    cin >> vDegree;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int numUKnots = uDegree + numberOfPoints + 1;
    int numVKnots = vDegree + numberOfPoints + 1;

    cout << "Enter " << numUKnots << " knot values for the u-direction: ";
    for (int i = 0; i < numUKnots; ++i) {
        double knot;
        cin >> knot;
        uKnots.push_back(knot);
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter " << numVKnots << " knot values for the v-direction: ";
    for (int i = 0; i < numVKnots; ++i) {
        double knot;
        cin >> knot;
        vKnots.push_back(knot);
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream outFile("NURBS_Surface_Data.txt");
    if (!outFile) {
        cerr << "Error: Unable to open file for writing." << endl;
        return 1;
    }

    for (int i = 0; i <= resolution; ++i) {
        for (int j = 0; j <= resolution; ++j) {
            double u = static_cast<double>(i) / resolution;
            double v = static_cast<double>(j) / resolution;
            vector<double> surfacePoint = interpolateSurface(u, v, controlPoints, uKnots, vKnots, uDegree, vDegree);
            outFile << surfacePoint[0] << " " << surfacePoint[1] << " " << surfacePoint[2] << endl;
        }
    }

    outFile.close();
    cout << "Data written" << endl;
}
