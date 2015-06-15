#ifndef _POKERSORT_H_
#define _POKERSORT_H_
/*
** this is a table lookup for all "flush" hands (e.g.  both
** flushes and straight-flushes.  entries containing a zero
** mean that combination is not possible with a five-card
** flush hand.
*/
extern int compare7(int* c);
#endif