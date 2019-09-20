#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/process.h>
#include <wx/txtstrm.h>

#ifndef __ELETTA_PROCESS_H__
#define __ELETTA_PROCESS_H__

#define ELET_INVALID_ARG        1       /* Invalid command line arg */
#define ELET_INVALID_INIT       2       /* Invalid initialization */
#define ELET_INVALID_PASSLIST   3       /* Invalid password file */
#define ELET_FEW_PASS           4       /* passwords not found */
#define ELET_INVALID_PERCENT    5       /* Invalid percentage */
#define ELET_INVALID_FILE       6       /* Unable to open file in reading */
#define ELET_INIT_INTERNAL      7       /* Unable to init internal mcrypt/mhash */
#define ELET_FAIL_COLLISION     8       /* fail collide password in entry point */
#define ELET_FINAL_WRITE        9       /* Unable to write archive */
#define ELET_READ_CRYPFILE      10      /* unable to read encrypted file */
#define ELET_BAD_EP             11      /* bad entry point found */
#define ELET_BAD_DECOMPR        12      /* fail in decompression */

class Process: public wxProcess {
public:
  Process			(wxWindow *	parent);
  ~Process			();

  void Decrypt			(wxString	input,
  				 wxString	password,
				 wxString	output);

  void Encrypt			(wxString	output,
				 int		incsize,
				 wxListCtrl *	inputs);

private:
  virtual void OnTerminate	(int		pid,
  				 int		status);

  wxWindow *		m_parent;
  wxMessageDialog *	m_dialog;
};

#endif 

/* EOF */
