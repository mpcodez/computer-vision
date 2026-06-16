//
#include <vector>
//
#include <iostream>
//
#include <fstream>
//
using namespace std ;
typedef unsigned char uchar ;
//


void save( uchar img[][640] ) ;
void drawSquare( uchar img[][1200], int x, int y, int col);


int main( int argc , char* argv[] )
{

    ifstream fin;
    vector<pair<double, double>> points;
    double x, y;
    string fname;

    cout << "Filename: " << flush;
    cin >> fname;

    fin.open(fname + ".txt");
    if (!fin.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    
    double minX = 100000000.0, maxX = 0.0, maxY = 0.0, minY = 100000000.0;

    // Read file as (x, y) pairs
    while (fin >> x >> y) {
        points.push_back({x, y});
        
        if(x > maxX){
            maxX = x;
        }
        
        if(y > maxY){
            maxY = y;
        }
        
        if(x < minX){
            minX = x;
        }
        
        if(y < minY){
            minY = y;
        }
    }

    fin.close();
    
    
    uchar    img[480][640] ;
    
    double TOPsy = double(410000 - minY) / double(maxY - minY);
    int TOPyVAL = 456 - 1 - int(TOPsy * (456 - 1));
    
    double BOTsy = double(380000 - minY) / double(maxY - minY);
    int BOTyVAL = 456 - 1 - int(BOTsy * (456 - 1));
    
    cout << "TOP - Y: " << TOPyVAL << endl;
    cout << "BOT - Y: " << BOTyVAL << endl;

    for(int c = 0; c < 640; c++){
        for(int r = 0; r < TOPyVAL; r++){
            img[r][c] = 255;
        }
        for(int r = TOPyVAL; r < BOTyVAL; r++){
            img[r][c] = 127;
        }
        for(int r = BOTyVAL; r < 480; r++){
            img[r][c] = 255;
        }
    }
    
    cout << "SIZE: " << points.size() << endl;
    cout << "MIN - X: " << minX << endl;
    cout << "MAX - X: " << maxX << endl;
    cout << "MIN - Y: " << minY << endl;
    cout << "MAX - Y: " << maxY << endl;
    
    for(pair p : points){

        double sx = double(p.first - minX) / double(maxX - minX);
        double sy = double(p.second - minY) / double(maxY - minY);
        int xVAL = int(sx * (608 - 1));
        int yVAL = 456 - 1 - int(sy * (456 - 1));
        
        img[yVAL+12][xVAL+16] = 0;
    }
    
    save(img);
    
    return 0 ;
}

void save( uchar img[][640] )
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
        }
    }
    //
    fout . close() ;
}
//