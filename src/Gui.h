#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/notebook.h>
#include <wx/file.h>
#include <wx/dir.h>

#include "Process.h"
#include "Password.h"

#ifndef __ELETTA_GUI_H__
#define __ELETTA_GUI_H__

class Gui: public wxFrame {
public:
  Gui					(const wxString &	title);

private:
  void		FileChooser		(wxCommandEvent &	event);
  void		DirectoryChooser	(wxCommandEvent &	event);

  void		EncryptAddFile		(wxCommandEvent &	event);
  void		EncryptRemoveFile	(wxCommandEvent &	event);
  void		EncryptExec		(wxCommandEvent &	event);
  void		DecryptExec		(wxCommandEvent &	event);

  void		GetPassword		(wxString &		file,
					 wxString &		password);

  enum {
    ELETTRA_ID_ENCRYPT_OUTPUT = 101,

    ELETTRA_ID_ENCRYPT_FILE_ADD,
    ELETTRA_ID_ENCRYPT_FILE_REMOVE,

    ELETTRA_ID_ENCRYPT_EXEC,

    ELETTRA_ID_DECRYPT_INPUT,
    ELETTRA_ID_DECRYPT_OUTPUT,

    ELETTRA_ID_DECRYPT_EXEC
  };

  // Data:
  wxString	m_encrypt_output;

  wxString	m_decrypt_input;
  wxString	m_decrypt_output;

  // Widgets:
  wxSpinCtrl *	m_wx_encrypt_incsize;
  wxListCtrl *	m_wx_encrypt_files;

  wxTextCtrl *	m_wx_decrypt_password;

  wxStatusBar*	m_wx_statusbar;

  // Exec:
  Process *	m_process;
};

#endif 

/* EOF */
