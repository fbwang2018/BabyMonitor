#include "RstpDataFetch.hpp"
#include <chrono>
#include <thread>

using namespace cv;

int width = 640;

int height = 480;

#define _CRT_SECURE_NO_WARNINGS

void RstpDataFetch::Display(void*data,void *id)
{
	int static i = 0;
	
	i++;

    IplImage *img = cvCreateImage(CvSize(width, height), IPL_DEPTH_8U, 4);


    img->imageData = videobuf;
	sprintf_s(szName, 55, "E:\\%d.jpg", i++);

	Mat Img;
	Img = cvarrToMat(img);
	imwrite(szName, Img);

   // cvShowImage("test", img);

    //waitKey(10);

    cvReleaseImage(&img);

}

void *RstpDataFetch::Lock(void *data, void**p_pixels)
{
    *p_pixels = videobuf;

    return NULL;
}

void RstpDataFetch::Unlock(void *data, void *id, void *const *p_pixels)
{
    (void)data;

    assert(id==NULL);
}

RstpDataFetch::RstpDataFetch():m_url(""), m_vlcInst(nullptr)
{
	Init();
}

RstpDataFetch::RstpDataFetch(string& rstp_url):m_url(rstp_url), m_vlcInst(nullptr)
{
	Init();
}

 RstpDataFetch::~RstpDataFetch()
 {
 	if(m_vlcMedia)
 	{
		libvlc_media_release(m_vlcMedia);
 	}

 	if(m_vlcPlayer)
 	{
		libvlc_media_player_release(m_vlcPlayer);
 	}

 	if(m_vlcInst)
 	{
 		libvlc_release(m_vlcInst);
 	}
 }



 cv::Mat RstpDataFetch::GetImage()
 {
 	 cv::Mat img;
	 libvlc_media_player_play(m_vlcPlayer);
	 std::this_thread::sleep_for(2s);

	 libvlc_media_player_stop(m_vlcPlayer);

 	 return img;
 }

 void RstpDataFetch::Init()
 {
 	m_vlcInst = libvlc_new(0, nullptr);

 	if(!m_vlcInst)
 	{
 		cout<<"Fail to init VLC instance"<<endl;

 		return;
 	}

    if(m_url.empty())
    {
		cout<<"The RTSP url is empty"<<endl;

		return;
    }

 	m_vlcMedia = libvlc_media_new_location (m_vlcInst, m_url.c_str());

 	if(!m_vlcMedia)
 	{
		cout<<"The media object is empty"<<endl;

		return;
 	}

 	m_vlcPlayer = libvlc_media_player_new_from_media(m_vlcMedia);

	libvlc_video_set_callbacks(m_vlcPlayer, Lock, Unlock, Display, NULL);

	libvlc_video_set_format(m_vlcPlayer, "RV32", width, height, width << 2);
 }
 char* RstpDataFetch::videobuf = (char*)malloc((height * width) << 2);

 char  RstpDataFetch::szName[56] = { 0 };