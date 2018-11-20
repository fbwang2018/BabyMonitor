
#include <iostream>
#include <string>

#include "BabyMonitor.hpp"

using namespace std;
int main(int argc, char *argv[])
{
	std::cout << "========================"<<std::endl;

	string rtsp_url("rtsp://192.168.1.17:554");
	
	BabyMonitor babyMonitor(rtsp_url);

	cv::Mat img = babyMonitor.GetImage();

	return 0;
}