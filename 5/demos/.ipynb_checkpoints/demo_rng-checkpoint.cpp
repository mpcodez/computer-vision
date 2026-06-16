//
// OpenCV
//
// https://docs.opencv.org/4.5.4/d1/dd6/classcv_1_1RNG.html
//
// *** replace "7" with your Student ID number ***
//
// this seeds the state of the random number generator
//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn/dnn.hpp>
//
#include <time.h>
#include <iostream>
//
using namespace std ;
using namespace cv  ;
//
int main( int argc , char* argv[] )
{
   RNG rng(8) ;
   //
   // rng . state = time( NULL ) ;
   //
   unsigned int x ;
   //
   cout << UINT_MAX << endl ;
   cout <<  INT_MAX << endl ;
   //
   rng . state = 1880238 ;
   //
   cout << rng . state << endl ;
   //
   for( int j = 0 ; j < 4 ; j++ )
   {
      x = rng . next() ;
      //
      cout << j << " " << x << " " << rng . state << endl ;
   }
   //
   //
   //
   return 0 ;
}
//
// end
//
