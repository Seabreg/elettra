#ifndef __ELETTRA_ABOUT_H__
#define __ELETTRA_ABOUT_H__

#define ELETTRA_EMAIL	"julia@winstonsmith.info"
#define ELETTRA_WWW	"https://www.winstonsmith.info/julia/elettra"
#define ELETTRA_AUTHOR	"Julia"

#define ELETTRA_ABOUT	"Elettra\n" \
			"\n" \
			"Author: " ELETTRA_AUTHOR "\n" \
			"Email: " ELETTRA_EMAIL "\n" \
			"Homepage: " ELETTRA_WWW "\n"

#ifdef WIN32
#  define ELETTRA_BIN	".\\cmd\\elettra.exe"
#else
#  define ELETTRA_BIN	"elettra"
#endif

#endif
