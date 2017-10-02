//
//  MatContainer.cpp
//  0619opencv
//
//  Created by Chensteven on 2017/9/25.
//  Copyright (c) 2017年 Rush. All rights reserved.
//

#include <stdio.h>
#include "MatContainer.h"
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace cv;
using namespace std;

MatContainer::MatContainer(Mat _indexMat) {
    _Mat = _indexMat.clone();
}
//直接載入Mat
MatContainer::MatContainer(string _filepath , int CV_LOAD_INDEX) {
    _Mat = imread(_filepath,CV_LOAD_INDEX);
   
}
//setting
//載入透過string地址載入圖片Mat
void MatContainer::Set_THRESHOLD_BINARIZATION (int index_THRESHOLD_BIN )  {
    THRESHOLD_BINIZARATION = index_THRESHOLD_BIN;
}
//設定二值化門檻
void MatContainer::Set_THRESHOLD_CUT( int index_THRESHOLD_CUT) {
    THRESHOLD_CUT = index_THRESHOLD_CUT * _Mat.rows ;
}

void MatContainer::Set_THRESHOLD_HORIZONSHAPE(int index_THRESHOLD_HORIZONSHAPE) {
    THRESHOLD_HORZIONSHAPE = index_THRESHOLD_HORIZONSHAPE * _Mat.cols;
}
void MatContainer::Set_THRESHOLD_VERITICALSHAPE(int index_THRESHOLD_VERITICALSHAPE) {
    THRESHOLD_VERITICALSHAPE = index_THRESHOLD_VERITICALSHAPE * _Mat.rows ;
}
void MatContainer::Set_THRESHOLD_EDGE(int index_THRESHOLD_EDGE) {
    THRESHOLD_EDGE = index_THRESHOLD_EDGE;
}
void MatContainer::Set_THRESHOLD_CAMPAREACCEPTABLE(float index_THRESHOLD_CAMPAREACCEPTABLE) {
    THRESHOLD_CAMPAREACCEPTABLE  = index_THRESHOLD_CAMPAREACCEPTABLE;
}
//設定投影門檻
//setting
std::vector< Mat > MatContainer::Getvector() { return _Vector_Mat_Letters; }
//load vector


//search ROI to be a plate
void MatContainer::cvsearchROI() {
    
}
void MatContainer::resize () {
    Mat temp;
}
//resize
Mat MatContainer::clone() {
    return _Mat.clone();
}
//clone
void MatContainer::cvToGray() {
    Mat _tempMat;
    cvtColor(_Mat, _tempMat,CV_BGR2GRAY);
    _Mat = _tempMat.clone();
}
//色彩轉換至灰階
//
//
void MatContainer::cvToGauss() {
    Mat temp;
    temp = _Mat.clone();
    for(int i = 1; i < _Mat.rows -1; i++ ) {
        for( int j = 1; j < _Mat.cols -1; j++ ) {
            uchar candidate[9] = {
                temp.at<uchar>(i-1,j-1),
                temp.at<uchar>(i-1,j),
                temp.at<uchar>(i-1,j+1),
                temp.at<uchar>(i,j-1),
                temp.at<uchar>(i,j),
                temp.at<uchar>(i,j+1),
                temp.at<uchar>(i+1,j-1),
                temp.at<uchar>(i+1,j),
                temp.at<uchar>(i+1,j+1)
            };
            _Mat.at<uchar>(i,j) = (
                                    candidate [0] +
                                    candidate [2] +
                                    candidate [6] +
                                    candidate [8] +
                                    candidate [1] *2 +
                                    candidate [3] *2 +
                                    candidate [5] *2 +
                                    candidate [7] *2 +
                                    candidate [4] *4
                                    )/16 ;//高斯分佈簡單模型
        }
    }
    //cv::imshow( "GaussDebug", _Mat);//debug

}
//進行高斯模糊(單通道)
//
//
void MatContainer::cvToBinariztion() {
    Mat temp;
    threshold(_Mat,temp,0,255,THRESH_BINARY|THRESH_OTSU);
    //cv::imshow( "BinaryDebug", _Mat);//debug
    _Mat = temp.clone();
}
//二值化
//
//
void MatContainer::cvShape() {
    int HorSum = 0,VerSum = 0;
    int north = 0,south = 0,right = 0,left = 0 ;
    //horizon part
    for(int i = 0; i < _Mat.rows; i++ ) {
        for( int j = 0; j < _Mat.cols ; j++ ) {
            HorSum += (_Mat.at <uchar> (i,j));
        }
        if( HorSum < THRESHOLD_HORZIONSHAPE ) {
            north = i;
            break;
        }
        
        HorSum = 0;
       
    }
    HorSum = 0;
    //hor upper
    for(int i = _Mat.rows-1; i >= 0; i-- ) {
        for( int j = 0; j < _Mat.cols; j++) {
            HorSum += (_Mat.at <uchar> (i,j));
        }
        if( HorSum < THRESHOLD_HORZIONSHAPE ) {
            south = i;
            break;
        }
        HorSum = 0;
    }
    //hor lower
    
    //Vertifical
    for ( int i = 0; i < _Mat.cols; i++ ) {
        for ( int j = 0; j < _Mat.rows; j++ ) {
            VerSum += (_Mat.at <uchar> (j,i));
        }
        if( VerSum < THRESHOLD_VERITICALSHAPE ) {
            left = i;
            break;
        }
        VerSum = 0;
       
    }
    VerSum = 0;
    //ver left
    for ( int i = _Mat.cols; i >= 0; i-- ) {
        for ( int j = 0; j < _Mat.rows; j++ ) {
            VerSum += (_Mat.at <uchar> (j,i));
        }
        if( VerSum < THRESHOLD_VERITICALSHAPE ) {
            
            right = i;
            break;
        }
        
        VerSum = 0;
    }
    //ver right
    //save to temp
    Mat temp(south-north,right-left,_Mat.type());
    for ( int i = 0; i < temp.rows; i++ ) {
        for ( int j = 0; j < temp.cols; j++ ) {
            temp.at <uchar> (i,j) = _Mat.at <uchar>(i + north , j + left);
        }
    }
    
    
    _Mat = temp.clone();
    //cout <<_Mat.rows<<endl;
    //cout <<_Mat.cols<<endl;
    //貼回去

}

///水平切割Shape畫面只有車牌號碼
//
void MatContainer::cvCutToLetter() {
    int leftedge = 0 ,rightedge = 0,VerSum = 0;
    bool isWord = 0;
    for ( int i = 0; i < _Mat.cols; i++ ) {
        for ( int j = 0; j < _Mat.rows; j++ ) {
            VerSum += (_Mat.at <uchar> (j,i));
        }
        //cout << i << VerSum << endl;
        if( VerSum < THRESHOLD_CUT && isWord == 0 ) {
            leftedge = i;
            isWord = 1;
        }
        else if((VerSum > THRESHOLD_CUT && isWord == 1)||(isWord == 1 && i == _Mat.cols-1)) {
            rightedge = i;
            isWord = 0;
            Mat temp(_Mat.rows,rightedge-leftedge,_Mat.type());
            for(int ini = 0; ini < _Mat.rows; ini++) {
                for(int inj = leftedge; inj < rightedge; inj++) {
                    temp.at <uchar> (ini,inj-leftedge) = _Mat.at<uchar>(ini,inj);
                }
            }
            //cv::resize(temp, temp, cvSize(44,79));
            _Vector_Mat_Letters.push_back(temp);
            
            
        }
        //cout << "VerSum" << VerSum << endl;
        VerSum = 0;
    }
    
    //show each letters
    //vector <Mat> ::iterator it_i;
    //int number = 1;
   
    //for(it_i = _Vector_Mat_Letters.begin();it_i != _Vector_Mat_Letters.end() ; ++it_i) {
        //stringstream count;
        //count << number;
        //cv::imshow("No. "+ count.str(),*it_i);
        //cout << (*it_i).rows<<endl;
        //cout << (*it_i).cols<<endl;
        //number++;
    //}
}
//將投影結果進行切割
void MatContainer::cvToZhangSUenThinning() {}
// 骨架化
void MatContainer::imshow(string indexstring) {
    cv::imshow(indexstring,_Mat);
}
//imshow