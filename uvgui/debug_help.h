#ifndef _debug_help_h_
#define _debug_help_h_

#define DEBUG


#ifdef DEBUG
#include <iostream>
using namespace std;
#define DEBUGPRINT cout << __FILE__ <<"   "<< __LINE__<<"\n"
#else
#define DEBUGPRINT
#endif

#endif
