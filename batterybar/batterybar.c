#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "config.h"

static volatile sig_atomic_t running = 1;

static void
on_signal(int sig)
{
	(void)sig;
	running = 0;
}

static int
read_capacity(void)
{
	FILE *fp;
	int capacity = -1;

	fp = fopen(BATTERY_CAPACITY_PATH, "r");
	if (fp == NULL)
		return -1;

	if (fscanf(fp, "%d", &capacity) != 1)
		capacity = -1;

	fclose(fp);
	return capacity;
}

static int
run_setcolor(const char *name, const char *value)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		return -1;

	if (pid == 0) {
		char spec[96];

		snprintf(spec, sizeof(spec), "%s=%s", name, value);
		execlp("dwm-msg", "dwm-msg", "run_command", "setcolor",
		       spec, (char *)NULL);
		_Exit(127);
	}

	(void)waitpid(pid, &status, 0);
	return WIFEXITED(status) && WEXITSTATUS(status) == 0 ? 0 : -1;
}

static int
set_bar_color(int low)
{
	const char *color = low ? BAR_LOW_COLOR : BAR_NORMAL_COLOR;
	return run_setcolor("titleselbgcolor", color);
}

int
main(void)
{
	int last_low = -1;

	signal(SIGINT, on_signal);
	signal(SIGTERM, on_signal);

	while (running) {
		int capacity = read_capacity();
		int low = capacity >= 0 && capacity < LOW_BATTERY_PERCENT;

		if (low != last_low) {
			(void)set_bar_color(low);
			last_low = low;
		}

		sleep(POLL_INTERVAL_SECONDS);
	}

	return 0;
}
