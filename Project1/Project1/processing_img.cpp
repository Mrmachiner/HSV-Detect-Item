#include "processing_img.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>       /* acos */

#define PI 3.14159265
const int max_value_H = 360 / 2;
const int max_value = 255;
const cv::String window_capture_name = "Video Capture";
const cv::String window_detection_name = "Object Detection";
const cv::String window_track_bar = "Object Detection";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;
static void on_low_H_thresh_trackbar(int, void*)
{
	low_H = cv::min(high_H - 1, low_H);
	cv::setTrackbarPos("Low H", window_track_bar, low_H);
}
static void on_high_H_thresh_trackbar(int, void*)
{
	high_H = cv::max(high_H, low_H + 1);
	cv::setTrackbarPos("High H", window_track_bar, high_H);
}
static void on_low_S_thresh_trackbar(int, void*)
{
	low_S = cv::min(high_S - 1, low_S);
	cv::setTrackbarPos("Low S", window_track_bar, low_S);
}
static void on_high_S_thresh_trackbar(int, void*)
{
	high_S = cv::max(high_S, low_S + 1);
	cv::setTrackbarPos("High S", window_track_bar, high_S);
}
static void on_low_V_thresh_trackbar(int, void*)
{
	low_V = cv::min(high_V - 1, low_V);
	cv::setTrackbarPos("Low V", window_track_bar, low_V);
}
static void on_high_V_thresh_trackbar(int, void*)
{
	high_V = cv::max(high_V, low_V + 1);
	cv::setTrackbarPos("High V", window_track_bar, high_V);
}
//q or esc quit, s Stop image 
void get_HSV_trackbar(std::string path) {
	cv::VideoCapture cap(path);
	cv::namedWindow(window_capture_name);
	cv::namedWindow(window_track_bar);
	cv::resizeWindow(window_track_bar, cv::Size(500, 400));
	cv::namedWindow(window_detection_name);

	/*cv::resizeWindow(window_capture_name, cv::Size(1080, 720));
	cv::resizeWindow(window_track_bar, cv::Size(500, 300));*/
	// Trackbars to set thresholds for HSV values
	cv::createTrackbar("Low H", window_track_bar, &low_H, max_value_H, on_low_H_thresh_trackbar);
	cv::createTrackbar("High H", window_track_bar, &high_H, max_value_H, on_high_H_thresh_trackbar);
	cv::createTrackbar("Low S", window_track_bar, &low_S, max_value, on_low_S_thresh_trackbar);
	cv::createTrackbar("High S", window_track_bar, &high_S, max_value, on_high_S_thresh_trackbar);
	cv::createTrackbar("Low V", window_track_bar, &low_V, max_value, on_low_V_thresh_trackbar);
	cv::createTrackbar("High V", window_track_bar, &high_V, max_value, on_high_V_thresh_trackbar);
	cv::Mat frame, frame_HSV, frame_threshold;
	while (true) {
		cap >> frame;
		cv::Mat clone = frame.clone();
		if (frame.empty())
		{
			break;
		}
		// Convert from BGR to HSV colorspace
		cvtColor(frame, frame_HSV, cv::COLOR_BGR2HSV);
		// Detect the object based on HSV Range Values
		inRange(frame_HSV, cv::Scalar(low_H, low_S, low_V), cv::Scalar(high_H, high_S, high_V), frame_threshold);
		cv::Mat element_dilate = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7), cv::Point(-1, -1)); //cv::Size(7, 7)
		cv::Mat element_Erosion = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
		// cv::morphologyEx(obj1_mask,obj1_mask,cv::MORPH_OPEN,element_dilate);

		// cv::morphologyEx(obj1_mask,obj1_mask,cv::MORPH_CLOSE,element_dilate);

		cv::dilate(frame_threshold, frame_threshold, element_dilate, cv::Point(-1, -1));

		cv::erode(frame_threshold, frame_threshold, element_Erosion, cv::Point(-1, -1));
		// Show the frames
		cv::resize(frame, frame, cv::Size(frame.size().width / 2, frame.size().height / 2));
		cv::resize(frame_threshold, frame_threshold, cv::Size(frame_threshold.size().width / 2, frame_threshold.size().height / 2));
		imshow(window_capture_name, frame);
		imshow("abcd", frame_threshold);

		char key = (char)cv::waitKey(30);
		if (key == 'q' || key == 27)
		{
			break;
		}
		if (key == 's') {
			while (true)
			{
				cvtColor(frame, frame_HSV, cv::COLOR_BGR2HSV);
				// Detect the object based on HSV Range Values
				inRange(frame_HSV, cv::Scalar(low_H, low_S, low_V), cv::Scalar(high_H, high_S, high_V), frame_threshold);
				cv::Mat element_dilate = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7), cv::Point(-1, -1)); //cv::Size(7, 7)
				cv::Mat element_Erosion = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
				// cv::morphologyEx(obj1_mask,obj1_mask,cv::MORPH_OPEN,element_dilate);


				// cv::morphologyEx(obj1_mask,obj1_mask,cv::MORPH_CLOSE,element_dilate);

				cv::dilate(frame_threshold, frame_threshold, element_dilate, cv::Point(-1, -1));

				cv::erode(frame_threshold, frame_threshold, element_Erosion, cv::Point(-1, -1));
				// Show the frames
				imshow(window_capture_name, frame);
				imshow("abcd", frame_threshold);
				char key = (char)cv::waitKey(1);
				if (key == 'q' || key == 27)
				{
					break;
				}
			}
		}
	}
}
std::vector<cv::Point> Xcompare(std::vector<cv::Point> topPoint, std::vector<cv::Point> botPoint)
{
	std::vector<cv::Point> _pts(4);
	if (topPoint[0].x < topPoint[1].x)
	{
		_pts[0] = topPoint[0];
		_pts[3] = topPoint[1];
	}
	else
	{
		_pts[0] = topPoint[1];
		_pts[3] = topPoint[0];
	}
	if (botPoint[0].x < botPoint[1].x)
	{
		_pts[1] = botPoint[0];
		_pts[2] = botPoint[1];
	}
	else
	{
		_pts[1] = botPoint[1];
		_pts[2] = botPoint[0];
	}
	return _pts;
}
std::vector<cv::Point> SortPoint(std::vector<cv::Point> points)
{
	cv::Point sw;
	std::vector<cv::Point> _pts(4);
	std::vector<cv::Point> _topPoint(2);
	std::vector<cv::Point> _botPoint(2);
	for (int i = 0; i < points.size() - 1; i++)
	{
		for (int j = i + 1; j < points.size(); j++)
		{
			if (points[i].y < points[j].y)
			{
				sw = points[i];
				points[i] = points[j];
				points[j] = sw;
			}
		}
	}
	_topPoint[0] = points[0];
	_topPoint[1] = points[1];
	_botPoint[0] = points[2];
	_botPoint[1] = points[3];
	_pts = Xcompare(_topPoint, _botPoint);
	return _pts;
}
cv::Mat original_to_hsv_blackblu(cv::Mat original, cv::Scalar low_obj1, cv::Scalar hight_obj1)
{
	// Video 1 green_blu Hmin (62, 0 ,0) , (153,255,255)

	// Black  np.array([0, 0, 0]), np.array([179, 68, 86]))  item image1,2

	// Blu  np.array([86, 23, 60]), np.array([179, 255, 255])) item image1,2

	// Green  np.array([94, 255, 255]), np.array([18, 30, 255])) item image1,2

	// Item pink Hmin = 7   Smin=Vmin=0 Hmax=179 Smax=Vmax=255 
	// Black in Item pink Hmin=0=Smin Vmin=116 Hmax=179 Smax=Vmax=255
	cv::Mat hsv_origi;
	cv::cvtColor(original, hsv_origi, cv::COLOR_BGR2HSV);

	cv::Mat obj1_mask, mask_obj;

	cv::inRange(hsv_origi, low_obj1, hight_obj1, obj1_mask);



	cv::Mat element_dilate = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7), cv::Point(-1, -1)); //cv::Size(7, 7)
	cv::Mat element_Erosion = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(-1, -1));
	// cv::morphologyEx(obj1_mask,obj1_mask,cv::MORPH_OPEN,element_dilate);


	// cv::morphologyEx(obj1_mask,obj1_mask,cv::MORPH_CLOSE,element_dilate);

	cv::dilate(obj1_mask, obj1_mask, element_dilate, cv::Point(-1, -1));

	cv::erode(obj1_mask, obj1_mask, element_Erosion, cv::Point(-1, -1));

	//cv::add(obj1_mask, obj2_mask, mask_obj, cv::noArray(), 8 );
	return obj1_mask;
}

std::vector<std::vector<cv::Point>> findContours_Hull(cv::Mat mask, bool marker )
{
	// marker = false detec object
	// marker = true detec marker

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	std::vector<cv::Point> approx;
	cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));


	std::vector<std::vector<cv::Point>> contours_obj;
	for (int i = 0; i < contours.size(); i++)
	{
		if (marker)
		{
			double perimeter = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], approx, 0.055 * perimeter, true);
			double area = cv::contourArea(contours[i]);
			bool ok = false;
			ok = approx.size() == 4 && area > 130 && area < 300;
			if (ok)
			{
				contours_obj.push_back(approx);
			}
		}
		else
		{
			double area = cv::contourArea(contours[i]);
			if (area > 2000 && area < 14000)
			{
				contours_obj.push_back(contours[i]);
			}
		}
	}
	if (marker)
	{
		return contours_obj;
	}
	else
	{
		std::vector<std::vector<cv::Point>> contour_hull_obj(contours_obj.size());
		for (int i = 0; i < contours_obj.size(); i++)
		{
			cv::convexHull(cv::Mat(contours_obj[i]), contour_hull_obj[i], false);
		}
		return contour_hull_obj;
	}

}

std::vector<cv::Point> lst_Point_center(std::vector<std::vector<cv::Point>> contuours_hull_blackblu)
{
	std::vector<cv::Point> lst_Point;
	for (int i = 0; i < contuours_hull_blackblu.size(); i++)
	{
		cv::Point c1;
		for (int j = 0; j < contuours_hull_blackblu[i].size(); j++)
		{
			c1.x += contuours_hull_blackblu[i][j].x;
			c1.y += contuours_hull_blackblu[i][j].y;
		}
		c1.x = c1.x / contuours_hull_blackblu[i].size() * 1.0;
		c1.y = c1.y / contuours_hull_blackblu[i].size() * 1.0;
		lst_Point.push_back(c1);
	}
	return lst_Point;
}
cv::Mat draw_Detection_obj(cv::Mat original, std::vector<std::vector<cv::Point>> contuours_hull_blackblu, std::vector<cv::Point> lst_Point, std::vector<float> lst_angle, std::vector<std::string> name_obj)
{
	cv::Mat real;
	cv::Point top;
	cv::Point left;
	if (!contuours_hull_blackblu.empty()) 
	{
		for (int i = 0; i < contuours_hull_blackblu.size(); i++)
		{
			cv::Mat mask = cv::Mat::zeros(original.size(), CV_8UC3);
			cv::Mat mask_obj = cv::Mat::zeros(original.size(), CV_8UC3);
			std::string str_angle = " ";
			float angle1 = -0.001;
			if (!lst_angle.empty())
			{
				try {
					angle1 = lst_angle[i];
				}
				catch (const std::out_of_range& oor) {
					std::cerr << "out of range error" << oor.what() <<'\n';
				}
			}
			float radian = angle1 * PI / 180;
			left.x = lst_Point[i].x + 100;
			left.y = lst_Point[i].y;

			top.y = lst_Point[i].y - 100 * sin(radian);
			top.x = lst_Point[i].x + 100 * cos(radian);
			str_angle = std::to_string(angle1) + "o";
			cv::line(mask, lst_Point[i], top, cv::Scalar(255, 0, 255), 2);

			cv::line(mask, lst_Point[i], left, cv::Scalar(255, 0, 255), 2);

			std::string txt_center = name_obj[i] + "(" + std::to_string(lst_Point[i].x) + "," + std::to_string(lst_Point[i].y) + ")" + str_angle;
			cv::putText(mask, txt_center, lst_Point[i], cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 0.5, cv::Scalar(255, 255, 0), 1, 8);
			cv::circle(mask, lst_Point[i], 1, cv::Scalar(0, 255, 0), 1, 8, 0);
			//cv::drawContours(mask,black_contours,i,cv::Scalar(0,255,0),1,8,std::vector<cv::Vec4i>(), 0, cv::Point());
			cv::drawContours(mask, contuours_hull_blackblu, i, cv::Scalar(0, 255, 0), 4, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
			cv::drawContours(mask_obj, contuours_hull_blackblu, i, cv::Scalar(0, 0, 0), -1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
			mask_obj.copyTo(original, mask);
		}
	}
	return original;
}
int range(cv::Point p1, cv::Point p2)
{
	int x01 = pow((p1.x - p2.x), 2);
	int y01 = pow((p1.y - p2.y), 2);
	int A01 = int(sqrt(x01 + y01));
	return A01;
}
cv::Point midpoint(cv::Point p1, cv::Point p2)
{
	cv::Point m;
	m.x = abs(int((p1.x + p2.x) / 2));
	m.y = abs(int((p1.y + p2.y) / 2));
	return m;
}
float calulator_angle(cv::Point A, cv::Point B)
{
	cv::Point AB, CD(1, 0), D;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;
	float lenAB = AB.x * AB.x + AB.y * AB.y;
	float lenCD = CD.x * CD.x + CD.y * CD.y;
	float angle = (AB.x * CD.x + AB.y * CD.y) / (sqrt(lenAB) * sqrt(lenCD)) * 1.0;
	if (AB.y > 0)
	{
		angle = 360 - (acos(angle) * 180.0 / PI);
	}
	else
	{
		angle = (acos(angle) * 180.0 / PI);
	}

	return angle;
}
std::vector<cv::Mat>lst_img_marker_in_item(cv::Mat img, std::vector<std::vector<cv::Point>> contounrs_hull_item, std::vector<std::string> &name_obj)
{
	std::vector<cv::Mat> lst_marker_in_item;
	std::vector<cv::Rect> boundRect(contounrs_hull_item.size());
	std::vector<std::vector<cv::Point> > contours_poly(contounrs_hull_item.size());
	for (int i = 0; i < contounrs_hull_item.size(); i++)
	{
		cv::approxPolyDP(contounrs_hull_item[i], contours_poly[i], 3, true);
		boundRect[i] = cv::boundingRect(contours_poly[i]);

		//cv::rectangle(img, boundRect[i], cv::Scalar(255,0,255),2);
		cv::Mat img_item = img(boundRect[i]);
		int area = img_item.size().width * img_item.size().height;
		if (area > 3000 && area < 5000)
		{
			name_obj.push_back("object nho");
		}
		else if (area > 10000 && area < 14000)
		{
			name_obj.push_back("object to");
		}
		else
		{
			name_obj.push_back("none");
		}
		lst_marker_in_item.push_back(img_item);
	}
	return lst_marker_in_item;
}
//int main(int argc, char* argv[])
//{
	////VideoCapture cap(argc > 1 ? atoi(argv[1]) : 0); //C:\Users\T450s\Downloads
	//cv::String path = "C:\\Users\\T450s\\Downloads\\item.mp4";
	//get_HSV_trackbar(path);
	//return 0;
//	cv::VideoCapture cap("./Image/item_pink.mp4");
//	// cv::Scalar low(62, 0 ,0);
//	// cv::Scalar hight(153,255,255);  
//	cv::Scalar objlow_pink(0, 97, 0); //0, 84 ,0
//	cv::Scalar objhight_pink(179, 255, 255);
//
//	cv::Scalar objlow_black(0, 146, 0); // 8, 122 ,0
//	cv::Scalar objhight_black(179, 255, 255);
//	cv::Mat frame;
//	int i = 1;
//	while (1)
//	{
//		bool s = cap.read(frame);
//		cv::Mat img = frame.clone();
//		//cv::imwrite("/home/minhhoang/Desktop/Item_Tracking/Image/abcd"+ std::to_string(i) + ".jpg",img);
//		i++;
//		if (!s) {
//			break;
//		}
//		try
//		{
//			std::vector<std::string> name_obj;
//			cv::Mat mask_pink_item = original_to_hsv_blackblu(img, objlow_pink, objhight_pink);
//
//			//find Contour item
//			std::vector<std::vector<cv::Point>> contounrs_hull_item = findContours_Hull(mask_pink_item, false);
//
//			//Poin center
//			std::vector<cv::Point> lst_Point_C_item = lst_Point_center(contounrs_hull_item);
//
//			//Crop image contain item
//			std::vector<cv::Rect> boundRect(contounrs_hull_item.size());
//
//			std::vector<std::vector<cv::Point> > contours_poly(contounrs_hull_item.size());
//
//			std::vector<cv::Mat> lst_marker_in_item;
//			for (int i = 0; i < contounrs_hull_item.size(); i++)
//			{
//
//				cv::approxPolyDP(contounrs_hull_item[i], contours_poly[i], 3, true);
//				boundRect[i] = cv::boundingRect(contours_poly[i]);
//
//				//cv::rectangle(img, boundRect[i], cv::Scalar(255,0,255),2);
//				cv::Mat img_item = img(boundRect[i]);
//				int area = img_item.size().width * img_item.size().height;
//				if (area > 3000 && area < 5000)
//				{
//					name_obj.push_back("object nho");
//				}
//				else if (area > 10000 && area < 14000)
//				{
//					name_obj.push_back("object to");
//				}
//				else
//				{
//					name_obj.push_back(" ");
//				}
//
//				lst_marker_in_item.push_back(img_item);
//			}
//			//angle
//			std::vector<float> lst_angle;
//			cv::Point A, B, AB;
//
//			for (int i = 0; i < lst_marker_in_item.size(); i++)
//			{
//				float ratiox = 0.1;
//				float ratioy = 0.1;
//				cv::Point center_item;
//				ratiox = boundRect[i].width * 1.0 / img.size().width * 1.0;
//				ratioy = boundRect[i].height * 1.0 / img.size().height * 1.0;
//				center_item.x = int(ratiox * lst_Point_C_item[i].x * 1.0);
//
//				center_item.y = int(ratioy * lst_Point_C_item[i].y * 1.0);
//
//				cv::Mat mask_obj = cv::Mat::zeros(lst_marker_in_item[i].size(), CV_8UC3);
//				cv::Mat mask_black_marker = original_to_hsv_blackblu(lst_marker_in_item[i], objlow_black, objhight_black);
//
//				//find Contour marker
//				std::vector<std::vector<cv::Point>> contounrs_hull_marker = findContours_Hull(mask_black_marker, true);
//				if (!contounrs_hull_marker.empty())
//				{
//					contounrs_hull_marker[0] = SortPoint(contounrs_hull_marker[0]);
//					// calulator 0 1 vs 0 3
//					int A01 = range(contounrs_hull_marker[0][0], contounrs_hull_marker[0][1]);
//
//					int A03 = range(contounrs_hull_marker[0][0], contounrs_hull_marker[0][3]);
//
//					if (A01 > A03)
//					{
//						A = midpoint(contounrs_hull_marker[0][3], contounrs_hull_marker[0][0]);
//
//						B = midpoint(contounrs_hull_marker[0][2], contounrs_hull_marker[0][1]);
//					}
//					else
//					{
//						A = midpoint(contounrs_hull_marker[0][1], contounrs_hull_marker[0][0]);
//
//						B = midpoint(contounrs_hull_marker[0][2], contounrs_hull_marker[0][3]);
//					}
//					lst_angle.push_back(calulator_angle(A, B));
//				}
//			}
//			cv::Mat Obj_original = draw_Detection_obj(img, contounrs_hull_item, lst_Point_C_item, lst_angle, name_obj);
//			cv::imshow("mask", Obj_original);
//			cv::waitKey(40);
//		}
//		catch (const std::exception & e)
//		{
//			std::cerr << e.what() << '\n';
//		}
//	}
//	// cv::Mat img = cv::imread("./Image/abcd87.jpg"); //87 102 199
//
//
//
//	// // 2 image have item and marker
//	// cv::Mat mask_pink_item = original_to_hsv_blackblu(img, objlow_pink, objhight_pink);
//
//	// //find Contour item
//	// std::vector<std::vector<cv::Point>> contounrs_hull_item = findContours_Hull(mask_pink_item, false);
//
//	// //Poin center
//	// std::vector<cv::Point> lst_Point_C_item = lst_Point_center(contounrs_hull_item);
//
//	// //Crop image contain item
//	// std::vector<cv::Rect> boundRect(contounrs_hull_item.size());
//
//	// std::vector<std::vector<cv::Point> > contours_poly( contounrs_hull_item.size() );
//
//	// std::vector<cv::Mat> lst_marker_in_item;
//	// std::vector<std::string> name_obj;
//	// for (int i = 0; i < contounrs_hull_item.size(); i++)
//	// {
//	//     cv::approxPolyDP( contounrs_hull_item[i], contours_poly[i], 3, true );
//	//     boundRect[i] = cv::boundingRect(contours_poly[i]);
//
//	//     //cv::rectangle(img, boundRect[i], cv::Scalar(255,0,255),2);
//	//     cv::Mat img_item  = img(boundRect[i]);
//	//     int area = img_item.size().width * img_item.size().height;
//	//     if(area > 3000 && area < 5000)
//	//     {
//	//         name_obj.push_back("Object Nho");
//	//     }
//	//     else if( area > 10000 && area <14000)
//	//     {
//	//         name_obj.push_back("Object To");
//	//     }
//	//     lst_marker_in_item.push_back(img_item);
//	// }
//	// //angle
//	// std::vector<float> lst_angle;
//	// for(int i = 0; i < lst_marker_in_item.size(); i++)
//	// {
//	//     cv::Point center_item;
//	//     center_item.x = int((boundRect[i].width * 1.0/img.size().width * 1.0)*lst_Point_C_item[i].x);
//
//	//     center_item.y = int((boundRect[i].height * 1.0/img.size().height * 1.0)*lst_Point_C_item[i].y);
//
//	//     cv::Mat mask_obj = cv::Mat::zeros(lst_marker_in_item[i].size(),CV_8UC3);
//	//     cv::Mat mask_black_marker = original_to_hsv_blackblu(lst_marker_in_item[i], objlow_black, objhight_black);
//
//	//     cv::imshow("mask_black_marker", mask_black_marker);
//	//     cv::waitKey();
//	//     //find Contour marker
//	//     std::vector<std::vector<cv::Point>> contounrs_hull_marker = findContours_Hull(mask_black_marker, true);
//	//     contounrs_hull_marker[0] = SortPoint(contounrs_hull_marker[0]);
//	//     //Center marker
//	//     //std::vector<cv::Point> lst_Point_C_marker = lst_Point_center(contounrs_hull_marker);
//
//	//     cv::Point A, B, AB,D, CD;
//
//	//     // calulator 0 1 vs 0 3
//	//     int A01 = range(contounrs_hull_marker[0][0],contounrs_hull_marker[0][1]);
//
//	//     int A03 = range(contounrs_hull_marker[0][0],contounrs_hull_marker[0][3]);
//
//	//     if(A01>A03)
//	//     {
//	//         A = midpoint(contounrs_hull_marker[0][3],contounrs_hull_marker[0][0]);
//
//	//         B = midpoint(contounrs_hull_marker[0][2],contounrs_hull_marker[0][1]);
//	//     }
//	//     else
//	//     {
//	//         A = midpoint(contounrs_hull_marker[0][1],contounrs_hull_marker[0][0]);
//
//	//         B = midpoint(contounrs_hull_marker[0][2],contounrs_hull_marker[0][3]);
//	//     }
//	//     //lst_angle.push_back(calulator_angle(A, B));
//	//     int R_center_item_A = range(center_item, A);
//	//     int R_center_item_B = range(center_item, B);
//
//	//     if(R_center_item_A > R_center_item_B)
//	//     {
//	//         lst_angle.push_back(calulator_angle(B, A));
//	//     }
//	//     else
//	//     {
//	//         lst_angle.push_back(calulator_angle(A, B));
//	//     }
//	// }
//	// cv::Mat Obj_original = draw_Detection_obj(img, contounrs_hull_item, lst_Point_C_item, lst_angle, name_obj);
//	// cv::namedWindow("Obj_original",cv::WINDOW_NORMAL);
//	// cv::resizeWindow("Obj_original", 1706,1280);
//	// cv::imshow("Obj_original", Obj_original);
//	// cv::waitKey(0);
//	return 0;
//}