
/**
  @brief: a sample for using gettimeofday()
  @file: time.c
  @date: May 1st, 2012
  @author: yqhuang@uwaterloo.ca 
 */

#include <sys/time.h>
#include <stdio.h>

int 
main(void)
{
	struct timeval tv;
	double t1;
	double t2;

	gettimeofday(&tv, NULL);
	t1 = tv.tv_sec + tv.tv_usec/1000000.0;

	sleep(5);
	usleep(50);

	gettimeofday(&tv, NULL);
	t2 = tv.tv_sec + tv.tv_usec/1000000.0;

	printf("%.6lf seconds elapsed\n", t2-t1);

	return 0;

}
