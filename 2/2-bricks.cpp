//
#include <fstream>
//
using namespace std ;
//
typedef unsigned char uchar ;
//
//
void save( uchar img[][1200] ) ;
void drawSquare( uchar img[][1200], int x, int y, int col);
//
int main( int argc , char* argv[] )
{
    //
    uchar    img[560][1200] ;
    //
    //
    
    int count = 0;
    for( int r = 0 ; r < 560 ; r+=70){
        int color = 255;
        if(r%140==0){
            count = 1;
        }else{
            count = 0;
        }
        
        for(int c = 0 ; c < 1200 ; c+=48){
            if(count == 2){
                count = 0;
                if(color == 255){
                    color = 0;
                }else{
                    color = 255;
                }
            }
            
            drawSquare(img, r, c, color);
            count += 1;
        }
    }
    
    for( int r = 0 ; r <= 560 ; r+=70){
        for(int c = 0 ; c < 1200 ; c++){
            if(r-2 > 0){
                img[r-2][c] = 127;
                img[r-1][c] = 127;
            }
            if(r+1 != 561){
                img[r+1][c] = 127;
                img[r][c] = 127;
            }
        }
    }
    
    //
    save( img ) ;
    //
    return 0 ;
}

void drawSquare( uchar img[][1200], int x, int y, int col)
{
    for( int r = x ; r < x+70 ; r++ )
    {
        for( int c = y ; c < y+48 ; c++ )
        {
            img[r][c] = col;
        }
    }
}
//
void save( uchar img[][1200] )
{
    //
    ofstream fout          ;
    //
    //
    fout . open( "demo.pgm" ) ;
    //
    fout << "P5" << endl ;
    //
    fout << "1200 560" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 560 ; r++ )
    {
        for( int c = 0 ; c < 1200 ; c++ )
        {
            fout << img[r][c] << flush ;
            //
            //               NOT endl !!!
        }
    }
    //
    fout . close() ;
}
//
// end
//
