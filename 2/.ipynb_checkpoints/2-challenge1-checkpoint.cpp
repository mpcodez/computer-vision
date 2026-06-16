//
#include <fstream>
#include <time.h>
#include <iostream>
//
using namespace std ;
//
//
typedef unsigned char uchar ;
//
//
void save(uchar img[][640], int num) ;
void drawRect( uchar img[][640], int x, int y, int width, int height, int col) ;

//
//
int main( int argc , char* argv[] )
{
    
    for(int image = 0; image < 128; image++){
        //
        uchar    img[480][640] ;

        /*

        1 - Black
        2 - White
        3 - Yellow
        4 - Blue

        */
        
        int color = 1, count = 1;

        for( int c = 0 ; c < 640 ; c+=16 )
        {
            if(count == 2){
                color = 2;
            }if(count == 4){
                count = 0;
                color = 1;
            }

            drawRect(img, 0, c, 16, 480, color);

            count += 1;
        }
        
        
        drawRect(img, 180, 5*image, 64, 32, 3);
        drawRect(img, 180, 5*image-640, 64, 32, 3);
        
        drawRect(img, 300, 5*image, 64, 32, 4);
        drawRect(img, 300, 5*image-640, 64, 32, 4);
        
        
        //
        save(img, image) ;
    }
    //
    return 0 ;
}


void drawRect( uchar img[][640], int x, int y, int width, int height, int col)
{
    for( int r = x ; r < x+height ; r++ )
    {
        for( int c = y ; c < y+width ; c++ )
        {
            if(r >= 0 && r < 480 && c >= 0 && c < 640){
                img[r][c] = col;
            }
        }
    }
}

void save( uchar img[][640], int num)
{
    //
    ofstream fout          ;
    //
    //
    string name = "000" + to_string(num);
    fout.open( "img/frame" + name.substr(name.size()-3, name.size()) + ".pgm" ) ;

    //
    fout << "P6" << endl ;
    //
    fout << "640 480" << endl << "255" << endl ;
    //
    for( int r = 0 ; r < 480 ; r++ )
    {
        for( int c = 0 ; c < 640 ; c++ )
        {
            if(img[r][c] == 1){
                fout << (uchar) 0 << (uchar) 0 << (uchar) 0 << flush ;
            }else if(img[r][c] == 2){
                fout << (uchar) 255 << (uchar) 255 << (uchar) 255 << flush ;
            }else if(img[r][c] == 3){
                fout << (uchar) 0 << (uchar) 0 << (uchar) 255 << flush ;
            }else if(img[r][c] == 4){
                fout << (uchar) 255 << (uchar) 255 << (uchar) 0 << flush ;
            }else{
                fout << (uchar) 175 << (uchar) 175 << (uchar) 175 << flush ;
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