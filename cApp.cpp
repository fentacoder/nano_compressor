#include "cApp.h"
#include "id.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {

}

bool cApp::OnInit() {
	if (!wxApp::OnInit()) {
		return false;
	}

	MainWindow* main = new MainWindow(nullptr, window::id::MAINWINDOW, _("Main Window"),wxPoint(30,30),wxSize(800,600));
	main->Show();
	return true;
}

DECLARE_APP(cApp);