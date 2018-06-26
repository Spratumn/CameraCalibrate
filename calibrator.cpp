#include "calibrator.h"
calibrator::calibrator()
{
    calibrated=false;
    flag = 0;
}

calibrator::calibrator(vector<string> &fList,const Size &bSize,const double &square)
{
    setFileList(fList);
    setBoardSize(bSize);
    squareSize=square;
    calibrated=false;
    flag = 0;
}

void calibrator::setFileList(vector<string> &fList)
{
    fileList.assign(fList.begin(),fList.end());
    Mat temimage=imread(fileList[0],0);
    imageSize.height= temimage.rows;
    imageSize.width=temimage.cols;
}

void calibrator::setBoardSize(const Size& bsize)
{
    boardSize.height=bsize.height;
    boardSize.width=bsize.width;
}

void calibrator::setSquareSize(const double &square)
{
    squareSize=square;
}

void calibrator::setFlag(bool radial8CoeffEnabled, bool tangentialParamEnabled)
{
        flag = 0;
        if (!tangentialParamEnabled) flag += CV_CALIB_ZERO_TANGENT_DIST;
        if (radial8CoeffEnabled) flag += CV_CALIB_RATIONAL_MODEL;
}

Mat calibrator::getCameraMatrix()
{
    return cameraMatrix;
}

Mat calibrator::getDistCoeffs()
{
    return distCoeffs;
}

int calibrator::addBoardPoints()
{
    vector<Point2f> imageCorners;
    vector<Point3f> objectCorners;

    for (int i=0; i<boardSize.height; i++) {
        for (int j=0; j<boardSize.width; j++) {
            objectCorners.push_back(cv::Point3f(i*squareSize, j*squareSize, 0.0f));
        }
    }
    Mat boardimage; // to contain chessboard image
    int successes = 0;
    // for all viewpoints
    for (unsigned int i=0; i<fileList.size(); i++)
    {
        boardimage = cv::imread(fileList[i],0);
        // Get the chessboard corners
        bool found = findChessboardCorners(
                        boardimage,
                        boardSize,
                        imageCorners);
        // Get subpixel accuracy on the corners
        cornerSubPix(boardimage,
                     imageCorners,
                     Size(5,5),
                     Size(-1,-1),
                     TermCriteria(TermCriteria::MAX_ITER +TermCriteria::EPS,
                     20,
                     0.01));
        if (imageCorners.size() ==(unsigned int) boardSize.area())
        {
            // 2D image points from one view
            imagePoints.push_back(imageCorners);
            // corresponding 3D scene points
            objectPoints.push_back(objectCorners);
            successes++;
          }

        drawChessboardCorners(boardimage, boardSize, imageCorners, found);
        imshow("Corners on Chessboard", boardimage);
        waitKey(100);
    }
    return successes;
}

void calibrator::calibrate()
{
    int usepoint= addBoardPoints();
    cout<<"use "<<usepoint<<" pictures"<<endl;
    calibrateCamera(objectPoints, // the 3D points
                    imagePoints,  // the image points
                    imageSize,    // image size
                    cameraMatrix, // output camera matrix
                    distCoeffs,   // output distortion matrix
                    rvecs, tvecs, // Rs, Ts
                    flag);        // set options
    calibrated=true;

}

Mat calibrator::rectifyImage(const Mat &image)
{
    cv::Mat undistorted;
    if (calibrated)
    {
        initUndistortRectifyMap(
                    cameraMatrix,  // computed camera matrix
                    distCoeffs,    // computed distortion matrix
                    Mat(),     // optional rectification (none)
                    Mat(),     // camera matrix to generate undistorted
                    image.size(),  // size of undistorted
                    CV_32FC1,      // type of output map
                    map1, map2);   // the x and y mapping functions
        remap(image,
              undistorted,
              map1, map2,
              INTER_LINEAR);
    }


    return undistorted;
}



