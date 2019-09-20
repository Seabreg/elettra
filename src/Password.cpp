#include "Password.h"
#include "About.h"

// Interface
Password::Password (const wxString & title, wxString & file, wxString & password, wxListCtrl * inputs):
wxDialog (NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
  wxBoxSizer *hbox;
  wxStaticText *string;

  m_inputs = inputs;

  wxBoxSizer *vbox = new wxBoxSizer (wxVERTICAL);

  hbox = new wxBoxSizer (wxHORIZONTAL);
  string = new wxStaticText (this, wxID_ANY, wxT ("File:"));

  hbox->Add (string, 0, wxRIGHT, 8);
  wxButton *wx_file =
    new wxButton (this, ELETTRA_ID_PASSWORD_FILE, wxT ("---"));
  Connect (ELETTRA_ID_PASSWORD_FILE, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Password::FileChooser));

  hbox->Add (wx_file, 1);
  vbox->Add (hbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

  vbox->Add (-1, 10);

  hbox = new wxBoxSizer (wxHORIZONTAL);
  string = new wxStaticText (this, wxID_ANY, wxT ("Password:"));

  hbox->Add (string, 0, wxRIGHT, 8);
  m_wx_password =
    new wxTextCtrl (this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		    wxDefaultSize, wxTE_PASSWORD);
  hbox->Add (m_wx_password, 1);
  vbox->Add (hbox, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

  vbox->Add (-1, 10);

  hbox = new wxBoxSizer (wxHORIZONTAL);
  vbox->Add (hbox, 1, wxALL, 10);

  vbox->Add (-1, 10);

  hbox = new wxBoxSizer (wxHORIZONTAL);
  vbox->Add (hbox, 0, wxALIGN_RIGHT | wxRIGHT, 10);

  wxButton *button = new wxButton (this, ELETTRA_ID_PASSWORD_OK, wxT ("Ok"));
  hbox->Add (button, 0);
  Connect (ELETTRA_ID_PASSWORD_OK, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Password::ButtonOk));

  button = new wxButton (this, ELETTRA_ID_PASSWORD_CLOSE, wxT ("Close"));
  hbox->Add (button, 0, wxLEFT | wxBOTTOM, 5);
  Connect (ELETTRA_ID_PASSWORD_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED,
	   wxCommandEventHandler (Password::ButtonClose));

  SetSizer (vbox);

  Layout ();
  Centre ();
  ShowModal ();
  Destroy ();

  file = m_file;
  password = m_wx_password->GetValue ();
}

// Select a file and put it into the correct button
void
Password::FileChooser (wxCommandEvent & event)
{
  wxString file;
  wxButton *button = static_cast < wxButton * >(event.GetEventObject ());

  // Open and check if it exists
  while (1)
    {
      wxFileDialog fd (this, wxT ("Choose the Output File"), wxEmptyString,
		       wxEmptyString, wxT ("*"), wxFD_OPEN);

      if (fd.ShowModal () != wxID_OK)
	return;

      if (wxFile::Exists (fd.GetPath ()) == true)
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
    case ELETTRA_ID_PASSWORD_FILE:
      m_file = file;
      button->SetLabel (m_file);
      break;

    default:
      break;
    }
}

void
Password::ButtonOk (wxCommandEvent & event)
{
  if (m_file == wxEmptyString)
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("Select the Input file!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
      return;
    }

  wxString password = m_wx_password->GetValue ();

  if (password == wxEmptyString)
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (this, wxT ("Insert the Password!"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();
      return;
    }

  if (password.Length () < 6)
    {
      wxMessageDialog *dialog = new wxMessageDialog (this,
						     wxT
						     ("The length of the password is too short!"),
						     wxT ("Attention!"),
						     wxOK);
      dialog->ShowModal ();
      return;
    }

  wxListItem row_info;

  for (size_t i = 0, size = m_inputs->GetItemCount (); i < size; i++)
    {
      row_info.m_itemId = i;
      row_info.m_col = 0;
      row_info.m_mask = wxLIST_MASK_TEXT;

      m_inputs->GetItem (row_info);

      wxString *pass = (wxString *) m_inputs->GetItemData (i);

      if (password == *pass)
	{
	  wxMessageDialog *dialog = new wxMessageDialog (this,
							 wxT
							 ("Password already used by another file!"),
							 wxT ("Attention!"),
							 wxOK);
	  dialog->ShowModal ();
	  return;
	}
    }

  Close (true);
}

void
Password::ButtonClose (wxCommandEvent & event)
{
  m_file = wxEmptyString;
  Close (true);
}

/* EOF */
