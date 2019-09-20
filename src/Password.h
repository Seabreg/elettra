#include <wx/wx.h>
#include <wx/file.h>
#include <wx/dir.h>
#include <wx/listctrl.h>

#ifndef __ELETTA_PASSWORD_H__
#define __ELETTA_PASSWORD_H__

class Password: public wxDialog {
public:
  Password		(const wxString &	title,
  			 wxString &		file,
  			 wxString &		password,
			 wxListCtrl *		input);

private:
  wxTextCtrl *	m_wx_password;
  wxString 	m_file;
  wxListCtrl *	m_inputs;

  enum {
    ELETTRA_ID_PASSWORD_FILE,
    ELETTRA_ID_PASSWORD_OK,
    ELETTRA_ID_PASSWORD_CLOSE
  };

  void	FileChooser	(wxCommandEvent &	event);

  void	ButtonOk	(wxCommandEvent &	event);
  void	ButtonClose	(wxCommandEvent &	event);

};

#endif 

/* EOF */
