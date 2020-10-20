#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
	EVT_BUTTON(10001,OnButtonClicked)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(wxWindow* parent,
	wxWindowID id,
	const wxString& title,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxString& name) : wxFrame(parent, id, title, pos, size, style, name)
{
	m_btn1 = new wxButton(this, 10001, "Click Me", wxPoint(10, 10), wxSize(150, 50));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}

void MainWindow::OnButtonClicked(wxCommandEvent &evt) {
	m_list1->AppendString(m_txt1->GetValue());
	evt.Skip();
}

MainWindow::~MainWindow() {

}