//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//
#include <iostream>
//
using namespace std ;
using namespace cv ;
//
int main( int argc , char* argv[] )
{
    string array[] = { "ants" , "bear" , "bird" , "claw" , "eyes" , "hawk" , "lion" , "wolf" } ;
    Mat img = imread( "elvis.png" ) ;
    cvtColor( img , img , COLOR_BGR2GRAY ) ;
   //
   cout << img . size() << endl ;
   //
   cout << img . channels() << endl ;
   //
   int val = img . at< uchar > ( 0 , 0 ) ;
   //
   cout << ( (int)( val ) ) << endl ;
   //
   //
   //
    
    for(int r = 0; r < img.rows; r++){
        for(int c = 0; c < img.cols; c++){
            val = img . at< uchar > ( r , c ) ;
            if(val > 128){
                img.at<uchar>( r , c ) = 255; 
            }else{
                img.at<uchar>( r , c ) = 0;
            }
        }
    }
    
    imwrite( "elvisFORMATIVE.png" , img ) ;
    
   return 0 ;
}
//
// end
//
