#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah", "chess", "crab_spider", "peppers", "peru", "seahorse"};

    for(int picture = 0; picture < 9; picture++)
    {
        Mat img = imread("pictures/" + pictures[picture] + ".png");

        cout << pictures[picture] << endl;

        vector<Vec3f> splits;
        splits.push_back(Vec3f(85, 85, 85));
        splits.push_back(Vec3f(170, 170, 170));

        vector<Vec3f> finalColors(splits.size(), Vec3f(0,0,0));

        for(int iter = 0; iter < 10; iter++)
        {
            vector<Vec3f> sum(splits.size(), Vec3f(0,0,0));
            vector<int> count(splits.size(), 0);

            for(int r = 0; r < img.rows; r++){
                for(int c = 0; c < img.cols; c++){
                    Vec3b pix = img.at<Vec3b>(r,c);
                    Vec3f p(pix[0], pix[1], pix[2]);

                    int bestIdx = 0;
                    float bestDist = (p - splits[0]).dot(p - splits[0]);

                    for(int s = 1; s < splits.size(); s++){
                        float d = (p - splits[s]).dot(p - splits[s]);
                        if(d < bestDist){
                            bestDist = d;
                            bestIdx = s;
                        }
                    }

                    sum[bestIdx] += p;
                    count[bestIdx]++;
                }
            }

            // update splits and store mean colors
            for(int s = 0; s < splits.size(); s++){
                if(count[s] > 0){
                    Vec3f mean = sum[s] * (1.0f / count[s]);
                    splits[s] = mean;
                    finalColors[s] = mean; // store final color for later assignment
                }
            }

            // print for debugging
            cout << "Iteration " << iter+1 << " splits:" << endl;
            for(int s = 0; s < splits.size(); s++){
                cout << splits[s] << " ";
            }
            cout << endl << "--------------------" << endl;
        }

        // assign final pixel values based on mean of bucket
        for(int r = 0; r < img.rows; r++){
            for(int c = 0; c < img.cols; c++){
                Vec3b pix = img.at<Vec3b>(r,c);
                Vec3f p(pix[0], pix[1], pix[2]);

                int bestIdx = 0;
                float bestDist = (p - splits[0]).dot(p - splits[0]);

                for(int s = 1; s < splits.size(); s++){
                    float d = (p - splits[s]).dot(p - splits[s]);
                    if(d < bestDist){
                        bestDist = d;
                        bestIdx = s;
                    }
                }

                Vec3f assignColor = finalColors[bestIdx];
                img.at<Vec3b>(r,c) = Vec3b(
                    saturate_cast<uchar>(round(assignColor[0])),
                    saturate_cast<uchar>(round(assignColor[1])),
                    saturate_cast<uchar>(round(assignColor[2]))
                );
            }
        }

        imwrite("part2/" + string(pictures[picture]) + ".png", img);
        cout << "Saved: " << pictures[picture] << endl;
    }

    return 0;
}
