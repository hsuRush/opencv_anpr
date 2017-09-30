//
//  main.cpp
//  0619opencv
//
//  Created by Chensteven on 2017/6/19.
//  Copyright (c) 2017年 Rush. All rights reserved.
//


#include "MatContainer.h"
#include <opencv2/ml/ml.hpp>
#include <vector>


#define defTHRESHOLD_BIN 145
#define defTHRESHOLD_CUT 17000/79
#define defTHRESHOLD_HOR 57000/331        //66000
#define defTHRESHOLD_VER 26000/109     //23000/109
#define defTHRESHOLD_EDG 10
#define defTHRESHOLD_COMPAREACCEPTABLE 0.7
const int MIN_CONTOUR_AREA = 100;
const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;


//! [namespace]

using namespace cv;
using namespace cv::ml;
using namespace std;
//class
class ContourWithData {
public:
    // member variables ///////////////////////////////////////////////////////////////////////////
    std::vector<cv::Point> ptContour;           // contour
    cv::Rect boundingRect;                      // bounding rect for contour
    float fltArea;                              // area of contour
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    bool checkIfContourIsValid() {                              // obviously in a production grade program
        if (fltArea < MIN_CONTOUR_AREA) return false;           // we would have a much more robust function for
        return true;                                            // identifying if a contour is valid !!
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    static bool sortByBoundingRectXPosition(const ContourWithData& cwdLeft, const ContourWithData& cwdRight) {      // this function allows us to sort
        return(cwdLeft.boundingRect.x < cwdRight.boundingRect.x);                                                   // the contours from left to right
    }
    
};
//class

int main( int argc, char** argv )

{
    
    //! [load]
    string traindata_address("/Users/Rush/Project/opencv/c++/Project_test/resource_pic/Font/black font/");
    string imageNamelena("/Users/Rush/Project/opencv/c++/Project_test/resource_pic/lena.png"); // lena <3
    string imageNamenumber("/Users/Rush/Project/opencv/c++/Project_test/resource_pic/number.jpeg");
    string imageNamenumber2("/Users/Rush/Project/opencv/c++/Project_test/resource_pic/number2.png");
    string imageNamenumber3("/Users/Rush/Project/opencv/c++/Project_test/resource_pic/number3.png");
    /*
    ////using trainingdata
    Mat traindata [36];
    Mat matTrainingImagesAsFlattenedFloatsData;
    Mat matClassificationIntsData;
    for ( int i = 0; i < 36; i++ ) {
        stringstream count;
        if(i >= 0 &&  i < 10)
            count << i;
        else if(i >= 10 && i < 36)
            count << char(i+55);
        
        traindata[i] = imread(traindata_address + count.str()+ ".png",CV_LOAD_IMAGE_COLOR);
        //cout << i <<" "<< traindata[i].rows <<", "<<traindata[i].cols<<endl;
       
       
        cv::resize(traindata[i], traindata[i], cv::Size(RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT));//need to contour tbd
        traindata[i].convertTo(traindata[i], CV_32FC1);
        cv::Mat traindatafloat = traindata[i].reshape(1, 1);
         matTrainingImagesAsFlattenedFloatsData.push_back(traindatafloat);
        if(i > -1 &&  i < 10)
            matClassificationIntsData.push_back(i+48);
        else if(i > 9 && i < 36)
            matClassificationIntsData.push_back(i+55);
    }
    */
    /*
     ////File save
    cv::FileStorage fsClassifications("/Users/Rush/Project/0619opencv/0619opencv/classifications.xml", cv::FileStorage::WRITE);
    fsClassifications << "classifications" << matClassificationIntsData;        // write classifications into classifications section of classifications file
    fsClassifications.release();

    cv::FileStorage fsTrainingImages("/Users/Rush/Project/0619opencv/0619opencv/images.xml", cv::FileStorage::WRITE);
    fsTrainingImages << "images" << matTrainingImagesAsFlattenedFloatsData;         // write training images into images section of images file
    fsTrainingImages.release();
    //////File save 
     */
        //! [load]
    //read storage
    cv::Mat matClassificationIntsData;
    cv::FileStorage fsClassifications("classifications.xml", cv::FileStorage::READ);        // open the classifications file
    
    if (fsClassifications.isOpened() == false) {                                                    // if the file was not opened successfully
        std::cout << "error, unable to open training classifications file, exiting program\n\n";    // show error message
        return(0);                                                                                  // and exit program
    }
    
    fsClassifications["classifications"] >> matClassificationIntsData;      // read classifications section into Mat classifications variable
    fsClassifications.release();                                        // close the classifications file
    
    // read in training images ////////////////////////////////////////////////////////////
    
    cv::Mat matTrainingImagesAsFlattenedFloatsData;         // we will read multiple images into this single image variable as though it is a vector
    
    cv::FileStorage fsTrainingImages("images.xml", cv::FileStorage::READ);          // open the training images file
    
    if (fsTrainingImages.isOpened() == false) {                                                 // if the file was not opened successfully
        std::cout << "error, unable to open training images file, exiting program\n\n";         // show error message
        return(0);                                                                              // and exit program
    }
    
    fsTrainingImages["images"] >> matTrainingImagesAsFlattenedFloatsData;           // read images section into Mat training images variable
    fsTrainingImages.release();
    
    // read in training classifications ///////////////////////////////////////////////////
    
    
    //read storage
    
    ///!KNN setting
    cv::Ptr<cv::ml::KNearest>  kNearest (cv::ml::KNearest::create());            // instantiate the KNN object
    //KKNN setting
    // finally we get to the call to train, note that both parameters have to be of type Mat (a single Mat)
    // even though in reality they are multiple images / numbers
    //  KNN training
    kNearest->train(matTrainingImagesAsFlattenedFloatsData, cv::ml::ROW_SAMPLE, matClassificationIntsData);
    ///!KNN training
    
    // training
    //Ptr<TrainData> td = TrainData::create(SVM_TrainingData,ROW_SAMPLE,SVM_Classes);
    //svm->trainAuto(td);
    
    // training
    
    //! [MatContainer]
    
    MatContainer image = MatContainer(imageNamenumber,CV_LOAD_IMAGE_COLOR) ;
    
    image.Set_THRESHOLD_BINARIZATION(defTHRESHOLD_BIN);
    image.Set_THRESHOLD_HORIZONSHAPE(defTHRESHOLD_HOR);
    image.Set_THRESHOLD_VERITICALSHAPE(defTHRESHOLD_VER);
    image.Set_THRESHOLD_EDGE(defTHRESHOLD_EDG);
    image.Set_THRESHOLD_CAMPAREACCEPTABLE(defTHRESHOLD_COMPAREACCEPTABLE);
    //! [MatContainer]
    image.cvToGray();
    image.cvToGauss();
    image.cvToBinariztion();
    image.cvShape();
    //debug
    image.imshow("image");                // Show our image inside it.
    //debug
    
    //cut letter
    image.Set_THRESHOLD_CUT(defTHRESHOLD_CUT);
    image.cvCutToLetter();
    //image.cvCompare(traindata,defTHRESHOLD_COMPAREACCEPTABLE);
    //cut letter
    std::string strFinalString;         // declare final string, this will have the final number sequence by the end of the program
    std::vector<Mat> image_vector = image.Getvector();
    
    for(int ok = 0 ;ok < image_vector.size();ok++) {
        stringstream s;
        s << ok;
        cv::imshow(s.str(),image_vector.at(ok));
    }
    
    for (int i = 0; i < image_vector.size(); i++) {            // for each contour
        
        cv::Mat image_vector_Resized;
        cv::resize(image_vector[i], image_vector_Resized, cv::Size(RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT));     // resize image, this will be more consistent for recognition and storage
        
        cv::Mat image_vector_Float;
        image_vector_Resized.convertTo(image_vector_Float, CV_32FC1);             // convert Mat to float, necessary for call to find_nearest
        
        cv::Mat image_vector_FlattenedFloat = image_vector_Float.reshape(1, 1);
        
        cv::Mat matCurrentChar(0, 0, CV_32FC1);
        
        kNearest->findNearest(image_vector_FlattenedFloat, 1, matCurrentChar);     // finally we can call find_nearest !!!
        
        float fltCurrentChar = (float)matCurrentChar.at<float>(0, 0);
        
        strFinalString = strFinalString + char(int(fltCurrentChar));        // append current char to full string
    }
    
    std::cout << "\n\n" << "numbers read = " << strFinalString << "\n\n";
    //! [imshow]
    
    //! [imshow]
    
    
    
    //! [wait]
    
    waitKey(0); // Wait for a keystroke in the window
    
    //! [wait]
    
    return 0;
    
}