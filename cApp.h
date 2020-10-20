#pragma once
#include "wx/wx.h"
#include "MainWindow.h"
 

class cApp : public wxApp
{
private:
	MainWindow* m_frame1 = nullptr;
public:
	cApp();
	~cApp();

	virtual bool OnInit();
};

