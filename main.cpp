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

//BINARIZATION
#define defTHRESHOLD_BIN 145
//CUT
#define defTHRESHOLD_CUT 17000/79
#define defTHRESHOLD_LETTERLENGTH 8/59
//HORIZON
#define defTHRESHOLD_HOR 57000/331        //66000
//VERITICAL
#define defTHRESHOLD_VER 26000/109     //23000/109
//EDGE
#define defTHRESHOLD_EDG 10

const int RESIZED_IMAGE_WIDTH = 44;    //44
const int RESIZED_IMAGE_HEIGHT = 79;   //79


//! [namespace]

using namespace cv;
using namespace cv::ml;
using namespace std;
//class

//class
//func
void fsWrite(Mat matClassificationIntsData, Mat matTrainingImagesAsFlattenedFloatsData);

//func

int main( int argc, char** argv )

{
    
    //! [load]
    string traindata_address("/Users/Rush/Project/0619opencv/0619opencv/resources_pic/Font/black font/");
    string inputREGULARimage_address("/Users/Rush/Project/0619opencv/0619opencv/resources_pic/regular picture/regular2.png");
    string inputOCRimage_address("/Users/Rush/Project/0619opencv/0619opencv/resources_pic/testing/number6.png");
    string imageNamenumber2("/Users/Rush/Project/0619opencv/0619opencv/resources_pic/testing/number2.png");
    string imageNamenumber3("/Users/Rush/Project/0619opencv/0619opencv/resources_pic/testing/number3.png");
    
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
    
        traindata[i] = imread(traindata_address + count.str()+ ".png",CV_8UC3);
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
    
   
     ////File save
    cv::FileStorage fsClassifications("classifications.xml", cv::FileStorage::WRITE);
    fsClassifications << "classifications" << matClassificationIntsData;        // write classifications into classifications section of classifications file
    fsClassifications.release();

    cv::FileStorage fsTrainingImages("images.xml", cv::FileStorage::WRITE);
    fsTrainingImages << "images" << matTrainingImagesAsFlattenedFloatsData;         // write training images into images section of images file
    fsTrainingImages.release();
    //////File save 
    */
        //! [load]
    
    //read storage
    cv::Mat matClassificationIntsData;
    cv::Mat matTrainingImagesAsFlattenedFloatsData;
    cv::FileStorage fsClassificationsRead("/Users/Rush/Project/0619opencv/0619opencv/classifications.xml", cv::FileStorage::READ);        // open the classifications file
    
    if (fsClassificationsRead.isOpened() == false) {                                                    // if the file was not opened successfully
        std::cout << "error, unable to open training classifications file, exiting program\n\n";    // show error message
        return(0);                                                                                  // and exit program
    }
    
    fsClassificationsRead["classifications"] >> matClassificationIntsData;      // read classifications section into Mat classifications variable
    fsClassificationsRead.release();                                        // close the classifications file
   
    // read in training images ////////////////////////////////////////////////////////////
    
            // we will read multiple images into this single image variable as though it is a vector
    
    cv::FileStorage fsTrainingImagesRead("/Users/Rush/Project/0619opencv/0619opencv/images.xml", cv::FileStorage::READ);          // open the training images file
    
    if (fsTrainingImagesRead.isOpened() == false) {                                                 // if the file was not opened successfully
        std::cout << "error, unable to open training images file, exiting program\n\n";         // show error message
        return(0);                                                                              // and exit program
    }
    
    fsTrainingImagesRead["images"] >> matTrainingImagesAsFlattenedFloatsData;           // read images section into Mat training images variable
    fsTrainingImagesRead.release();
    
    // read in training classifications ///////////////////////////////////////////////////
    
    
    //read storage
    
    ///!KNN setting
    cv::Ptr<cv::ml::KNearest>  kNearest (cv::ml::KNearest::create());            // instantiate the KNN object
    //KKNN setting
    
    //  KNN training
    kNearest->train(matTrainingImagesAsFlattenedFloatsData, cv::ml::ROW_SAMPLE, matClassificationIntsData);
    ///!KNN training
    
    // training
    //Ptr<TrainData> td = TrainData::create(SVM_TrainingData,ROW_SAMPLE,SVM_Classes);
    //svm->trainAuto(td);
    
    // training
    
    //! [MatContainer]
    /*
    MatContainer inputREGULARimage =  MatContainer(inputREGULARimage_address,CV_LOAD_IMAGE_COLOR);
    inputREGULARimage.cvToGray();
    inputREGULARimage.Set_THRESHOLD_BINARIZATION(defTHRESHOLD_BIN);
    inputREGULARimage.cvToBinariztion();
    inputREGULARimage.cvEdgelize();
    */
    MatContainer inputOCRimage = MatContainer(inputOCRimage_address,CV_LOAD_IMAGE_COLOR) ;
    inputOCRimage.Set_THRESHOLD_BINARIZATION(defTHRESHOLD_BIN);
    inputOCRimage.Set_THRESHOLD_HORIZONSHAPE(defTHRESHOLD_HOR);
    inputOCRimage.Set_THRESHOLD_VERITICALSHAPE(defTHRESHOLD_VER);
    inputOCRimage.Set_THRESHOLD_EDGE(defTHRESHOLD_EDG);
    //! [MatContainer]
    inputOCRimage.cvToGray();
    inputOCRimage.cvToGauss();
    inputOCRimage.cvToBinariztion();
    inputOCRimage.cvShape();
    //debug
    inputOCRimage.imshow("image");                // Show our image inside it.
    //debug
    //waitkey
    waitKey(1);
    //waitkey
    
    //cut letter
    inputOCRimage.Set_THRESHOLD_CUT(defTHRESHOLD_CUT);
    inputOCRimage.Set_THRESHOLD_LETTERLENGTH(defTHRESHOLD_LETTERLENGTH);
    inputOCRimage.cvCutToLetter();
    //cut letter
    std::string strFinalString;         // declare final string, this will have the final number sequence by the end of the program
    std::vector<Mat> image_vector = inputOCRimage.Getvector();
    std::vector<Mat> image_backtracktosample;

    
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
        //可寫回sample裡
        image_backtracktosample.push_back(image_vector_FlattenedFloat);
        //
        cv::Mat matCurrentChar(0,0,CV_32F);
        Mat matresponse (0,0,CV_32F) , matdistance (0,0,CV_32F) ;
        kNearest->findNearest(image_vector_FlattenedFloat, 1, matCurrentChar,matresponse,matdistance);     // finally we can call find_nearest !!!
        float fltresponse,fltdistance;
        fltresponse = (float)matresponse.at<float>(0,0);
        fltdistance = (float)matdistance.at<float>(0,0);
        float fltCurrentChar = (float)matCurrentChar.at<float>(0, 0);
        cout << "distance: " << fltdistance << endl;
        strFinalString = strFinalString + char(int(fltCurrentChar));        // append current char to full string
    }
    
    cout << "\n\n" << "numbers read = " << strFinalString << endl <<"is it the real answer? ( yes / no )"<<endl;
    string writebackstate;
    cin >> writebackstate;
    //! [imshow]
    
    //! [imshow]
    
    //write the correct answer back
    if(writebackstate == "no") {
        string inputRealAnswer;
        string yesno;
        cout << "Input the real numbers"<<endl;
        inputOCRimage.imshow("the real answer");
        cin >> inputRealAnswer;
        cout <<"your anwser is " << inputRealAnswer << endl;
        cout <<"Comfirmed? ( type 'yes_please') Warning!!!!!!" << endl;
        cin >> yesno;
        if((yesno == "hsuR"||yesno == "yes_please" ) && (inputRealAnswer.length() < 8) ){
            for(int i = 0; i < inputRealAnswer.length(); i++) {
                matClassificationIntsData.push_back(int(inputRealAnswer.at(i)));
                matTrainingImagesAsFlattenedFloatsData.push_back(image_backtracktosample.at(i));
            }
            fsWrite(matClassificationIntsData,matTrainingImagesAsFlattenedFloatsData);
            cout << "sample has been Updated!!"<<endl;
            return 0 ;
        }
        else {
            cout << "bye!!" << endl;
            return 0;
        }
    }
    else if ( writebackstate == "yes" ) {
        string yesno;
        cout <<"Comfirmed? ( type 'yes_please') Warning!!!!!!" << endl;
        cin >> yesno;
        if((yesno == "hsuR"||yesno == "yes_please" )){
            for(int i = 0; i < strFinalString.length(); i++) {
                matClassificationIntsData.push_back(int(strFinalString.at(i)));
                matTrainingImagesAsFlattenedFloatsData.push_back(image_backtracktosample.at(i));
            }
            fsWrite(matClassificationIntsData,matTrainingImagesAsFlattenedFloatsData);
            cout << "sample has been Updated!!"<<endl;
        }
        else
            cout << "bye!!" << endl;
    
        return 0;
    }
    //write the correct answer back
    
    
    
    //! [wait]
    
    waitKey(0); // Wait for a keystroke in the window
    
    //! [wait]
    
    return 0;
    
}
void fsWrite (Mat matClassificationIntsData,Mat matTrainingImagesAsFlattenedFloatsData) {
    cv::FileStorage fsClassificationsWrite("/Users/Rush/Project/0619opencv/0619opencv/classifications.xml", cv::FileStorage::WRITE);
    fsClassificationsWrite << "classifications" << matClassificationIntsData;        // write classifications into classifications section of classifications file
    fsClassificationsWrite.release();
    
    cv::FileStorage fsTrainingImagesWrite("/Users/Rush/Project/0619opencv/0619opencv/images.xml", cv::FileStorage::WRITE);
    fsTrainingImagesWrite << "images" << matTrainingImagesAsFlattenedFloatsData;         // write training images into images section of images file
    fsTrainingImagesWrite.release();
    //store fs

}