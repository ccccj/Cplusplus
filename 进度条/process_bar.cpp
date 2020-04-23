#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

const char* flag = "-/|\\";

int main() {
	system("clear");
	char buf[101];
	memset(buf, ' ', sizeof(buf));
	buf[100] = '\0';
	for (int i = 0; i < 100; ++i) {
		buf[i] = '#';
		printf("[%c][%s][%d%%]\r", flag[i % 4], buf, i);
		fflush(stdout);
		usleep(100000);
	}
	return 0;
}




