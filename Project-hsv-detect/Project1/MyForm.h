#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "processing_img.h"
#include <msclr\marshal_cppstd.h>

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}







	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;


	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ btnTrackBar;
	private: System::Windows::Forms::Button^ btnDetection;












	private: System::Windows::Forms::TextBox^ txtPath;


	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ btnOpenFile;



	private: System::Windows::Forms::TextBox^ txtX_objecTo;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtY_objecTo;
	private: System::Windows::Forms::TextBox^ txtA_objecTo;
	private: System::Windows::Forms::TextBox^ txtX_objecNho;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ txtY_objecNho;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ txtA_objecNho;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ btnSetHSV;


	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->btnTrackBar = (gcnew System::Windows::Forms::Button());
			this->btnDetection = (gcnew System::Windows::Forms::Button());
			this->txtPath = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtX_objecTo = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->txtY_objecTo = (gcnew System::Windows::Forms::TextBox());
			this->txtA_objecNho = (gcnew System::Windows::Forms::TextBox());
			this->txtA_objecTo = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->txtX_objecNho = (gcnew System::Windows::Forms::TextBox());
			this->txtY_objecNho = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->btnOpenFile = (gcnew System::Windows::Forms::Button());
			this->btnSetHSV = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(96, 43);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(17, 17);
			this->label3->TabIndex = 6;
			this->label3->Text = L"X";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(146, 43);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(17, 17);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Y";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(196, 43);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(44, 17);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Angle";
			// 
			// btnTrackBar
			// 
			this->btnTrackBar->Location = System::Drawing::Point(92, 261);
			this->btnTrackBar->Name = L"btnTrackBar";
			this->btnTrackBar->Size = System::Drawing::Size(99, 59);
			this->btnTrackBar->TabIndex = 17;
			this->btnTrackBar->Text = L"Track Bar Detection";
			this->btnTrackBar->UseVisualStyleBackColor = true;
			this->btnTrackBar->Click += gcnew System::EventHandler(this, &MyForm::btnTrackBar_Click);
			// 
			// btnDetection
			// 
			this->btnDetection->Location = System::Drawing::Point(258, 84);
			this->btnDetection->Name = L"btnDetection";
			this->btnDetection->Size = System::Drawing::Size(85, 38);
			this->btnDetection->TabIndex = 18;
			this->btnDetection->Text = L"Detection";
			this->btnDetection->UseVisualStyleBackColor = true;
			this->btnDetection->Click += gcnew System::EventHandler(this, &MyForm::btnDetect_Click);
			// 
			// txtPath
			// 
			this->txtPath->Location = System::Drawing::Point(16, 20);
			this->txtPath->Name = L"txtPath";
			this->txtPath->ReadOnly = true;
			this->txtPath->Size = System::Drawing::Size(272, 22);
			this->txtPath->TabIndex = 19;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtX_objecTo);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->btnDetection);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->txtY_objecTo);
			this->groupBox1->Controls->Add(this->txtA_objecNho);
			this->groupBox1->Controls->Add(this->txtA_objecTo);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->txtX_objecNho);
			this->groupBox1->Controls->Add(this->txtY_objecNho);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Location = System::Drawing::Point(16, 78);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(363, 177);
			this->groupBox1->TabIndex = 20;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Info Item";
			// 
			// txtX_objecTo
			// 
			this->txtX_objecTo->Location = System::Drawing::Point(99, 63);
			this->txtX_objecTo->Name = L"txtX_objecTo";
			this->txtX_objecTo->ReadOnly = true;
			this->txtX_objecTo->Size = System::Drawing::Size(44, 22);
			this->txtX_objecTo->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(14, 61);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 17);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Object To";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(11, 116);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(79, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Object Nho";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(196, 95);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(44, 17);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Angle";
			// 
			// txtY_objecTo
			// 
			this->txtY_objecTo->Location = System::Drawing::Point(149, 63);
			this->txtY_objecTo->Name = L"txtY_objecTo";
			this->txtY_objecTo->ReadOnly = true;
			this->txtY_objecTo->Size = System::Drawing::Size(44, 22);
			this->txtY_objecTo->TabIndex = 7;
			// 
			// txtA_objecNho
			// 
			this->txtA_objecNho->Location = System::Drawing::Point(199, 115);
			this->txtA_objecNho->Name = L"txtA_objecNho";
			this->txtA_objecNho->ReadOnly = true;
			this->txtA_objecNho->Size = System::Drawing::Size(44, 22);
			this->txtA_objecNho->TabIndex = 15;
			// 
			// txtA_objecTo
			// 
			this->txtA_objecTo->Location = System::Drawing::Point(199, 63);
			this->txtA_objecTo->Name = L"txtA_objecTo";
			this->txtA_objecTo->ReadOnly = true;
			this->txtA_objecTo->Size = System::Drawing::Size(44, 22);
			this->txtA_objecTo->TabIndex = 9;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(146, 95);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(17, 17);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Y";
			// 
			// txtX_objecNho
			// 
			this->txtX_objecNho->Location = System::Drawing::Point(99, 115);
			this->txtX_objecNho->Name = L"txtX_objecNho";
			this->txtX_objecNho->ReadOnly = true;
			this->txtX_objecNho->Size = System::Drawing::Size(44, 22);
			this->txtX_objecNho->TabIndex = 11;
			// 
			// txtY_objecNho
			// 
			this->txtY_objecNho->Location = System::Drawing::Point(149, 115);
			this->txtY_objecNho->Name = L"txtY_objecNho";
			this->txtY_objecNho->ReadOnly = true;
			this->txtY_objecNho->Size = System::Drawing::Size(44, 22);
			this->txtY_objecNho->TabIndex = 13;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(96, 95);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(17, 17);
			this->label8->TabIndex = 12;
			this->label8->Text = L"X";
			// 
			// btnOpenFile
			// 
			this->btnOpenFile->Location = System::Drawing::Point(295, 12);
			this->btnOpenFile->Name = L"btnOpenFile";
			this->btnOpenFile->Size = System::Drawing::Size(85, 38);
			this->btnOpenFile->TabIndex = 0;
			this->btnOpenFile->Text = L"Open File";
			this->btnOpenFile->UseVisualStyleBackColor = true;
			this->btnOpenFile->Click += gcnew System::EventHandler(this, &MyForm::btnOpenFile_Click);
			// 
			// btnSetHSV
			// 
			this->btnSetHSV->Location = System::Drawing::Point(215, 261);
			this->btnSetHSV->Name = L"btnSetHSV";
			this->btnSetHSV->Size = System::Drawing::Size(99, 59);
			this->btnSetHSV->TabIndex = 21;
			this->btnSetHSV->Text = L"Set Para HSV";
			this->btnSetHSV->UseVisualStyleBackColor = true;
			this->btnSetHSV->Click += gcnew System::EventHandler(this, &MyForm::btnSetHSV_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(392, 360);
			this->Controls->Add(this->btnSetHSV);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnOpenFile);
			this->Controls->Add(this->txtPath);
			this->Controls->Add(this->btnTrackBar);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void add_info(std::vector<std::vector<cv::Point>> contuours_hull_blackblu, std::vector<cv::Point> lst_Point_C_item, std::vector<float> lst_angle, std::vector<std::string> name_obj)
		{
			txtA_objecNho->Text = " ";

			txtX_objecNho->Text = " ";

			txtY_objecNho->Text = " ";
			txtA_objecTo->Text = " ";
			txtX_objecTo->Text = " ";
			txtY_objecTo->Text = " ";
			for (int i = 0; i < name_obj.size(); i++)
			{
				String^ Angle = msclr::interop::marshal_as<String^>(std::to_string(lst_angle[i]));

				String^ X = msclr::interop::marshal_as<String^>(std::to_string(lst_Point_C_item[i].x));

				String^ Y = msclr::interop::marshal_as<String^>(std::to_string(lst_Point_C_item[i].y));
				if (name_obj[i] == "object nho")
				{

					txtA_objecNho->Text = Angle;

					txtX_objecNho->Text = X;

					txtY_objecNho->Text = Y;
				}
				else if (name_obj[i] == "object to")
				{
					txtA_objecTo->Text = Angle;
					txtX_objecTo->Text = X;
					txtY_objecTo->Text = Y;
				}
			}
		}
	private: System::Void btnOpenFile_Click(System::Object^ sender, System::EventArgs^ e) {

		OpenFileDialog^ openFilediallog1 = gcnew OpenFileDialog;
		openFilediallog1->ShowDialog();
		String^ strFilename = openFilediallog1->FileName;
		txtPath->Text = strFilename;
		
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void btnDetect_Click(System::Object^ sender, System::EventArgs^ e) {

	if (txtPath->Text->Length != 0)
	{
		std::string unmanaged = msclr::interop::marshal_as<std::string>(txtPath->Text);
		cv::VideoCapture cap(unmanaged);

		cv::Scalar objlow_pink(62, 0, 0); //0, 84 ,0 //(0, 97, 0);
		cv::Scalar objhight_pink(153, 255, 255); // (179, 255, 255)

		cv::Scalar objlow_black(62, 0, 0); // 8, 122 ,0 //(0, 146, 0);
		cv::Scalar objhight_black(153, 255, 255); // (179, 255, 255);
		cv::Mat frame;
		while (1)
		{
			bool s = cap.read(frame);
			cv::Mat img = frame.clone();
			//cv::imwrite("/home/minhhoang/Desktop/Item_Tracking/Image/abcd"+ std::to_string(i) + ".jpg",img);
			if (!s) {
				break;
			}
			try
			{
				std::vector<std::string> name_obj;
				cv::Mat mask_pink_item = original_to_hsv_blackblu(img, objlow_pink, objhight_pink);

				//find Contour item
				std::vector<std::vector<cv::Point>> contounrs_hull_item = findContours_Hull(mask_pink_item, false);

				//Poin center
				std::vector<cv::Point> lst_Point_C_item = lst_Point_center(contounrs_hull_item);

				//Crop image contain item


				std::vector<cv::Mat> lst_marker_in_item = lst_img_marker_in_item(img, contounrs_hull_item, name_obj);
				//angle

				cv::Point A, B, AB;
				std::vector<float> lst_angle(name_obj.size());
				for (int i = 0; i < lst_marker_in_item.size(); i++)
				{
					/*if (lst_Point_C_item[i].x == 34 && lst_Point_C_item[i].y == 388)
					{
						cv::waitKey();
					}*/

					cv::Mat mask_obj = cv::Mat::zeros(lst_marker_in_item[i].size(), CV_8UC3);
					cv::Mat mask_black_marker = original_to_hsv_blackblu(lst_marker_in_item[i], objlow_black, objhight_black);

					//find Contour marker
					std::vector<std::vector<cv::Point>> contounrs_hull_marker = findContours_Hull(mask_black_marker, true);
					if (!contounrs_hull_marker.empty())
					{
						contounrs_hull_marker[0] = SortPoint(contounrs_hull_marker[0]);
						// calulator 0 1 vs 0 3
						int A01 = range(contounrs_hull_marker[0][0], contounrs_hull_marker[0][1]);

						int A03 = range(contounrs_hull_marker[0][0], contounrs_hull_marker[0][3]);

						if (A01 > A03)
						{
							A = midpoint(contounrs_hull_marker[0][3], contounrs_hull_marker[0][0]);

							B = midpoint(contounrs_hull_marker[0][2], contounrs_hull_marker[0][1]);
						}
						else
						{
							A = midpoint(contounrs_hull_marker[0][1], contounrs_hull_marker[0][0]);

							B = midpoint(contounrs_hull_marker[0][2], contounrs_hull_marker[0][3]);
						}
						lst_angle[i] = (calulator_angle(A, B));
					}
				}
				cv::Mat Obj_original = draw_Detection_obj(img, contounrs_hull_item, lst_Point_C_item, lst_angle, name_obj);
				// add info to text
				add_info(contounrs_hull_item, lst_Point_C_item, lst_angle, name_obj);
				cv::imshow("mask", Obj_original);
				cv::waitKey(40);
			}
			catch (const std::exception & e)
			{
				std::cerr << e.what() << '\n';
			}
		}
	}
	else
	{
		MessageBox::Show("Path emtry");
	}
}
private: System::Void btnTrackBar_Click(System::Object^ sender, System::EventArgs^ e) {
	if (txtPath->Text->Length != 0)
	{
		std::string path_mp4 = msclr::interop::marshal_as<std::string>(txtPath->Text);
		get_HSV_trackbar(path_mp4);
	}
	else
	{
		MessageBox::Show("Path emtry");
	}
}
private: System::Void btnSetHSV_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Loadding");
}
};
}
