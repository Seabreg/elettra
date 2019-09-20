/*
 *    DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE.
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION:
 *
 *    0. You just DO WHAT THE FUCK YOU WANT TO. 
 *
 */  
    
#ifdef WIN32
    
#include <sys/timeb.h>
#include <Winsock2.h>
int  gettimeofday(struct timeval *tv, void *tz) 
{
    struct _timeb timebuffer;
    _ftime(&timebuffer);
    tv->tv_sec = (long) timebuffer.time;
    tv->tv_usec = timebuffer.millitm * 1000;
    return 0;
}


#endif	/*  */
