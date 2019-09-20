#include "Gui.h"
#include "About.h"

// Interface
Gui::Gui (const wxString & title):
wxFrame (NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
	 wxDEFAULT_FRAME_STYLE)
{
  wxStaticText *label;
  wxButton *button;
  wxPanel *panel;

  wxBoxSizer *box, *tbox;

  box = new wxBoxSizer (wxVERTICAL);
  SetSizer (box);

  // Notebook:
  wxNotebook *notebook =
    new wxNotebook (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
  box->Add (notebook, 1, wxEXPAND, 0);

  // Encrypt page:
  panel = new wxPanel (notebook, wxID_ANY);
  notebook->AddPage (panel, wxT ("Encrypt"));

  box = new wxBoxSizer (wxVERTICAL);
  panel->SetSizer (box);

  // Encrypt Output file:
  tbox = new wxBoxSizer (wxHORIZONTAL);
  box->Add (tbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

  label = new wxStaticText (panel, wxID_ANY, wxT ("Output File:"));
  tbox->Add (label, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);

  button = new wxButton (panel, ELETTRA_ID_ENCRYPT_OUTPUT, wxT ("---"));
  Connect (ELETTRA_ID_ENCRYPT_OUTPUT, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Gui::FileChooser));
  tbox->Add (button, 1);

  tbox->Add (-1, 10);

  // Encrypt Incremental Size:
  tbox = new wxBoxSizer (wxHORIZONTAL);
  box->Add (tbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

  label = new wxStaticText (panel, wxID_ANY, wxT ("Incremental Size:"));
  tbox->Add (label, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);

  m_wx_encrypt_incsize =
    new wxSpinCtrl (panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
		    wxDefaultSize, wxSP_ARROW_KEYS, 10, 1000);
  m_wx_encrypt_incsize->SetValue (10);
  tbox->Add (m_wx_encrypt_incsize, 1);

  tbox->Add (-1, 10);

  // Encrypt File Box:
  m_wx_encrypt_files =
    new wxListCtrl (panel, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		    wxLC_REPORT);

  m_wx_encrypt_files->InsertColumn (0, wxT ("Files"));
  m_wx_encrypt_files->SetColumnWidth (0, wxLIST_AUTOSIZE_USEHEADER);

  box->Add (m_wx_encrypt_files, 1, wxEXPAND | wxALL, 10);

  // Encrypt File Box Buttons:
  tbox = new wxBoxSizer (wxHORIZONTAL);
  box->Add (tbox, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

  button =
    new wxButton (panel, ELETTRA_ID_ENCRYPT_FILE_REMOVE, wxT ("Remove"));
  Connect (ELETTRA_ID_ENCRYPT_FILE_REMOVE, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Gui::EncryptRemoveFile));
  tbox->Add (button, 0);

  button = new wxButton (panel, ELETTRA_ID_ENCRYPT_FILE_ADD, wxT ("Add"));
  Connect (ELETTRA_ID_ENCRYPT_FILE_ADD, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Gui::EncryptAddFile));
  tbox->Add (button, 0);

  // Encrypt Exec Button
  button = new wxButton (panel, ELETTRA_ID_ENCRYPT_EXEC, wxT ("&Ok"));
  box->Add (button, 0, wxALIGN_RIGHT, 0);
  Connect (ELETTRA_ID_ENCRYPT_EXEC, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Gui::EncryptExec));

  // Decrypt page:
  panel = new wxPanel (notebook, wxID_ANY);
  notebook->AddPage (panel, wxT ("Decrypt"));

  box = new wxBoxSizer (wxVERTICAL);
  panel->SetSizer (box);

  // Decrypt Input file:
  tbox = new wxBoxSizer (wxHORIZONTAL);
  box->Add (tbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

  label = new wxStaticText (panel, wxID_ANY, wxT ("Input File:"));
  tbox->Add (label, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);

  button = new wxButton (panel, ELETTRA_ID_DECRYPT_INPUT, wxT ("---"));
  Connect (ELETTRA_ID_DECRYPT_INPUT, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Gui::FileChooser));
  tbox->Add (button, 1);

  tbox->Add (-1, 10);

  // Decrypt Password:
  tbox = new wxBoxSizer (wxHORIZONTAL);
  box->Add (tbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

  label = new wxStaticText (panel, wxID_ANY, wxT ("Password:"));
  tbox->Add (label, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);

  m_wx_decrypt_password =
    new wxTextCtrl (panel, wxID_ANY, wxEmptyString, wxDefaultPosition,
		    wxDefaultSize, wxTE_PASSWORD);
  tbox->Add (m_wx_decrypt_password, 1);

  tbox->Add (-1, 10);

  // Decrypt Output Directory:
  tbox = new wxBoxSizer (wxHORIZONTAL);
  box->Add (tbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

  label = new wxStaticText (panel, wxID_ANY, wxT ("Output Directory:"));
  tbox->Add (label, 0, wxRIGHT | wxALIGN_CENTER_VERTICAL, 10);

  button = new wxButton (panel, ELETTRA_ID_DECRYPT_OUTPUT, wxT ("---"));
  Connect (ELETTRA_ID_DECRYPT_OUTPUT, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Gui::DirectoryChooser));
  tbox->Add (button, 1);

  tbox->Add (-1, 10);

  // Spacer:
  tbox = new wxBoxSizer (wxHORIZONTAL);
  box->Add (tbox, 1, wxEXPAND | wxALL, 10);

  // Decrypt Exec:
  button = new wxButton (panel, ELETTRA_ID_DECRYPT_EXEC, wxT ("&Ok"));
  box->Add (button, 0, wxALIGN_RIGHT, 0);
  Connect (ELETTRA_ID_DECRYPT_EXEC, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Gui::DecryptExec));

  // About page:
  panel = new wxPanel (notebook, wxID_ANY);
  notebook->AddPage (panel, wxT ("About"));

  box = new wxBoxSizer (wxVERTICAL);
  panel->SetSizer (box);

  label = new wxStaticText (panel, wxID_ANY, wxT (ELETTRA_ABOUT));
  box->Add (label, 0,
	    wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxTOP, 10);

  // Statusbar:
  m_wx_statusbar = CreateStatusBar (1, 0);
  m_wx_statusbar->SetStatusText (wxT ("Welcome to elettra!"));

  SetSize (-1, 400);
  Layout ();
  Centre ();
}

// Select a file and put it into the correct button
void
Gui::FileChooser (wxCommandEvent & event)
{
  wxString file;
  wxButton *button = static_cast < wxButton * >(event.GetEventObject ());

  m_wx_statusbar->SetStatusText (wxT ("Select a file..."));

  // Open and check if it exists
  while (1)
    {
      wxFileDialog fd (this, wxT ("Choose the Output File"), wxEmptyString,
		       wxEmptyString, wxT ("*"), wxFD_OPEN);

      if (fd.ShowModal () != wxID_OK)
	{
	  m_wx_statusbar->SetStatusText (wxT ("Select a file: aborted"));
	  return;
	}

      if (wxFile::Exists (fd.GetPath ()) == true
	  || event.GetId () == ELETTRA_ID_ENCRYPT_OUTPUT)
	{
	  file = fd.GetPath ();
	  break;
	}

      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("This file doesn't exist!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
    }

  // Fill the button and the string:
  switch (event.GetId ())
    {
    case ELETTRA_ID_ENCRYPT_OUTPUT:
      m_encrypt_output = file;
      button->SetLabel (m_encrypt_output);
      break;

    case ELETTRA_ID_DECRYPT_INPUT:
      m_decrypt_input = file;
      button->SetLabel (m_decrypt_input);
      break;

    default:
      break;
    }

  m_wx_statusbar->SetStatusText (wxT ("Selected file!"));
}

// Select a directory and put it into the correct button
void
Gui::DirectoryChooser (wxCommandEvent & event)
{
  wxString directory;
  wxButton *button = static_cast < wxButton * >(event.GetEventObject ());

  m_wx_statusbar->SetStatusText (wxT ("Select a directory..."));

  // Open and check if it exists
  while (1)
    {
      wxDirDialog fd (this, wxT ("Choose the Output Directory"));

      if (fd.ShowModal () != wxID_OK)
	{
	  m_wx_statusbar->SetStatusText (wxT ("Select a directory: aborted"));
	  return;
	}

      if (wxDir::Exists (fd.GetPath ()) == true)
	{
	  directory = fd.GetPath ();
	  break;
	}

      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("This directory doesn't exist!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
    }

  // Fill the button and the string:
  switch (event.GetId ())
    {
    case ELETTRA_ID_DECRYPT_OUTPUT:
      m_decrypt_output = directory;
      button->SetLabel (m_decrypt_output);
      break;

    default:
      break;
    }

  m_wx_statusbar->SetStatusText (wxT ("Selected directory!"));
}

// Add a file into the listbox:
void
Gui::EncryptAddFile (wxCommandEvent & event)
{
  m_wx_statusbar->SetStatusText (wxT ("Select a file..."));

  wxString file, password;
  GetPassword (file, password);

  if (file == wxEmptyString || password == wxEmptyString)
    {
      m_wx_statusbar->SetStatusText (wxT ("Select a file: aborted!"));
      return;
    }

  wxListItem item;
  item.SetData (new wxString (password));
  item.SetColumn (0);
  item.SetText (file);

  m_wx_encrypt_files->InsertItem (item);

  m_wx_statusbar->SetStatusText (wxT ("Selected the file!"));
}

// Remove items from the listbox:
void
Gui::EncryptRemoveFile (wxCommandEvent & event)
{
  int number = 0;

  for (size_t i = 0, length = m_wx_encrypt_files->GetItemCount (); i < length;
       i++)
    {
      if (m_wx_encrypt_files->GetItemState (i, wxLIST_STATE_SELECTED))
	{
	  wxString *password =
	    (wxString *) m_wx_encrypt_files->GetItemData (i);
	  delete password;

	  m_wx_encrypt_files->DeleteItem (i);
	  number++;
	}
    }

  m_wx_statusbar->
    SetStatusText (wxString::Format (wxT ("Delete %d file(s)!"), number));
}

// Check inputs from the encrypt func and run the process:
void
Gui::EncryptExec (wxCommandEvent & event)
{
  if (m_encrypt_output == wxEmptyString)
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("Select the Output file!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
      return;
    }

  if (m_wx_encrypt_files->GetItemCount () <= 0)
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("Insert files!"), wxT ("Attention!"),
			     wxOK);
      dialog->ShowModal ();
      return;
    }

  m_wx_statusbar->
    SetStatusText (wxString::
		   Format (wxT ("Encrypting %d file(s)..."),
			   m_wx_encrypt_files->GetItemCount ()));

  m_process = new Process (this);
  m_process->Encrypt (m_encrypt_output, m_wx_encrypt_incsize->GetValue (),
		      m_wx_encrypt_files);
}

// Check inputs from the decrypt func and run the process:
void
Gui::DecryptExec (wxCommandEvent & event)
{
  if (m_decrypt_input == wxEmptyString)
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("Select the Input file!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
      return;
    }

  if (m_wx_decrypt_password->GetValue () == wxEmptyString)
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("Insert the Password!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
      return;
    }

  if (m_decrypt_output == wxEmptyString)
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("Select the Output directory!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
      return;
    }

  m_wx_statusbar->SetStatusText (wxT ("Decrypting file..."));

  m_process = new Process (this);
  m_process->Decrypt (m_decrypt_input, m_wx_decrypt_password->GetValue (),
		      m_decrypt_output);
}

void
Gui::GetPassword (wxString & file, wxString & password)
{
  Password *dialog =
    new Password (wxT ("Elettra"), file, password, m_wx_encrypt_files);
  dialog->Show ();
}

/* EOF */
