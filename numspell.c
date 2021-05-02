/**
 * \author Serge Yuschenko
 */
#ident "@(#) $Id$"

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

/* let's draw a line somewhere */
#define NMAX  1000000000000000L

/**************************************************************** UNDER10() ***/
/**
 * The function spells a number in 1-9 range.
 *
 * \param num the number to spell
 */
static void under10( long num ) {
	char *txt[] = {
		"one", "two", "three", "four", "five",
		"six", "seven", "eight", "nine"
	};

	if( num > 0 && num < 10 )
		printf( "%s ", txt[ num - 1 ] );
}

/*************************************************************** UNDER100() ***/
/**
 * The function spells a number in 1-99 range.
 *
 * \param num the number to spell
 */
static void under100( long num ) {
	char *nums10_19[] = {
		"ten", "eleven", "twelve", "thirteen", "fourteen",
		"fifteen", "sixteen", "seventeen", "eigteen", "nineteen"
	};

	char *tens[] = {
		"twenty", "thirty", "fourty", "fifty",
		"sixty", "seventy",	"eighty", "ninety"
	};

	if( num > 9 && num < 20 )
		printf( "%s ", nums10_19[ num - 10 ] );
	else {
		if( num > 19 && num < 100 )
			printf( "%s ", tens[ num / 10 - 2 ] );

		under10( num % 10 );
	}
}

/************************************************************** UNDER1000() ***/
/**
 * The function spells a number in 1-999 range.
 *
 * \param num the number to spell
 */
static void under1000( long num ) {
	int  n;

	n = num / 100;

	if( n ) {
		under10( n );
		printf( "hundred ");
	}

	n = num % 100;

	if( n )
		under100( n % 100 );
}

/******************************************************************* MAIN() ***/

int main( int argc, char *argv[] ) {
	long i, num, div = NMAX;
	char *txt[] = {
		"quadrillion",
		"trillion",
		"billion",
		"million",
		"thousand",
		""
	};

	if( argc > 1 )
		num = atol( argv[ 1 ] );
	else {
		printf( "%s %ld-%ld\n", basename( argv[ 0 ] ), -NMAX, NMAX );
		return -1;
	}

	if( num < -NMAX || num > NMAX ) {
		printf( "this is beyond my pay grade\n" );
		return -1;
	}

	if( 0 == num ) {
		printf( "zero\n" );
		return 0;
	}

	if( num < 0 ) {
		printf( "minus " );
		num = -num;
	}

	/* keep reducing the number by the factor of 1000 */
	for( i = 0; div > 0; i++ ) {
		if( num / div ) {
			under1000( num / div );
			printf( "%s ", txt[ i ] );
		}

		num %= div;
		div /= 1000;
	}

	printf( "\n");
	return 0;
}

