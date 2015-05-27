#include "CommonHelpers.h"

char threadIDs = 0;
thread_local char curThreadID = 0;

u_int32 uPoT(u_int32 v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	v += (v == 0);
	return v;

}