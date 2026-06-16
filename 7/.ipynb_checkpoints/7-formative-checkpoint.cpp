#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// BLUE, GREEN, RED --> 0, 1, 2 --> blue = img[100,100,0]

float distance(int b, int g, int r, Vec3b split) {
      return sqrt(pow((float)b - (float)split[0], 2) + pow((float)g - (float)split[1], 2) + pow((float)r - (float)split[2], 2));
}

void drawSquare(Mat format, int r, int c, Vec3b color){
    for(int row = r; row < r+100; row++){
        for(int col = c; col < c+100; col++){
            format.at<Vec3b>(row, col)[0] = color[0];
            format.at<Vec3b>(row, col)[1] = color[1];
            format.at<Vec3b>(row, col)[2] = color[2];
            
            if(row == r || row == r + 100 || col == c || col == c + 100){
                format.at<Vec3b>(row, col)[0] = 0;
                format.at<Vec3b>(row, col)[1] = 0;
                format.at<Vec3b>(row, col)[2] = 0;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah", "chess", "crab_spider", "peppers", "peru", "seahorse"};

    for(int picture = 0; picture < 9; picture++)
    {
        Mat temp = imread("pictures/" + pictures[picture] + ".png");        
        Mat img = imread("pictures/" + pictures[picture] + ".png");        

        cout << pictures[picture] << endl;
                 
        cvtColor(img, img, COLOR_BGR2GRAY);

        int hist[256] = {0};

        for(int blur = 0; blur <= 9; blur++){
            for(int r = 1; r < img.rows-1; r++){
                for(int c = 1; c < img.cols-1; c++){
                    int val = ((int)temp.at<uchar>(r, c) + (int)temp.at<uchar>(r-1, c) + (int)temp.at<uchar>(r+1, c) + (int)temp.at<uchar>(r, c+1) + (int)temp.at<uchar>(r-1, c+1) + (int)temp.at<uchar>(r+1, c+1)+(int)temp.at<uchar>(r, c-1) + (int)temp.at<uchar>(r-1, c-1) + (int)temp.at<uchar>(r+1, c-1))/9;
                    img.at<uchar>(r, c) = (uchar)val;
                }
            }
        }

        imwrite("formative/" + string(pictures[picture]) + ".png", img);
    }

    return 0;
}