#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    string animals[] = {"elvis", "ants", "bear", "bird", "claw", "eyes", "hawk", "lion", "wolf"};

    for(int animal = 0; animal < 9; animal++)
    {
        ofstream myfile;
        string filename = "right/" + animals[animal] + ".txt";
        myfile.open(filename);
        if(!myfile.is_open()){
            cerr << "Failed to open " << filename << endl;
            continue;
        }

        Mat img = imread("animals/" + animals[animal] + ".png");
        if(img.empty()){
            cerr << "Failed to load image: " << animals[animal] << ".png" << endl;
            continue;
        }

        cvtColor(img, img, COLOR_BGR2GRAY);

        int hist[256] = {0};

        for(int r = 0; r < img.rows; r++){
            for(int c = 0; c < img.cols; c++){
                uchar val = img.at<uchar>(r, c);
                hist[val]++;
            }
        }
        
        float total = 1.0 * img.rows * img.cols;
        float sum = 0.0;

        for(int i = 0; i < 256; i++){
            sum += hist[i]*1.0;
            myfile << sum/(total) << "\n";
        }

        myfile.close();
        cout << "Histogram for " << animals[animal] << " saved to " << filename << endl;
    }

    return 0;
}
