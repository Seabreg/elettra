#include "Process.h"
#include "About.h"

// Exec a command, show the progressdialog and active the timer:
Process::Process (wxWindow * parent):wxProcess (0)
{
  Redirect ();

  m_parent = parent;

  m_dialog = new wxMessageDialog (m_parent, wxT("Work in progres..."), wxT ("Elettra"), wxOK);

  m_dialog->Show ();
}

// Destroy:
Process::~Process ()
{
  delete m_dialog;
}

// When the program exits:
void
Process::OnTerminate (int pid, int status)
{
  wxString string;

  switch (status)
    {
    case ELET_INVALID_ARG:
      string =
	wxT ("Invalid argument... pls! Send a report to " ELETTRA_EMAIL);
      break;

    case ELET_INVALID_INIT:
      string =
	wxT ("Invalid initialization.. pls! Send a report to " ELETTRA_EMAIL);
      break;

    case ELET_INVALID_PASSLIST:
      string = wxT ("The Password File is not valid. Change it and retry.");
      break;

    case ELET_FEW_PASS:
      string =
	wxT ("Passwords not found. Change the Password File and retry.");
      break;

    case ELET_INVALID_PERCENT:
      string = wxT ("Invalid Percentual value. Change it and retry.");
      break;

    case ELET_INVALID_FILE:
      string =
	wxT
	("Unable to open file in reading. Check the permissions and retry.");
      break;

    case ELET_INIT_INTERNAL:
      string =
	wxT ("Unable to init internal mcrypt/mhash. Send a report to "
	     ELETTRA_EMAIL);
      break;

    case ELET_FAIL_COLLISION:
      string = wxT ("Fail collide password in entry point.");
      break;

    case ELET_FINAL_WRITE:
      string = wxT ("Enable to write archive.");
      break;

    case ELET_READ_CRYPFILE:
      string =
	wxT
	("Enable to read encrypted file. Check the input file and retry.");
      break;

    case ELET_BAD_EP:
      string = wxT ("Bad entry point found.");
      break;

    case ELET_BAD_DECOMPR:
      string = wxT ("Fail in decompression. I'm sorry...");
      break;

    default:
      if (status != 0)
	{
	  wxInputStream *es = GetErrorStream ();
	  wxTextInputStream *tes = new wxTextInputStream (*es);
	  wxString string;

	  while (!es->Eof () && es->IsOk ())
	    {
	      string.Append (tes->ReadLine ());
	      string.Append ('\n');
	    }

	  delete tes;
	}

      break;
    }

  // Errors?
  if (string != wxEmptyString)
    {
      wxMessageDialog *dialog;
      dialog =
	new wxMessageDialog (m_parent,
			     wxString::
			     Format (wxT ("Error executing the command:\n%s"),
				     string.c_str ()), wxT ("Attention!"),
			     wxOK);
      dialog->ShowModal ();

      delete this;
      return;
    }

  wxInputStream *is = GetInputStream ();
  wxTextInputStream *tis = new wxTextInputStream (*is);

  while (!is->Eof () && is->IsOk ())
    {
      string.Append (tis->ReadLine ());
      string.Append ('\n');
    }

  delete tis;

  if (string != wxEmptyString)
    string = wxT ("Done!");

  wxMessageDialog *dialog;
  dialog = new wxMessageDialog (m_parent, string, wxT ("Elettra"), wxOK);
  dialog->ShowModal ();

  delete this;
}

// Create the encrypt command and exec it: 
void
Process::Encrypt (wxString output, int incsize, wxListCtrl * inputs)
{
  wxString argv;
  argv << wxT (ELETTRA_BIN) << wxT (" encrypt \"") << output << wxT ("\" ") <<
    incsize << wxT ("%");

  wxListItem row_info;

  for (size_t i = 0, size = inputs->GetItemCount (); i < size; i++)
    {
      row_info.m_itemId = i;
      row_info.m_col = 0;
      row_info.m_mask = wxLIST_MASK_TEXT;

      inputs->GetItem (row_info);
      argv << wxT (" \"") << row_info.m_text << wxT ("::");

      wxString *password = (wxString *) inputs->GetItemData (i);
      argv << *password << wxT ("\"");
    }

  wxExecute (argv, wxEXEC_ASYNC, this);
}

// Create the Decrypt command and exec it:
void
Process::Decrypt (wxString input, wxString password, wxString output)
{
  wxString argv;
  argv << wxT (ELETTRA_BIN) << wxT (" decrypt \"") << input << wxT ("\" \"")
    << password << wxT ("\" \"") << output << wxT ("\"");

  if (!wxExecute (argv, wxEXEC_ASYNC, this))
    {
      wxMessageDialog *dialog =
	new wxMessageDialog (m_parent, wxT ("Error executing the command"),
			     wxT ("Attention!"), wxOK);
      dialog->ShowModal ();

      delete this;
    }
}

/* EOF */
