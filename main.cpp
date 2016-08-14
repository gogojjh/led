#include "led/base.h"
#include "led/contour.h"
#include "led/orbmatching.h"

static const std::string OPENCV_WINDOW = "Image window";
static const std::string RESULT_WINDOW = "Result window";
int number = 0;

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

        frame = imread("/home/gogojjh/QT/led/data/1116.jpg", 1);
        resize(frame, frame, Size(frame.cols/IMAGE_SIZE_COL, frame.rows/IMAGE_SIZE_ROW));
        int ans1=0, ans2=0;
        ans1 = contour(frame, goal, result);
        //ans2 = orbmatching(frame, result);

        if ((ans1 == 1) && (ans2 == 1)) cout << "octopus" << endl; else //zhangyu
        if ((ans1 == 2) && (ans2 == 2)) cout << "hippo" << endl; else //hema
        if (ans1 == -1) cout << "need little more colser" << endl; else
        if (ans1 == -2) cout << "missing WAWA" << endl;

        //undistort the images
        //Mat image_undistorted;
        //imageCalibration(frame, image_undistorted);

        //if (Transformer::number < 2000) continue;

        /*
        cout<<"distance:"<<distance<<endl;
        cout<<"F1111111:::::::"<<countF1<<endl;
        cout<<"F2222222:::::::"<<countF2<<endl;
        int ACK=3;
        int thresholdD=20;

        if (find_object&countF1<3)    countF1++;
        else
        {
            if(!find_object)
            {
                countF1 = 0;
                cout<<"missing target"<<endl;
                Transformer::gridfourdetect_threshold  = 66;
            }
        }
        if (countF1 == ACK)
        {
            cout << "***********object_targeted**********" << endl;
            Transformer::gridfourdetect_threshold  = 80;
            if(distance<thresholdD)
            {
                countF2++;
            }
            else
                countF2=0;
            if(countF2==ACK)
            {
                cout<<"///////////////////I wanna drop WAWA/////////////////"<<endl;
                countF2=0;
                countF1=0;
                Transformer::gridfourdetect_threshold = 66;
            }
            */
            /*
            cout << "Goal: " << goal << endl;
            cout << "Distance: " << distance << endl;
            cout << "Find Object: " << find_object << endl;
            */
            /*
            if (Transformer::number % 1 == 0)
            {
                char saveFileName[50];
                sprintf(saveFileName, "/home/gogojjh/QT/mapRecognition/image2/Origin%d.jpg", Transformer::number);
                imwrite(saveFileName, frame);
                sprintf(saveFileName, "/home/gogojjh/QT/mapRecognition/image2/Result%d.jpg", Transformer::number);
                imwrite(saveFileName, trans.gImage((2)));
            }*/
        //}
        imshow(OPENCV_WINDOW, frame);
        if (!result.data) continue;
        imshow(RESULT_WINDOW, result);
        waitKey(100);
    }

    return 0;
}
















