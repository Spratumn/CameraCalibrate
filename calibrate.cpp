#include <calibrator.cpp>
int main()
{
    namedWindow("Image");

    Mat image;
    vector<string> filelist;
    for (int i=1; i<=4; i++)
    {
        stringstream str;
        str << "../chessboard/left" << std::setw(2) << std::setfill('0') << i << ".jpg";
        cout << str.str() << endl;
        filelist.push_back(str.str());
        image= imread(str.str());
        imshow("Image",image);
        waitKey(100);
    }
    Size size(9,6);
    calibrator calib(filelist,size,10);
    calib.calibrate();
    cout<<"cameraMatrix:"<<calib.getDistCoeffs()<<endl;
    Mat image1=imread("../chessboard/left02.jpg",0);
    Mat image2= calib.rectifyImage(image1);
    imshow("orginal image",image1);
    imshow("rectified image",image2);
    waitKey(0);

}
