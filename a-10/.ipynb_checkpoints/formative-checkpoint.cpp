#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <algorithm>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;


double score(int x1, int y1, int x2, int y2, Mat img){

    int vals[] = {-1, 0, 1};
    double answer = 0.0;
    
    for(int dx = 0; dx <= 2; dx++){
        for(int dy = 0; dy <= 2; dy++){
            uchar val1 = img.at<uchar>(y1+dy, x1+dx);
            uchar val2 = img.at<uchar>(y2+dy, x2+dx);
            answer += (((double)val1 - (double)val2)*((double)val1 - (double)val2));
        }
    }

    return answer;
}

Mat votes;


int main(int argc, char* argv[]) {
    
    string pictures[] = {"image", "chess"};

    for (int i = 0; i < 2; i++) {

        Mat img = imread("pictures/" + pictures[i] + ".png", IMREAD_COLOR);
        cvtColor(img, img, COLOR_BGR2GRAY);

        votes = Mat::zeros(img.size(), CV_32F);

        for (int y = 1; y < img.rows - 1; y++) {
            for (int x = 1; x < img.cols - 1; x++) {

                double min = score(x, y, x+1, y, img);

                double scores[] = {score(x, y, x, y+1, img), score(x, y, x+1, y+1, img), score(x, y, x+1, y-1, img)};

                for(int i = 0; i < 3; i++){
                    if(scores[i] < min){
                        min = scores[i];
                    }
                }
                
                votes.at<float>(y, x) = (float)min;
                                                        
            }
        }
                
        float maxVal = 0;
        int maxR = 0;
        int maxC = 0;
        
        for (int r = 0; r < votes.rows; r++) {
            for (int c = 0; c < votes.cols; c++) {
                if(votes.at<float>(r,c) > maxVal){
                    maxVal = votes.at<float>(r,c);
                    maxR = r;
                    maxC = c;
                }
            }
        }

        cout << maxR << " " << maxC << endl;
        cout << votes.at<float>(maxR,maxC-1) << " " << votes.at<float>(maxR,maxC) << " " << votes.at<float>(maxR,maxC+1) << endl;
        
        Mat votes_scaled = Mat::zeros(img.size(), CV_8U);
        
        for (int r = 0; r < votes.rows; r++) {
            for (int c = 0; c < votes.cols; c++) {
                votes_scaled.at<uchar>(r,c) = (uchar)(255.0 * (votes.at<float>(r,c) / maxVal));

                if(r == maxR && c == maxC){
                    cout << votes.at<float>(r,c) << " " << maxVal << " " << (votes.at<float>(r,c) / maxVal) << " " << (255.0 * (votes.at<float>(r,c) / maxVal)) << endl;
                }
            }
        }

        cout << (int)votes_scaled.at<uchar>(maxR,maxC-1) << " " << (int)votes_scaled.at<uchar>(maxR,maxC) << " " << (int)votes_scaled.at<uchar>(maxR,maxC+1) << endl;
                
        bitwise_not(votes_scaled, votes_scaled);

        cout << (int)votes_scaled.at<uchar>(maxR,maxC-1) << " " << (int)votes_scaled.at<uchar>(maxR,maxC) << " " << (int)votes_scaled.at<uchar>(maxR,maxC+1) << endl;


        for (int r = 0; r < votes.rows; r++) {
            for (int c = 0; c < votes.cols; c++) {
        //         if( votes_scaled.at<uchar>(r,c) < 200 ) cout << r << " " << c << endl ;
            }
        }
        imwrite("formative/" + pictures[i] + ".png", votes_scaled);
    }

    return 0;
}