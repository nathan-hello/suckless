static char *getcwd_by_pid(pid_t pid);
static pid_t getterm_pid(pid_t pid);

void
newterm(const Arg* a)
{
	switch (fork()) {
	case -1:
		die("fork failed: %s\n", strerror(errno));
		break;
	case 0:
		switch (fork()) {
		case -1:
			die("fork failed: %s\n", strerror(errno));
			break;
		case 0:
			chdir(getcwd_by_pid(getterm_pid(pid)));
			execlp("st", "./st", NULL);
			break;
		default:
			exit(0);
		}
	default:
		wait(NULL);
	}
}

static char *getcwd_by_pid(pid_t pid) {
	char buf[32];
	snprintf(buf, sizeof buf, "/proc/%d/cwd", pid);
	return realpath(buf, NULL);
}

static pid_t getterm_pid(pid_t pid) {
	char path[64], comm[32] = {0}, children[256] = {0};
	FILE *f;
	pid_t child = pid;

	snprintf(path, sizeof path, "/proc/%d/comm", pid);
	if ((f = fopen(path, "r")) == NULL)
		return pid;
	if (!fgets(comm, sizeof comm, f)) {
		fclose(f);
		return pid;
	}
	fclose(f);
	comm[strcspn(comm, "\n")] = '\0';
	if (strcmp(comm, "script") != 0)
		return pid;

	snprintf(path, sizeof path, "/proc/%d/task/%d/children", pid, pid);
	if ((f = fopen(path, "r")) == NULL)
		return pid;
	if (!fgets(children, sizeof children, f)) {
		fclose(f);
		return pid;
	}
	fclose(f);
	if (sscanf(children, "%d", &child) != 1)
		return pid;
	return child;
}
