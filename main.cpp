#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TrailPoint {
    float x;
    float y;
    float temperature;
    string timestamp;
    string color;
};

string getColor(float temp) {
    if (temp < 50) return "blue";
    else if (temp < 100) return "yellow";
    else if (temp < 200) return "orange";
    else return "red";
}

void addTrailPoint(vector<TrailPoint>& trail, float x, float y, float temp, string timestamp) {
    TrailPoint point;
    point.x = x;
    point.y = y;
    point.temperature = temp;
    point.timestamp = timestamp;
    point.color = getColor(temp);
    trail.push_back(point);
}

void printTrail(vector<TrailPoint>& trail) {
    for (auto& point : trail) {
        cout << "Position: (" << point.x << ", " << point.y << ")" << endl;
        cout << "Temperature: " << point.temperature << "C" << endl;
        cout << "Recorded: " << point.timestamp << endl;
        cout << "Trail Color: " << point.color << endl;
        cout << "---" << endl;
    }
}

int main() {
    vector<TrailPoint> trail;

    addTrailPoint(trail, 1.0, 2.0, 45.0, "1 minute ago");
    addTrailPoint(trail, 2.0, 3.0, 95.0, "2 minutes ago");
    addTrailPoint(trail, 3.0, 4.0, 150.0, "3 minutes ago");
    addTrailPoint(trail, 4.0, 5.0, 250.0, "4 minutes ago");

    printTrail(trail);

    return 0;
}