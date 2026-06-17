typedef struct {
	const char *name;
	char *value;
} ColorSpec;

static int
valid_color(const char *s)
{
	int i;

	if (s == NULL || strlen(s) != 7 || s[0] != '#')
		return 0;

	for (i = 1; i < 7; i++) {
		if ((s[i] >= '0' && s[i] <= '9') ||
		    (s[i] >= 'a' && s[i] <= 'f') ||
		    (s[i] >= 'A' && s[i] <= 'F'))
			continue;
		return 0;
	}

	return 1;
}

static void
setcolor(const Arg *arg)
{
	static ColorSpec specs[] = {
		{ "normfgcolor", normfgcolor },
		{ "normbgcolor", normbgcolor },
		{ "normbordercolor", normbordercolor },
		{ "normfloatcolor", normfloatcolor },
		{ "selfgcolor", selfgcolor },
		{ "selbgcolor", selbgcolor },
		{ "selbordercolor", selbordercolor },
		{ "selfloatcolor", selfloatcolor },
		{ "titlenormfgcolor", titlenormfgcolor },
		{ "titlenormbgcolor", titlenormbgcolor },
		{ "titlenormbordercolor", titlenormbordercolor },
		{ "titlenormfloatcolor", titlenormfloatcolor },
		{ "titleselfgcolor", titleselfgcolor },
		{ "titleselbgcolor", titleselbgcolor },
		{ "titleselbordercolor", titleselbordercolor },
		{ "titleselfloatcolor", titleselfloatcolor },
		{ "tagsnormfgcolor", tagsnormfgcolor },
		{ "tagsnormbgcolor", tagsnormbgcolor },
		{ "tagsnormbordercolor", tagsnormbordercolor },
		{ "tagsnormfloatcolor", tagsnormfloatcolor },
		{ "tagsselfgcolor", tagsselfgcolor },
		{ "tagsselbgcolor", tagsselbgcolor },
		{ "tagsselbordercolor", tagsselbordercolor },
		{ "tagsselfloatcolor", tagsselfloatcolor },
		{ "hidnormfgcolor", hidnormfgcolor },
		{ "hidnormbgcolor", hidnormbgcolor },
		{ "hidselfgcolor", hidselfgcolor },
		{ "hidselbgcolor", hidselbgcolor },
		{ "urgfgcolor", urgfgcolor },
		{ "urgbgcolor", urgbgcolor },
		{ "urgbordercolor", urgbordercolor },
		{ "urgfloatcolor", urgfloatcolor },
	};
	char specbuf[64];
	char *name;
	char *value;
	unsigned int i;

	if (arg == NULL || arg[0].v == NULL)
		return;

	snprintf(specbuf, sizeof(specbuf), "%s", (const char *)arg[0].v);
	name = strtok(specbuf, "=");
	value = strtok(NULL, "=");
	if (name == NULL || value == NULL || !valid_color(value))
		return;

	for (i = 0; i < LENGTH(specs); i++) {
		if (strcmp(specs[i].name, name) == 0) {
			snprintf(specs[i].value, 8, "%s", value);
			reload_colors();
			return;
		}
	}
}
