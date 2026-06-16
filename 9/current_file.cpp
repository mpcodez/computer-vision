#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
namespace fs = std::filesystem;


Mat votes;


int main(int argc, char* argv[]) {
    string pictures[] = {"circle01a", "circle01b", "circle02", "chatgpt"};

    double threshold = 75.0;

    for (int i = 0; i < 4; i++) {

        Mat img = imread("pictures/" + pictures[i] + ".png", IMREAD_COLOR);
        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        Mat blurred;
        blur(gray, blurred, Size(3,3));

        Mat edges;
        Canny(blurred, edges, 25.0, 75.0);

        Mat Gx, Gy;
        Sobel(blurred, Gx, CV_64F, 1, 0, 3);
        Sobel(blurred, Gy, CV_64F, 0, 1, 3);

        votes = Mat::zeros(gray.size(), CV_32F);

        for (int r = 1; r < gray.rows - 1; r++) {
            for (int c = 1; c < gray.cols - 1; c++) {

                if (edges.at<uchar>(r, c) != 0) {

                    double gx_val = Gx.at<double>(r, c);
                    double gy_val = Gy.at<double>(r, c);

                    double angle_rad = atan2(gy_val, gx_val);
                    
                    float temp = 1.0;
                    
                    while((r-temp*sin(angle_rad)) < votes.rows && (c+temp*cos(angle_rad)) < votes.cols && (r+temp*sin(angle_rad)) > 0 && (c+temp*cos(angle_rad)) > 0){
                        votes.at<float>((int)(r-temp*sin(angle_rad)), (int)(c+temp*cos(angle_rad))) += 1.0;
                        temp += 0.1;
                    }
                    
                    
                    temp = 1;
                    while((r+temp*sin(angle_rad)) < votes.rows && (c-temp*cos(angle_rad)) < votes.cols && (r-temp*sin(angle_rad)) > 0 && (c-temp*cos(angle_rad)) > 0){
                        votes.at<float>((int)(r+temp*sin(angle_rad)), (int)(c-temp*cos(angle_rad))) += 1.0;
                        temp += 0.1;
                    }
                                                        
                }
            }
        }
        
        cout << "2" << endl;
        
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
        
        cout << pictures[i] << " maxR: " << maxR << " maxC: " << maxC << endl;
                
        cout << "3" << endl;
        
        float centerR[] = {97.0, 197.0, 197.0, 200.0};
        float centerC[] = {74.0, 497.0, 497.0, 100.0};
        
        ofstream out("formative/radius_" + pictures[i] + ".txt");
        
        for (int r = 1; r < gray.rows - 1; r++) {
            for (int c = 1; c < gray.cols - 1; c++) {

                if (edges.at<uchar>(r, c) != 0) {

                    double gx_val = Gx.at<double>(r, c);
                    double gy_val = Gy.at<double>(r, c);

                    double angle_rad = atan2(gy_val, gx_val);
                    
                    float temp = 1.0;
                    
                    while((r-temp*sin(angle_rad)) < votes.rows && (c+temp*cos(angle_rad)) < votes.cols && (r+temp*sin(angle_rad)) > 0 && (c+temp*cos(angle_rad)) > 0){
                        if((int)(r-temp*sin(angle_rad)) == (int)centerR[i] && (int)(c+temp*cos(angle_rad)) == (int)centerC[i]){
                            out << temp << "\n";
                        }
                        temp += 0.1;
                    }
                                        
                    temp = 1;
                    while((r+temp*sin(angle_rad)) < votes.rows && (c-temp*cos(angle_rad)) < votes.cols && (r-temp*sin(angle_rad)) > 0 && (c-temp*cos(angle_rad)) > 0){
                        if((int)(r+temp*sin(angle_rad)) == (int)centerR[i] && (int)(c-temp*cos(angle_rad)) == (int)centerC[i]){
                            out << temp << "\n";
                        }
                        temp += 0.1;
                    }
                    
                }
            }
        }
        
        out.close();
        
        cout << "4" << endl;
        
        Mat votes_scaled = Mat::zeros(gray.size(), CV_8U);
        
        for (int r = 0; r < votes.rows; r++) {
            for (int c = 0; c < votes.cols; c++) {
                votes_scaled.at<uchar>(r,c) = (uchar)(255.0 * (votes.at<float>(r,c) / maxVal));
            }
        }
                
        bitwise_not(votes_scaled, votes_scaled);

        imwrite("formative/" + pictures[i] + ".png", votes_scaled);
    }

    return 0;
}