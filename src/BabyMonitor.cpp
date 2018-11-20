#include "BabyMonitor.hpp"

BabyMonitor::BabyMonitor(string& rtsp_url):m_dataFetch(new RstpDataFetch(rtsp_url))
{

}
BabyMonitor::~BabyMonitor()
{
	if(m_dataFetch)
	{
		delete m_dataFetch;
	}
}

cv::Mat BabyMonitor::GetImage()
{
	return m_dataFetch->GetImage();
}