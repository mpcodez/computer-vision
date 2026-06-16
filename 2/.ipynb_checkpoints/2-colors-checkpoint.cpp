//
#include <fstream>
//
using namespace std ;
//
typedef unsigned char uchar ;
//
//
void save( uchar img[][640] ) ;
void drawSquare( uchar img[][640], int x, int y, int col) ;

//
//
int main( int argc , char* argv[] )
{
    //
    uchar    img[480][640] ;
    
    for( int c = 0 ; c < 640 ; c++ )
    {
        for( int r = 0 ; r < 480 ; r++ )
        {
            if(r%20 == 0 && c%20 == 0){
                if(r >= 230 && r < 250){
                    drawSquare(img, r, c, 255);
                }else{
                    drawSquare(img, r, c, 0);
                }
            }else if(r%20 == 10 && c%20 == 10){
                if(r >= 230 && r < 250){
                    drawSquare(img, r, c, 255);
                }else{
                    drawSquare(img, r, c, 0);
                }
            }else if(r%20 == 0 && c%20 == 10){
                if(c >= 310 && c < 330){
                    drawSquare(img, r, c, 255);
                }else{
                    drawSquare(img, r, c, 100);
                }
            }else if(r%20 == 10 && c%20 == 0){
                if(c >= 310 && c < 330){
                    drawSquare(img, r, c, 255);
                }else{
                    drawSquare(img, r, c, 100);
                }
            }
            
        }
    }

    //
    save( img ) ;
    //
    return 0 ;
}


void drawSquare( uchar img[][640], int x, int y, int col)
{
    for( int r = x ; r < x+10 ; r++ )
    {
        for( int c = y ; c < y+10 ; c++ )
        {
            img[r][c] = col;
        }
    }
}

void save( uchar img[][640] )
{
    //
    ofstream fout          ;
    //
    //
    fout . open( "demo.pgm" ) ;
    //
    fout << "P6" << endl ;
    //
    fout << "640 480" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 480 ; r++ )
    {
        for( int c = 0 ; c < 640 ; c++ )
        {
            if(img[r][c] == 0){
                fout << (uchar) 255 << (uchar) 255 << (uchar) 255 << flush ;
            }else if(img[r][c] == 100){
                fout << (uchar) 0 << (uchar) 255 << (uchar) 0 << flush ;
            }else{
                fout << (uchar) 255 << (uchar) 0 << (uchar) 0 << flush ;
            }
           
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

            
/// fout << (uchar) 0 << (uchar) 255 << (uchar) 0 << flush ;
/// uchar c1 = (uchar) 0;
         