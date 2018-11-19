#ifndef INTERFACE_DATA_FETCH_H
#define INTERFACE_DATA_FETCH_H

#include <opencv2/opencv.hpp>

class IDataFetch
{
public:
	virtual  cv::Mat GetImage() = 0;
};

#endif //INTERFACE_DATA_FETCH_H
