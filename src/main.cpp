#include "main.h"

IMPLEMENT_APP (Elettra);

// Here we are...
bool Elettra::OnInit ()
{
  Gui *
    gui = new Gui (wxT ("Elettra"));
  SetTopWindow (gui);
  gui->Show ();

  return true;
}

/* EOF */
