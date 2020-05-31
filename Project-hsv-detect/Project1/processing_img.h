#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>  /* acos */

#define PI 3.14159265

std::vector<cv::Point> Xcompare(std::vector<cv::Point> topPoint, std::vector<cv::Point> botPoint);
std::vector<cv::Point> SortPoint(std::vector<cv::Point> points);
cv::Mat original_to_hsv_blackblu(cv::Mat original, cv::Scalar low_obj1, cv::Scalar hight_obj1);

std::vector<std::vector<cv::Point>> findContours_Hull(cv::Mat mask, bool marker = false);

std::vector<cv::Point> lst_Point_center(std::vector<std::vector<cv::Point>> contuours_hull_blackblu);
cv::Mat draw_Detection_obj(cv::Mat original, std::vector<std::vector<cv::Point>> contuours_hull_blackblu, std::vector<cv::Point> lst_Point, std::vector<float> lst_angle, std::vector<std::string> name_obj);
int range(cv::Point p1, cv::Point p2);
cv::Point midpoint(cv::Point p1, cv::Point p2);
float calulator_angle(cv::Point A, cv::Point B);
std::vector<cv::Mat>lst_img_marker_in_item(cv::Mat img, std::vector<std::vector<cv::Point>> contounrs_hull_item, std::vector<std::string>& name_obj);
void get_HSV_trackbar(std::string path);
//int main(int argc, char* argv[])
//{
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

