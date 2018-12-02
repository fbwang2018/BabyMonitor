#include "RstpDataFetch.hpp"
#include <chrono>
#include <thread>
#include <ctime>
#include <time.h>
#include <iostream>
using namespace cv;


void RstpDataFetch::Display(void*data,void *id)
{	/*
	int static i = 0;

    IplImage *img = cvCreateImage(CvSize(m_width, m_height), IPL_DEPTH_8U, 4);
    
	img->imageData = m_videoBuf;

	if(m_saveImg)
	{
		Mat Img;
		sprintf_s(m_fileName, 55, "D:\\github\\BabyMonitor\\res\\train\\%d.jpg", i++);

		Img = cvarrToMat(img);

		imwrite(m_fileName, Img);

		m_saveImg = false;
	}

    cvReleaseImage(&img);
	*/
}

void *RstpDataFetch::Lock(void *data, void**p_pixels)
{
	PCTX ctx = (PCTX)data;

	ctx->m_mtx.lock();

    *p_pixels = ctx->pixels;

    return 0;
}

void RstpDataFetch::Unlock(void *data, void *id, void *const *p_pixels)
{
	PCTX ctx = (PCTX)data;

	ctx->m_mtx.unlock();

    assert(id== nullptr);
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
	if (m_vlcMedia)
	{
		libvlc_media_release(m_vlcMedia);
	}

	if (m_vlcPlayer)
	{
		libvlc_media_player_release(m_vlcPlayer);
	}

	if (m_vlcInst)
	{
		libvlc_release(m_vlcInst);
	}

	if (m_pCtx->m_img)
	{
		delete m_pCtx->m_img;
	}
}

string RstpDataFetch::GetImage()
{
	 //m_pCtx->m_mtx.lock();
	std::cout << "camaera status:" << libvlc_media_player_is_playing(m_vlcPlayer) << std::endl;
	while (libvlc_media_player_is_playing(m_vlcPlayer) != 1)
	{
		libvlc_state_t state = libvlc_media_player_get_state(m_vlcPlayer);
		std::cout << "the media player state is:" << state << std::endl;
		libvlc_media_player_stop(m_vlcPlayer);

		std::cout << "the media player is not playing release resource and re init" << std::endl;
		if (m_vlcMedia)
		{
			libvlc_media_release(m_vlcMedia);
		}

		if (m_vlcPlayer)
		{
			libvlc_media_player_release(m_vlcPlayer);
		}

		if (m_vlcInst)
		{
			libvlc_release(m_vlcInst);
		}

		Init();

		std::this_thread::sleep_for(300s);
	}
	 struct tm ts;   //tm½á¹¹Ö¸Õë

	 auto t = chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	 localtime_s(&ts, &t);

	 sprintf_s(m_fileName, 55, "D:\\github\\BabyMonitor\\res\\train\\%d-%d-%d_%d_%d.jpg", ts.tm_year + 1900, ts.tm_mon + 1, ts.tm_mday, ts.tm_hour, ts.tm_min);

	// imwrite(m_fileName, (*m_pCtx->m_img));
	
	 
	 libvlc_video_take_snapshot(m_vlcPlayer, 0, m_fileName, 0, 0);

	 //m_pCtx->m_mtx.unlock();
	 return string(m_fileName);
 }

 void RstpDataFetch::Init()
 {
	 m_pCtx = new CTX();

	m_pCtx->m_img = new cv::Mat(m_height, m_width, CV_8UC3);
	//m_pCtx->m_img = (char*)malloc((m_height * m_width) << 2);

	m_pCtx->pixels = (unsigned char*)m_pCtx->m_img->data;
	//m_pCtx->pixels = (unsigned char*)m_pCtx->m_img;

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
	libvlc_media_add_option(m_vlcMedia, ":avcodec-hw=none");

 	m_vlcPlayer = libvlc_media_player_new_from_media(m_vlcMedia);
	
	//libvlc_video_set_callbacks(m_vlcPlayer, Lock, Unlock, Display, m_pCtx);

	//libvlc_video_set_format(m_vlcPlayer, "RV24", m_width, m_height, m_width*3);

	libvlc_media_player_play(m_vlcPlayer);
 }
 char* RstpDataFetch::m_videoBuf = (char*)malloc((m_height * m_width) << 2);

 char  RstpDataFetch::m_fileName[56] = { 0 };

 bool  RstpDataFetch::m_saveImg = false;

 void RstpDataFetch::PauseDevice()
 {
	 libvlc_media_player_set_pause(m_vlcPlayer, 1);
 }

 void RstpDataFetch::ResumeDevice()
 {
	 libvlc_media_player_set_pause(m_vlcPlayer, 0);
 }