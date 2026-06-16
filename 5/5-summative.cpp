//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//
#include <time.h>
#include <iostream>
//
#include <vector>
//
#include <iostream>
//
#include <fstream>
//

//
using namespace std ;
using namespace cv  ;
//
int main( int argc , char* argv[] )
{
    string array[] = {"elvis", "ants" , "bear" , "bird" , "claw" , "eyes" , "hawk" , "lion" , "wolf" } ;
    
    unsigned int randomTable[64][64] ;

    ifstream fin;
    string fname;

    cout << "Filename: " << flush;
    cin >> fname;

    fin.open(fname + ".txt");
    if (!fin.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    
    // Read file as (x, y) pairs
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            fin >> randomTable[i][j];
        }
    }
    
    fin.close();
    
    for(int animal = 0; animal < 9; animal++){
        
        int black = 0, white = 0, grey = 0, val = 0;
        int black2 = 0, white2 = 0;
        
        Mat img = imread( "animals/" + string(array[animal]) + ".png" ) ;
        cvtColor( img , img , COLOR_BGR2GRAY ) ;
        
        Mat img2 = imread( "animals/" + string(array[animal]) + ".png" ) ;
        cvtColor( img2 , img2 , COLOR_BGR2GRAY ) ;
        

        for(int r = 0; r < img.rows; r++){
            for(int c = 0; c < img.cols; c++){
                val = img . at< uchar > ( r , c ) ;
                if(val < 64){
                    img.at<uchar>( r , c ) = 0;
                    black += 1;
                }else if(val >= 64 && val < 192){
                    img.at<uchar>( r , c ) = 127;
                    grey += 1;
                }else{
                    img.at<uchar>( r , c ) = 255;
                    white += 1;
                }
                
                if(val < randomTable[r%64][c%64]){
                    img2.at<uchar>( r , c ) = 0;
                    black2 += 1;
                }else{
                    img2.at<uchar>( r , c ) = 255;
                    white2 += 1;
                }

            }
        }

        imwrite( "part3/" + string(array[animal]) + ".png"  , img );
        imwrite( "part4/" + string(array[animal]) + ".png"  , img2 );
  
                
        cout << "FIXED THRESHOLD: " << string(array[animal]) << endl;
        cout << "BLACK: " << (black*1.0)/(black+grey+white) << endl;
        cout << "GREY: " << (grey*1.0)/(black+grey+white) << endl;
        cout << "WHITE: " << (white*1.0)/(black+grey+white) << endl;
        
        /// Blue Noise
        
        cout << "NOISY THRESHOLD: " << string(array[animal]) << endl;
        cout << "BLACK: " << (black2*1.0)/(black2+white2) << endl;
        cout << "WHITE: " << (white2*1.0)/(black2+white2) << endl;


    }
    
   return 0 ;
    
}
//
// end
//
