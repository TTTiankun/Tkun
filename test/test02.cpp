#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv) {

    Mat img(542, 1123, CV_8UC3, Scalar(255, 255, 255));

    vector<vector<Point>> tdts;
    tdts.push_back(vector<Point>{Point(81, 135), Point(81, 191), Point(295, 191), Point(321, 135)});
    tdts.push_back(vector<Point>{Point(160, 190), Point(229, 190), Point(229, 401), Point(160, 401)});
    tdts.push_back(vector<Point>{Point(329, 242), Point(329, 294), Point(502, 294), Point(502, 242)});
    tdts.push_back(vector<Point>{Point(520, 402), Point(520, 241), Point(585, 241), Point(585, 343)});
    tdts.push_back(vector<Point>{Point(518, 135), Point(544, 192), Point(641, 192), Point(641, 135)}); 
    tdts.push_back(vector<Point>{Point(520, 402), Point(641, 402), Point(641, 343), Point(580, 343)});     
    tdts.push_back(vector<Point>{Point(858, 191), Point(858, 402), Point(925, 402), Point(925, 191)});
    tdts.push_back(vector<Point>{Point(779, 135), Point(779, 191), Point(993, 191), Point(1019, 135)});


    for (auto tdt : tdts) {
        fillConvexPoly(img, tdt, Scalar(0, 0, 0));
    }
    
    Point center = Point(641, 268);
    Size axes = Size(76, 104);
    double angle = 180;
    double startAngle = 90;
    double endAngle = 270;
    Scalar color = Scalar(0, 0, 0);
    int thickness = 57;
    ellipse(img, center, axes, angle, startAngle, endAngle, color, thickness);
    
    string text = "Welcome to T-DT!";
    int length = text.length();
    string border(length + 4, '*');

    cout << border << endl;
    cout << "* " << text << " *" << endl;
    cout << border << endl;
    
    imshow("T-DT", img);
    waitKey(0);

    return 0;
}