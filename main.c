#include "philo.h"

int	main()
{
	struct timeval	now;
	long	year, month, day, hour, minute, second;

	//	epoch time
	//  starts 1 january 1970
	//	365.24 day in a year
	//	30.44 day in a month
	gettimeofday(&now, NULL);
	second = now.tv_sec;
	// printf("%ld\n", now.tv_sec);
	// second = 1654863553;
	year	=	second / (3600 * 24 * 365.24);
	second	%=	(long)(3600 * 24 * 365.24);
	month	=	second / (long)(3600 * 24 * 30.44);
	second	%=	(long)(3600 * 24 * 30.44);
	day		=	second / (3600 * 24);
	second	%=	(3600 * 24);
	hour	=	second / 3600;
	second	%=	3600;
	minute	=	second / 60;
	second	%=	60;


	// printf("%ld\n", year);
	printf("%ld - %ld - %ld\n", day, month, year + 1970);
	printf("%ld : %ld : %ld\n", hour, minute, second);
}