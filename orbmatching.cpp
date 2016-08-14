#include "led/orbmatching.h"

int orbmatching(const Mat src,
                            Mat &result)
{
    Mat img_octopus = imread("/home/gogojjh/QT/led/data/octopus.jpg");
    Mat img_hippo = imread("/home/gogojjh/QT/led/data/hippo.jpg");
    /*resize(img_mode1,img_mode1,Size(img_mode1.cols/3,img_mode1.rows/3),0,0,CV_INTER_LINEAR);
    resize(img_mode2,img_mode2,Size(img_mode2.cols/3,img_mode2.rows/3),0,0,CV_INTER_LINEAR);
    resize(img_src,img_src,Size(img_src.cols/3,img_src.rows/3),0,0,CV_INTER_LINEAR);*/
    //img_src = img_src - Scalar(100,100,100);
    //waitKey(0);
    int n_octopus = objectrecognition(img_octopus, src, result);
    //int n_hippo = objectrecognition(img_hippo, src, result);
    int n_hippo = 0;
    if ( n_octopus > n_hippo )
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int objectrecognition(Mat img1, Mat img2, Mat &result)
{
    //img2.copyTo(result);
    int n = 0;
    ORB orb;
    vector<KeyPoint> keyPoints_1, keyPoints_2;
    Mat descriptors_1, descriptors_2;

    orb(img1, Mat(), keyPoints_1, descriptors_1);
    orb(img2, Mat(), keyPoints_2, descriptors_2);
    BruteForceMatcher<HammingLUT> matcher;
    vector<DMatch> matches;

    if (!descriptors_1.data) return 0;
    if (!descriptors_2.data) return 0;

    matcher.match(descriptors_1, descriptors_2, matches);

    double max_dist = 0;
    double min_dist = 70;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    //matching orb threshold:0.45*max_dist
    std::vector< DMatch > good_matches;
    for( int i = 0; i < descriptors_1.rows; i++ )
    {
        if( matches[i].distance < 0.6*max_dist )
        {
            good_matches.push_back( matches[i]);
            n++;
        }
    }
    cout << n << endl;

    //Mat result;
    drawMatches(img1, keyPoints_1, img2, keyPoints_2,
        good_matches, result, Scalar::all(-1), Scalar::all(-1),
        vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    //imshow("match",result);
    //waitKey(0);
    return n;
}

/*
RotatedRect SquareDetect::squareDet_4(Mat img)
{
    //split the channel
    vector<Mat> img_split;
    Mat img_single;
    split(img,img_split);
    img_single = img_split[2].clone();
    imshow("img_single",img_single);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    float maxContourArea = 0;
    int maxContourArea_index;

    Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
    morphologyEx(img_single,img_single,MORPH_CLOSE, element);
    imshow("img_single_close",img_single);
    threshold(img_single, img_single, 35, 255, THRESH_BINARY_INV );
    imshow("img_single_threshold",img_single);
    findContours(img_single, contours,hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    drawContours(img_single,contours,-1,Scalar(255),2);
    imshow("contours",img_single);
    // Find the max area of contours
    maxContourArea_index=0;
    for (int i=0;i<contours.size();i++){
        int contourSize = contourArea(contours[i]);
        if(contourSize > maxContourArea){
            maxContourArea = contourSize;
            maxContourArea_index = i;
        }
    }
    RotatedRect box;
    if(maxContourArea_index!=0){
         box = minAreaRect(contours[maxContourArea_index]);

    }
    return box;
}*/

/*
RotatedRect SquareDetect::squareDet_3(Mat img)
{
    vector<Mat> img_split;
    Mat img_single;
    split(img,img_split);
    img_single = img_split[2].clone();
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    float maxContourArea = 0;
    int maxContourArea_index;

    Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
    morphologyEx(img_single,img_single,MORPH_CLOSE, element);
    threshold(img_single, img_single, 0, 255, CV_THRESH_BINARY_INV + CV_THRESH_OTSU);// Use the OTSU algorithm
    imshow("img_single",img_single);
    findContours(img_single, contours,hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    // Find the max area of contours
    for (int i=0;i<contours.size();i++){
        int contourSize = contourArea(contours[i]);
        if(contourSize > maxContourArea){
            maxContourArea = contourSize;
            maxContourArea_index = i;
        }
    }
    RotatedRect box = minAreaRect(contours[maxContourArea_index]);
    return box;
}*/

/*
Mat dollDetect(Mat img, RotatedRect box)
{
    // Set ROI
    Mat mask(img.rows,img.cols,CV_8UC3,Scalar::all(0));
    Point2f vertex[4];
    box.points(vertex);
    vector<vector<Point>  > maskContours;
    vector<Point> ptr;
    for(int i=0;i<4;i++){
        ptr.push_back(Point(vertex[i].x,vertex[i].y));
    }
    maskContours.push_back(ptr);
    drawContours(mask,maskContours,0,Scalar::all(255),-1);
    Mat imgROI;
    img.copyTo(imgROI,mask);
    // convert to HSV
    Mat img_hsv_blue, img_hsv_red1,img_hsv_red2,img_hsv_yellow;
    cvtColor(imgROI, img_hsv_blue, CV_BGR2HSV);
    Mat img_threshold_blue, img_threshold_red, img_threshold_red1, img_threshold_red2, img_threshold_yellow;

    Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
    morphologyEx(img_hsv_blue,img_hsv_blue ,MORPH_OPEN,element,Point(-1,-1),3);
    morphologyEx(img_hsv_blue,img_hsv_blue ,MORPH_CLOSE,element,Point(-1,-1),3);
    img_hsv_red1   = img_hsv_blue.clone();
    img_hsv_red2   = img_hsv_blue.clone();
    img_hsv_yellow = img_hsv_blue.clone();

    Mat blue_low(Scalar(60,43,46));
    Mat blue_higher(Scalar(140,255,255));

    Mat red1_low(Scalar(0,43,46));
    Mat red1_higher(Scalar(3,255,255));

    Mat red2_low(Scalar(170,43,46));
    Mat red2_higher(Scalar(180,255,255));

    Mat yellow_low(Scalar(20,43,46));
    Mat yellow_higher(Scalar(34,255,255));

    inRange(img_hsv_blue,   blue_low,   blue_higher,   img_threshold_blue);
    inRange(img_hsv_red1,   red1_low,   red1_higher,   img_threshold_red1);
    inRange(img_hsv_red2,   red2_low,   red2_higher,   img_threshold_red2);
    inRange(img_hsv_yellow, yellow_low, yellow_higher, img_threshold_yellow);
    img_threshold_red = img_threshold_red1 | img_threshold_red2;

    imshow("123",img_threshold_red1);

    vector<vector<Point> > contours_blue, contours_red, contours_yellow;
    vector<Vec4i> hierarchy_blue, hierarchy_red, hierarchy_yellow;
    findContours(img_threshold_blue,   contours_blue,hierarchy_blue,     CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    findContours(img_threshold_red,    contours_red,hierarchy_red,       CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    findContours(img_threshold_yellow, contours_yellow,hierarchy_yellow, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
    // Find the max area of contours
    for (int i=0;i<contours_blue.size();i++){
        int contourSize = contourArea(contours_blue[i]);
        if(contourSize>6000){
            Rect box = boundingRect(contours_blue[i]);
            rectangle(img,box,Scalar(255,0,0),5);
        }
    }

    for (int i=0;i<contours_red.size();i++){
        int contourSize = contourArea(contours_red[i]);
        if(contourSize>10000){
            Rect box = boundingRect(contours_red[i]);
            rectangle(img,box,Scalar(0,0,255),5);
        }
    }

    for (int i=0;i<contours_yellow.size();i++){
        int contourSize = contourArea(contours_yellow[i]);
        if(contourSize>10000){
            Rect box = boundingRect(contours_yellow[i]);
            rectangle(img,box,Scalar(0,255,255),5);
        }
    }

    imshow("dst",img);
    return img;
}*/
