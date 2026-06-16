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
        
        if(x != 999){
            if(-1*x > maxX){
                maxX = -1*x;
            }

            if(y > maxY){
                maxY = y;
            }

            if(-1*x < minX){
                minX = -1*x;
            }

            if(y < minY){
                minY = y;
            }
        }
    }

    fin.close();
    
    
    uchar    img[480][640] ;

    for(int c = 0; c < 640; c++){
        for(int r = 0; r < 480; r++){
            img[r][c] = 255;
        }
    }
    
    cout << "SIZE: " << points.size() << endl;
    cout << "MIN - X: " << minX << endl;
    cout << "MAX - X: " << maxX << endl;
    cout << "MIN - Y: " << minY << endl;
    cout << "MAX - Y: " << maxY << endl;
    
    pair<double, double> previous = {999, 999};
        
    for(pair p : points){
        
        if(p.first != 999){
            double sx = double(-1*p.first - minX) / double(maxX - minX);
            double sy = double(p.second - minY) / double(maxY - minY);
            int xVAL = int(sx * (608 - 1));
            int yVAL = 456 - 1 - int(sy * (456 - 1));

            img[yVAL+12][640 - xVAL - 16] = 0;
            
        
            if(previous.first != 999){
                int diffX = ((640 - xVAL - 16) - previous.first);
                int diffY = ((yVAL+12) - previous.second);
                
                cout << (int)previous.first << " " << (int)previous.second << " " << diffY << endl;
                cout << (640 - xVAL - 16) << " " << (yVAL+12) << " " << diffX << endl;
                cout << "--------------------------------------------------------" << endl;
                /*
                if(diffY == 0 && diffX != 0){
                    for(int i = previous.first; i<= (640 - xVAL - 16); i++){
                        img[yVAL+12][i] = 0;
                    }
                }
                if(diffY != 0 && diffX == 0){
                    for(int i = previous.second; i<= yVAL+12; i++){
                        img[i][640 - xVAL - 16] = 0;
                    }
                }
                */
                for(int i = 0; i <= 100; i++){
                    img[(int)(previous.second + (diffY*i)*0.01)][(int)(previous.first + (diffX*i)*0.01)] = 0;
                }
            }
            
            previous = {640 - xVAL - 16, yVAL+12};
        }else{
            previous = {999, 999};
        }
        
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