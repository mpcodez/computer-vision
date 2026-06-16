//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include <fstream>
//
using namespace std ;
using namespace cv ;
//
typedef unsigned char uchar ;
//
const int W = 480 ;
const int H = 480 ;
//
void save( uchar img[][640] ) ;
//
int main( int argc , char* argv[] )
{
    
    ifstream fin       ;
    //
    int      r , c     ;
    //
    string   s         ;
    char     ch        ;
    //
    uchar    tea[H][W] ;
    //
    //
    //
    fin . open( "teapot.pgm" ) ;
    //
    fin >> s ; // P5
    fin >> s ; // 775
    fin >> s ; // 900
    fin >> s ; // 255
    //
    // fin >> ch ; // would skip the newline
    //
    fin.read( &ch , 1 ) ; // reads newline
    //
    for( r = 0 ; r < H ; r++ )
    {
        for( c = 0 ; c < W ; c++ )
        {
            fin . read( &ch , 1 ) ;
            //
            tea[r][c] = (uchar)ch ;
        }
    }
    //
    fin.close() ;
    //
    
    uchar img[480][640];
    
    RNG rng(8) ;
    rng.state = 1880238;
    
    
    for (int r = 0; r < 480; r++) {
        for (int c = 0; c < 160; c++) {
            img[r][c] = (rng.next() % 255)+1;
        }
    }
    
    int value = 0;
    
    for (int r = 0; r < 480; r++) {
        for (int c = 160; c < 640; c++) {
            if(value == tea[r][c-160]){
                img[r][c] = img[r][c-160+5];
            }else{
                img[r][c] = img[r][c-160];
            }
            
        }
    }
    
    //
    save( img ) ;
    //
    return 0 ;
}

void save( uchar img[][640])
{
    //
    ofstream fout          ;
    //
    //
    fout . open( "demo.pgm" ) ;

    //
    fout << "P5" << endl ;
    //
    fout << "640 480" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 480 ; r++ )
    {
        for( int c = 0 ; c < 640 ; c++ )
        {
            fout << img[r][c] << flush ;
            //
            //               NOT endl !!!
        }
    }
    //
    fout . close() ;
}
