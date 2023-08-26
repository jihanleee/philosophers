#include "philo.h"

void *start_routine(void *bruh)
{
	printf("%s", (char *)bruh);
	return (0);
}

int	main()
{
/* 	int	i;

	pthread_t	thread = 0;
	int			r_thcreate;
	struct timeval tv;
	suseconds_t		tv_usec; */
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	printf("%d\n", mutex.__data.__lock);
	pthread_mutex_lock(&mutex);
	printf("%d\n", mutex.__data.__lock);
	pthread_mutex_unlock(&mutex);
	printf("%d\n", mutex.__data.__lock);
	pthread_mutex_lock(&mutex);
	printf("%d\n", mutex.__data.__lock);
	pthread_mutex_unlock(&mutex);
	printf("%d\n", mutex.__data.__lock);
	pthread_mutex_lock(&mutex);
	printf("%d\n", mutex.__data.__lock);
	pthread_mutex_unlock(&mutex);
	printf("%d\n", mutex.__data.__lock);
	pthread_mutex_lock(&mutex);
	printf("%d\n", mutex.__data.__lock);
	return (0);
}
/*thread creation & time*/
/* int	main()
{
	int	i;

	pthread_t	thread = 0;
	int			r_thcreate;
	struct timeval tv;
	suseconds_t		tv_usec;

	gettimeofday(&tv, NULL);
	tv_usec = tv.tv_usec;
	printf("%ld\n", tv.tv_usec - tv_usec);
	r_thcreate = pthread_create(&thread, NULL, start_routine, "bruh");
	usleep(100000);
	pthread_detach(thread);
	pthread_join(thread, 0);
	printf("wow");
	gettimeofday(&tv, NULL);
	printf("%ld\n", tv.tv_usec - tv_usec);
	return (0);
} */