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

string BabyMonitor::GetImage()
{
	//m_dataFetch->ResumeDevice();

	//std::this_thread::sleep_for(1s);

	string imgpath = m_dataFetch->GetImage();

	//m_dataFetch->PauseDevice();

	return imgpath;
}