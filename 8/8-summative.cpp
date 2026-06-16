#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

const Scalar COLOR_WHITE = Scalar(255, 255, 255);
const Scalar COLOR_GREEN = Scalar(0, 255, 0);
const Scalar COLOR_RED   = Scalar(0, 0, 255);
const Scalar COLOR_BLACK = Scalar(0, 0, 0);

int getG(const Mat& gray, int r, int c) {
    int n1 = gray.at<uchar>(r - 1, c - 1);
    int n2 = gray.at<uchar>(r - 1, c);
    int n3 = gray.at<uchar>(r - 1, c + 1);
    int n4 = gray.at<uchar>(r, c - 1);
    int n5 = gray.at<uchar>(r, c + 1);
    int n6 = gray.at<uchar>(r + 1, c - 1);
    int n7 = gray.at<uchar>(r + 1, c);
    int n8 = gray.at<uchar>(r + 1, c + 1);

    int Gx_calc = (n3 + (2 * n5) + n8) - (n1 + (2 * n4) + n6);
    
    int Gy_calc = (n6 + (2 * n7) + n8) - (n1 + (2 * n2) + n3);

    int G = abs(Gx_calc) + abs(Gy_calc);
    
    return G;
}


int main()
{
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah", 
                         "chess", "crab_spider", "peppers", "peru", "seahorse"};

    const int lowThres = 25;
    const int highThres = 75;
    
    cout << "Custom Canny Threshold Visualization (Low: " << lowThres << ", High: " << highThres << ")" << endl;

    for (int i = 0; i < 9; ++i) {
        string pictureName = pictures[i];
        string inPath = "pictures/" + pictureName + ".png";
        Mat img = imread(inPath, IMREAD_COLOR);

        if (img.empty()) {
            cerr << "ERROR: Failed to read " << inPath << endl;
            continue;
        }

        cout << "Processing: " << pictureName << endl;

        Mat gray;
        cvtColor(img, gray, COLOR_BGR2GRAY);

        Mat blurred;
        blur(gray.clone(), blurred, Size(3,3));
        
        Mat output_color = Mat::zeros(blurred.size(), CV_8UC3);
        cvtColor(blurred, output_color, COLOR_GRAY2BGR);
        
        for (int r = 1; r < blurred.rows - 1; r++) {
            for (int c = 1; c < blurred.cols - 1; c++) {
                
                int n1 = blurred.at<uchar>(r - 1, c - 1);
                int n2 = blurred.at<uchar>(r - 1, c);
                int n3 = blurred.at<uchar>(r - 1, c + 1);
                int n4 = blurred.at<uchar>(r, c - 1);
                int n5 = blurred.at<uchar>(r, c + 1);
                int n6 = blurred.at<uchar>(r + 1, c - 1);
                int n7 = blurred.at<uchar>(r + 1, c);
                int n8 = blurred.at<uchar>(r + 1, c + 1);

                int Gx = (n3 + (2 * n5) + n8) - (n1 + (2 * n4) + n6);
                int Gy = (n6 + (2 * n7) + n8) - (n1 + (2 * n2) + n3);

                int G = abs(Gx) + abs(Gy);

                Vec3b& pixel = output_color.at<Vec3b>(r, c);

                if (G < lowThres) {
                    pixel[0] = COLOR_WHITE[0]; pixel[1] = COLOR_WHITE[1]; pixel[2] = COLOR_WHITE[2];
                } 
                else if (G >= highThres) {
                    pixel[0] = COLOR_RED[0]; pixel[1] = COLOR_RED[1]; pixel[2] = COLOR_RED[2];
                } 
                else {
                    
                    double angle = atan2((double)Gy, (double)Gx) * 180.0 / M_PI;
                    if (angle < 0) angle += 180.0;
                    
                    int neighbor1 = 0;
                    int neighbor2 = 0;
                    
                    if ((angle >= 0.0 && angle < 22.5) || (angle >= 157.5 && angle < 180.0)) {
                        neighbor1 = getG(blurred, r, c - 1);
                        neighbor2 = getG(blurred, r, c + 1);
                    } else if (angle >= 22.5 && angle < 67.5) {
                        neighbor1 = getG(blurred, r - 1, c + 1);
                        neighbor2 = getG(blurred, r + 1, c - 1);
                    } else if (angle >= 67.5 && angle < 112.5) {
                        neighbor1 = getG(blurred, r - 1, c);
                        neighbor2 = getG(blurred, r + 1, c);
                    } else {
                        neighbor1 = getG(blurred, r - 1, c - 1);
                        neighbor2 = getG(blurred, r + 1, c + 1);
                    }

                    if (G > neighbor1 && G > neighbor2) {
                        pixel[0] = COLOR_BLACK[0]; pixel[1] = COLOR_BLACK[1]; pixel[2] = COLOR_BLACK[2];
                    } else {
                        pixel[0] = COLOR_GREEN[0]; pixel[1] = COLOR_GREEN[1]; pixel[2] = COLOR_GREEN[2];
                    }
                }
            }
        }

        string outPath = "summative/" + pictureName + ".png";
        imwrite(outPath, output_color);
        cout << " Wrote: " << outPath << endl;
    }

    return 0;
}