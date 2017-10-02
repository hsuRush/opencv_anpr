//
//  MatContainer.h
//  0619opencv
//
//  Created by Chensteven on 2017/9/25.
//  Copyright (c) 2017年 Rush. All rights reserved.
//

#ifndef _619opencv_MatContainer_h
#define _619opencv_MatContainer_h
#endif


#include <string>
#include <vector>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

class MatContainer {
    
public:
    //constructors
    MatContainer(Mat);
    MatContainer(string,int);
    //load vector
    std::vector< Mat > Getvector();
    //save vector
    void SaveToMat_vector(string);
    //copy
    Mat clone();
    //cv funcctions
    void cvsearchROI();
    void resize();
    void cvToGray();
    void cvToGauss();
    void cvToBinariztion();
    void cvShape();
    Mat  cvProjection();//投影
    void cvCutToLetter();
    void cvEdgelize();

    void cvToZhangSUenThinning();
   
    //Settings
    void Set_THRESHOLD_BINARIZATION(int);
    void Set_THRESHOLD_CUT(int);
    void Set_THRESHOLD_HORIZONSHAPE(int);
    void Set_THRESHOLD_VERITICALSHAPE(int);
    void Set_THRESHOLD_EDGE(int);
    void Set_THRESHOLD_CAMPAREACCEPTABLE(float);
    // show
    void imshow(string);
    
private:
    /////data structure
    Mat _Mat;
    std::vector< Mat > _Vector_Mat_Letters;
    /////Threshold
    int THRESHOLD_BINIZARATION;//二值化
    int THRESHOLD_HORZIONSHAPE;
    int THRESHOLD_CUT;
    int THRESHOLD_VERITICALSHAPE;
    int THRESHOLD_EDGE;
    float THRESHOLD_CAMPAREACCEPTABLE;
};