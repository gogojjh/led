#include "base.h"
#include "contour.h"
#include "orbmatching.h"

static const std::string OPENCV_WINDOW = "Image window";
static const std::string RESULT_WINDOW = "Result window";
int number = 0;


bool flag_obj=0;
bool flag_wawa=0;
bool flag_controlstream=0;

int counter_obj=0;
int counter_wawa=0;


int main()
{
    //VideoCapture capture("/home/gogojjh/QT/led/data/test4.avi");
    /*
    VideoCapture capture(1);
    if (!capture.isOpened())
    {
        cout << "failed to open the camera..." << endl;
        return 0;
    }*/

    Mat frame, result;
    Point2f goal(0,0);

    namedWindow(OPENCV_WINDOW, 2);
    namedWindow(RESULT_WINDOW, 2);
//    queue<short> q;



    while (1)
    {
        //capture >> frame;

        /*
        number ++;
        if (number % 5 == 0 )
        {
            char saveFileName[50];
            sprintf(saveFileName, "/home/gogojjh/QT/led/image/%d.jpg", number/5);
            imwrite(saveFileName, frame);
        }*/


        frame = imread("/home/sd/document/graph/8_7/REGION4/g20160807_021244.524.jpg", 1);
        frame = imread("/home/sd/document/graph/8_7/REGION4/g20160807_021252.518.jpg", 1);


        resize(frame, frame, Size(frame.cols/IMAGE_SIZE_COL, frame.rows/IMAGE_SIZE_ROW));
        int ans1=0;//ans2=0;

        if (!flag_controlstream){
            ans1 = contour(frame, goal, result);
                switch(ans1){
                case 1:counter_obj++;counter_wawa++;break;
                case 2:counter_obj++;counter_wawa--;break;
                case -1:counter_obj--;cout<<"need little more closer"<<endl;break;
                case -2:counter_obj--;cout<<"missing target"<<endl;break;
                default:break;
                }

                if(counter_obj>3){
                    counter_obj=0;
                    flag_obj=1;
                    if(counter_wawa==10){
                        counter_wawa=0;
                        flag_wawa=1;
                        cout<<"octopus"<<endl;

                    }else
                        if(counter_wawa==-10){
                            counter_wawa=0;
                            flag_wawa=0;
                            cout<<"hippo"<<endl;
                        }
                        else{

                        }
                }
                else if(counter_obj<-10){
                    counter_obj=0;
                }

        }
        else{
            cout<<"waiting for a call"<<endl;
            flag_obj=0;
            flag_wawa=0;
            /*flag_controlstream=0;*/
        }


        //ans2 = orbmatching(frame, result);

//        if ((ans1 == 1) && (ans2 == 1)) cout << "octopus" << endl; else //zhangyu
//        if ((ans1 == 2) && (ans2 == 2)) cout << "hippo" << endl; else //hema



        //undistort the images
        //Mat image_undistorted;
        //imageCalibration(frame, image_undistorted);

        //if (Transformer::number < 2000) continue;


        imshow(OPENCV_WINDOW, frame);
        if (!result.data) continue;
        imshow(RESULT_WINDOW, result);
        waitKey(100);
    }

    return 0;
}

