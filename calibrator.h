#ifndef CALIBRATOR_H
#define CALIBRATOR_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace cv;
class calibrator
{
public:
    calibrator();
    calibrator(vector<string>& fList, const Size& bsize,const double& square);
    void setFileList(vector<string>& fList);
    void setBoardSize(const Size& bsize);
    void setSquareSize(const double &square);
    void setFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled);
    Mat getCameraMatrix();
    Mat getDistCoeffs();
    int addBoardPoints();
    void calibrate();
    Mat rectifyImage(const Mat & image);
private:
    vector<vector<Point3f>> objectPoints;
    vector<vector<Point2f>> imagePoints;
    vector<Mat> rvecs, tvecs;
    vector<string> fileList;
    Mat cameraMatrix;
    Mat distCoeffs;
    Size boardSize;
    Size imageSize;
    int flag;
    double squareSize;
    Mat map1,map2;
    bool calibrated;
};

#endif // CALIBRATOR_H
