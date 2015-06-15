#ifndef _POKER_H_
#define _POKER_H_
#define	STRAIGHT_FLUSH	1
#define	FOUR_OF_A_KIND	2
#define	FULL_HOUSE	3
#define	FLUSH		4
#define	STRAIGHT	5
#define	THREE_OF_A_KIND	6
#define	TWO_PAIR	7
#define	ONE_PAIR	8
#define	HIGH_CARD	9

#define	RANK(x)		((x >> 8) & 0xF)

static char *value_str[] = {
	"",
	"Straight Flush",
	"Four of a Kind",
	"Full House",
	"Flush",
	"Straight",
	"Three of a Kind",
	"Two Pair",
	"One Pair",
	"High Card"
};

#define CLUB	0x8000
#define DIAMOND 0x4000
#define HEART   0x2000
#define SPADE   0x1000

#define Deuce	0x00010000
#define Trey	    0x00020000
#define Four	    0x00040000
#define Five	    0x00080000
#define Six	      0x00100000
#define Seven	0x00200000
#define Eight		0x00400000
#define Nine		0x00800000
#define Ten		0x01000000
#define Jack		 0x02000000
#define Queen	 0x04000000
#define King	     0x08000000
#define Ace        0x10000000

/*
** each of the thirteen card ranks has its own prime number
**
** deuce = 2
** trey  = 3
** four  = 5
** five  = 7
** ...
** king  = 37
** ace   = 41
*/
int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41 };

//如CLUB DEUCE 的int值应该为 c1=CLUB+Deuce+primes[0]
#endif