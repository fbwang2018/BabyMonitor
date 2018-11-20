#ifndef INTERFACE_DATA_FETCH_H
#define INTERFACE_DATA_FETCH_H

#include <opencv2/opencv.hpp>
#pragma comment(lib, "libvlc.lib")
#pragma comment(lib, "libvlccore.lib")
#pragma comment(lib, "opencv_world343d.lib")

class IDataFetch
{
public:
	virtual  cv::Mat GetImage() = 0;
};

#endif //INTERFACE_DATA_FETCH_H
