#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

// BLUE, GREEN, RED --> 0, 1, 2 --> blue = img[100,100,0]

float distance(int b, int g, int r, Vec3b split) {
      return sqrt(pow((float)b - (float)split[0], 2) + pow((float)g - (float)split[1], 2) + pow((float)r - (float)split[2], 2));
}

int main(int argc, char* argv[])
{
    string pictures[] = {"aloha", "bluefin_trevally", "chameleon", "cheetah", "chess", "crab_spider", "peppers", "peru", "seahorse"};

    for(int picture = 0; picture < 9; picture++)
    {
        Mat img = imread("pictures/" + pictures[picture] + ".png");
        if(img.empty()){
            cerr << "Failed to load image: " << pictures[picture] << ".png" << endl;
            continue;
        }
        
        cout << pictures[picture] << endl;
        
        
        vector<Vec3b> splits; //k = whatever
        splits.push_back(Vec3b(0, 0, 0));
        splits.push_back(Vec3b(37, 37, 37));
        splits.push_back(Vec3b(67, 67, 67));
        splits.push_back(Vec3b(130, 130, 130));
        splits.push_back(Vec3b(189, 189, 189));
        splits.push_back(Vec3b(255, 255, 255));
        
        vector<Vec3b> prev; //k = whatever
        prev.push_back(Vec3b(0, 0, 0));
        prev.push_back(Vec3b(37, 37, 37));
        prev.push_back(Vec3b(67, 67, 67));
        prev.push_back(Vec3b(130, 130, 130));
        prev.push_back(Vec3b(189, 189, 189));
        prev.push_back(Vec3b(255, 255, 255));
        
        int COUNTME = 0;
        
        while(true){
            
            float sum[splits.size()][3] = {0.0};
            // x is the SPLIT and y is the COLOR

            float count[splits.size()] = {0.0};
            // how many points fall under each section?
                        
            for(int r = 0; r < img.rows; r++){
                for(int c = 0; c < img.cols; c++){
                    
                    int blue = img.at<Vec3b>(r,c)[0];
                    int green = img.at<Vec3b>(r,c)[1];
                    int red = img.at<Vec3b>(r,c)[2];
                                        
                    int whichSplit = 0;
                    float bestDist = distance(blue, green, red, splits[0]);

                    for(int split = 1; split < splits.size(); split++){
                        float d = distance(blue, green, red, splits[split]);
                        
                        if(d < bestDist){
                            bestDist = d;
                            whichSplit = split;
                        }
                    }

                    sum[whichSplit][0] += blue;
                    sum[whichSplit][1] += green;
                    sum[whichSplit][2] += red;
                    count[whichSplit]++;

                }
            }
            
            for(int s = 0; s < splits.size(); s++){
                Vec3f mean1 = sum[s][0]/(1.0*count[s]);
                Vec3f mean2 = sum[s][1]/(1.0*count[s]);
                Vec3f mean3 = sum[s][2]/(1.0*count[s]);
                splits[s] = Vec3b((int)mean1[0], (int)mean2[0], (int)mean3[0]);
            }
            
            int breakNow = 1;
            
            for(int split = 1; split < splits.size(); split++){
                if(prev[split] == splits[split]){
                    breakNow *= 1;
                }else{
                    breakNow *= 0;
                }
            }
            
            if(breakNow == 1){
                break;
            }else{
               prev = splits;
               COUNTME += 1;
            }

            

        }
        
        for(int r = 0; r < img.rows; r++){
            for(int c = 0; c < img.cols; c++){
                
                int blue = img.at<Vec3b>(r,c)[0];
                int green = img.at<Vec3b>(r,c)[1];
                int red = img.at<Vec3b>(r,c)[2];

                int whichSplit = 0;
                float bestDist = distance(blue, green, red, splits[0]);

                for(int split = 1; split < splits.size(); split++){
                    float d = distance(blue, green, red, splits[split]);

                    if(d < bestDist){
                        bestDist = d;
                        whichSplit = split;
                    }
                }    
                
                img.at<Vec3b>(r, c)[0] = splits[whichSplit][0];
                img.at<Vec3b>(r, c)[1] = splits[whichSplit][1];
                img.at<Vec3b>(r, c)[2] = splits[whichSplit][2];

            }
        }
        
        /* logging values but idk
        cout << splits[0] << endl;
        cout << splits[1] << endl;
        cout << COUNTME << endl;
        cout << "-----------------------------" << endl;
        */
        
        imwrite( "k6/" + string(pictures[picture]) + ".png"  , img );
    }

    return 0;
}