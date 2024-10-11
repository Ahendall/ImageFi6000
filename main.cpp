#include <wx/filedlg.h>
#include <wx/wx.h>
#include <cstdio>
#include "filter.h"

class MyApp : public wxApp {
public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
	MyFrame(const wxString &title);

	void OnOpenFile(wxCommandEvent &event); // Event handler for file selection

private:
	wxDECLARE_EVENT_TABLE();
	void UpdateFileSelected(const wxString &imageName);
	void OnApplyFilter(wxCommandEvent &event);
    void UpdateFilterStatus(const wxString &filterType);

	wxStaticText *fileSelectedText;
	wxScrolledWindow *scrollWindow;
    wxButton *applyFilterButton;
    wxChoice *filterChoice;
	int filterStatus = -1;
    wxStaticText *filterStatusText;
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_BUTTON(1001, MyFrame::OnOpenFile)
		wxEND_EVENT_TABLE()

			wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
	MyFrame *frame = new MyFrame("Image Filter-inator 6000");
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString &title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 300)) {

	// Global Sizer
	wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

	// Header Text
	wxStaticText *headerText = new wxStaticText(this, wxID_ANY, "Image Filter-inator 6000", wxDefaultPosition, wxDefaultSize);

	// Font Modifiers
	wxFont font = headerText->GetFont();
	font.SetFaceName("Comic Sans MS");
	font.SetPointSize(21);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	headerText->SetFont(font);

	// Sizer for the header text
	wxBoxSizer *titleSizer = new wxBoxSizer(wxVERTICAL);
	titleSizer->Add(headerText, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10); // Center and add padding

	// Open File Button
	wxBoxSizer *opfiSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton *openButton = new wxButton(this, 1001, "Open .bmp Image", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT | wxALIGN_RIGHT);
	opfiSizer->Add(openButton, 0, wxALL, 5);

	// Dropdown Selector of Filters
	wxArrayString filterOptions;
	filterOptions.Add("Edge");
	filterOptions.Add("Blur");
	filterOptions.Add("Grayscale");
	filterOptions.Add("Sepia");
	filterOptions.Add("Reflect");
	filterChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, filterOptions);
	opfiSizer->Add(filterChoice, 0, wxALL, 5);

	// Scrolled window to hold fileSelectedText || Handle Overflow
	scrollWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(250, 50), wxVSCROLL | wxHSCROLL);
	scrollWindow->SetScrollRate(5, 5);

	// Text --> Currently selected file (set scrollWindow as the parent)
	fileSelectedText = new wxStaticText(scrollWindow, wxID_ANY, "No image selected", wxDefaultPosition, wxDefaultSize);

	// Sizer for layout
	wxBoxSizer *scrollSizer = new wxBoxSizer(wxVERTICAL);
	scrollSizer->Add(fileSelectedText, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

	// Set the sizer for the scrolled window
	fileSelectedText->Wrap(150);
	scrollWindow->SetSizer(scrollSizer);
	scrollWindow->FitInside(); // Ensures the scrolled window's virtual size fits its content
	scrollWindow->Layout();	   // Layout the scroll window

	// Font modifications for the selected text
	wxFont statusFont = fileSelectedText->GetFont();
	statusFont.SetPointSize(8);
	statusFont.SetWeight(wxFONTWEIGHT_LIGHT);
	fileSelectedText->SetFont(statusFont);

    // Apply Filter Button
    // Check if file is selected, only then show the button
    applyFilterButton = new wxButton(this, wxID_ANY, "Apply Filter", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT | wxALIGN_RIGHT);
    applyFilterButton->Disable();
    Bind(wxEVT_BUTTON, &MyFrame::OnApplyFilter, this, applyFilterButton->GetId());


    // Filter Status text
    filterStatusText = new wxStaticText(this, wxID_ANY, "Status | Awaiting", wxDefaultPosition, wxDefaultSize);
    wxFont filterFont = filterStatusText->GetFont();
    filterFont.SetPointSize(8);
    filterFont.SetFaceName("Comic Sans MS");
    filterFont.SetWeight(wxFONTWEIGHT_LIGHT);

    

	// Apply Sizers
	mainSizer->Add(titleSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	mainSizer->Add(opfiSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	mainSizer->Add(scrollWindow, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(applyFilterButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    mainSizer->Add(filterStatusText, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	this->SetSizer(mainSizer);

}

void MyFrame::UpdateFileSelected(const wxString &imageName) {
	fileSelectedText->SetLabelText(imageName);
    applyFilterButton->Enable();
	this->Layout();
	scrollWindow->FitInside();
}

void MyFrame::OnOpenFile(wxCommandEvent &event) {
	// Create a file dialog to select BMP files
	wxFileDialog openFileDialog(this, _("Open BMP file"), "", "",
								"BMP files (*.bmp)|*.bmp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // The user canceled the dialog

	// Get the path of the selected file
	// Gonna need this to use classic C methods of handling files
	wxString filePath = openFileDialog.GetPath();

	// Update the text to show the selected file
	UpdateFileSelected(filePath);
}

void MyFrame::OnApplyFilter(wxCommandEvent& event) {
    // Get the selected filter from the drop-down
    int filterIndex = filterChoice->GetSelection();
    wxString filterType = filterChoice->GetString(filterIndex);

    // File input --> get from the fileSelectedText
    wxString infile = fileSelectedText->GetLabelText();

    // Generate the output file name by appending the filter type
    wxString outfile = infile.BeforeLast('.') + "_" + filterType + ".bmp";


	// Convert to classic C strings
	const char *infile_c = infile.mb_str();
	const char *outfile_c = outfile.mb_str();
    const char *filterType_c = filterType.mb_str();

    // // DEBUG - PRINT ALL THE VALUES
    // printf("Input File: %s\n", infile_c);
    // printf("Output File: %s\n", outfile_c);
    // printf("Filter Type: %s\n", filterType_c);


    // Call Filter function from filter.h
    filterStatus = filterImage(infile_c, outfile_c, filterType_c);
    UpdateFilterStatus(filterType);
}

void MyFrame::UpdateFilterStatus(const wxString &filterType) {
    switch (filterStatus) {
        case 2:
            filterStatusText->SetLabelText("Status | Not enough memory to store image");
            filterStatusText->SetForegroundColour(wxColour(255, 0, 0));
            break;

        case 1:
            filterStatusText->SetLabelText("Status | Unsupported file format");
            filterStatusText->SetForegroundColour(wxColour(255, 0, 0));
            break;

        case 0:
            filterStatusText->SetLabelText("Status | Filter Applied: " + filterType + " (Check your files, it's there!)");
            filterStatusText->SetForegroundColour(wxColour(0, 255, 0));
            break;

        case -1:
            filterStatusText->SetLabelText("Status | Unable to open file");
            filterStatusText->SetForegroundColour(wxColour(255, 0, 0));
            break;

        case -2:
            filterStatusText->SetLabelText("Status | Unable to create output file");
            filterStatusText->SetForegroundColour(wxColour(255, 0, 0));
            break;

        case -3:
            // DEBUGGING CASE
            filterStatusText->SetLabelText("Status | Unknown filter type");
            filterStatusText->SetForegroundColour(wxColour(255, 0, 0));
            break;
        default:
            filterStatusText->SetLabelText("Status | Unknown error occured");
            filterStatusText->SetForegroundColour(wxColour(255, 0, 0));
            break;
    }

    this->Layout();
}