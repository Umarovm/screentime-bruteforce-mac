#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

#define ENOUGH 5

void openSystemPreferences() {
	system("open -a System\\ Preferences");
}

int main() {
	struct timeval now;
	int rc;
	char str[ENOUGH], command[24];

	if (getuid()) {
		puts("This program must be run with the root user's privileges in order to function properly.");
		return 1;
	}
	openSystemPreferences();
	puts("Go to the prompt for disabling the Screen Time Passcode. When you're done, hit \"enter\" here.");
	getchar();
	openSystemPreferences();
	for (int i = 0; i < 10000; i++) {
		if (i % 3 && i) {
			now.tv_sec = (unsigned long)time(NULL) + 3600;
			now.tv_usec = 0;
			rc=settimeofday(&now, NULL);
			if (rc) {
				printf("settimeofday() failed, errno = %d\n",errno);
				return 1;
			}
		}
		if (i < 10)
			system("~/Documents/hitkey 000");
		else if (i < 100)
			system("~/Documents/hitkey 000");
		else if (i < 1000)
			system("~/Documents/hitkey 0");
		bzero(command, 23);
		strcpy(command, "~/Documents/hitkey ");
		sprintf(str, "%d", i);
		strcat(command, str);
		system(command);
	}
	return 0;
}
