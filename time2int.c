#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <getopt.h>

char *time2int_version = "0.0.4";

const struct option long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"ctime-full", no_argument, NULL, 'C'},
	{"ctime", no_argument, NULL, 'c'},
	{"time", required_argument, NULL, 't'},
	{"uptime", no_argument, NULL, 'u'},
	{"version", no_argument, NULL, 'V'},
};
const char *short_options = "hCct:uV";

time_t t0;
struct timeval tv0, tvc, tvd;
struct tm *tm0;

void HelpShow (void) {
	printf ("time2int argument usages:\n"
"  -C, --ctime-full          Show C func. gettimeofday() (14234789.987321) \n"
"  -c, --ctime               Show C function time() call result (14231568)\n"
"  -t, --time                Show normal time (2018-12-31 23:59:01) from ctime (1526000662)\n"
"  -u, --uptime              Show system uptime in seconds\n"
"  -h, --help                Show this help message and exit\n");
}

void CTime2Time(unsigned int time2) {
	time_t t0 = (time_t)time2;
	struct tm *tm0 = gmtime(&t0);
	printf("%d-%02d-%02d %02d:%02d:%02d\n", tm0->tm_year+1900, tm0->tm_mon, tm0->tm_mday,
		tm0->tm_hour, tm0->tm_min, tm0->tm_sec);

}

void Time2CTime (void) {
	printf ("%ld\n", time(NULL));
}

void Time2CTimeFull (void) {
	gettimeofday (&tv0, NULL);
	printf ("%ld.%06ld\n", tv0.tv_sec, tv0.tv_usec);
}

void Time2DaySeconds (void) {
}

void Time2DaySecondsFull (void) {
}

void Time2Seconds (char *timestr) {
	unsigned int cnt, read, hours, minutes, seconds;
	char str[4], *c;
	for (cnt = 0, read = 0, c = timestr; read < 3; c++,cnt++) {
		if (*c == ':' || *c == '\0') {
			str[cnt] = '\0';
			if (read == 0) hours = atoi (str);
			else if (read == 1) minutes = atoi (str);
			else if (read == 2) seconds = atoi (str);
			++read;
			cnt = 0;
		}
		else
			str[cnt] = *c;
	}

	printf ("%u\n", (hours*60*60) + (minutes*60) + seconds);
}

void Uptime(void) {
	struct sysinfo si;
	sysinfo(&si);
	printf("%ld\n", si.uptime);
}

int main (int argc, char **argv) {
	int c;
	while (1) {
		c = getopt_long(argc, argv, short_options, long_options, NULL);
		if (c == -1) break;
		switch (c) {
		case 'C':
			Time2CTimeFull ();
			break;
		case 'c':
			Time2CTime ();
			break;
		case 't':
			if (optarg != NULL)
				CTime2Time(atoi(optarg));
			break;
		case 'u':
			Uptime();
			break;
		case 'h':
			HelpShow ();
			exit (0);
			break;
		}
//			Time2Seconds (argv[1]);
	}
	if (argc == 1) {
		printf ("%lu\n", time(NULL));
	}
	

	return 0;
}

