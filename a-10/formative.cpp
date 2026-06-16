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


double score(int x1, int y1, int x2, int y2, const Mat& img){
    double answer = 0.0;

    for(int dy = -1; dy <= 1; dy++){
        for(int dx = -1; dx <= 1; dx++){
            int v1 = img.at<uchar>(y1+dy, x1+dx);
            int v2 = img.at<uchar>(y2+dy, x2+dx);
            int diff = v1 - v2;
            answer += diff * diff;
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

       
        Mat votes_scaled = Mat::zeros(img.size(), CV_8U);
       
        for (int r = 0; r < votes.rows; r++) {
            for (int c = 0; c < votes.cols; c++) {
                votes_scaled.at<uchar>(r,c) = (uchar)(255.0 * (votes.at<float>(r,c) / maxVal));
            }
        }
               
        bitwise_not(votes_scaled, votes_scaled);

        /*for (int r = 0; r < votes.rows; r++) {
            for (int c = 0; c < votes.cols; c++) {
                if( votes_scaled.at<uchar>(r,c) < 255 ) votes_scaled.at<uchar>(r,c)=(uchar)0;
            }
        }*/

        imwrite("formative/" + pictures[i] + ".png", votes_scaled);

        Mat out = Mat::zeros(img.size(), CV_32F);
        Mat out_scaled = Mat::zeros(img.size(), CV_8U);
        
        cornerHarris(img, out, 3, 3, 0.05);
        
        float minVal = out.at<float>(0,0);
        maxVal = out.at<float>(0,0);
        
        for (int r = 0; r < out.rows; r++) {
            for (int c = 0; c < out.cols; c++) {
                float v = out.at<float>(r,c);
                if (v > maxVal) maxVal = v;
                if (v < minVal) minVal = v;
            }
        }
        
        cout << minVal << " " << maxVal << endl;
        
        for (int r = 0; r < out.rows; r++) {
            for (int c = 0; c < out.cols; c++) {
                float v = out.at<float>(r,c);
                float scaled = (v - minVal) * 255.0f / (maxVal - minVal);
                out_scaled.at<uchar>(r,c) = (uchar)scaled;
            }
        }
        
        bitwise_not(out_scaled, out_scaled);
        imwrite("summative/" + pictures[i] + ".png", out_scaled);


    }

    return 0;
}