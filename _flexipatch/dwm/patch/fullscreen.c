Layout *last_layout;
static int last_enablegaps;

void
fullscreen(const Arg *arg)
{
	int monocle_pos = 0;
	Client *c;
	if (selmon->showbar || last_layout == NULL) {
		for (monocle_pos = 0, last_layout = (Layout *)layouts; !last_layout->arrange || last_layout->arrange != &monocle; monocle_pos++, last_layout++ );
		for (last_layout = (Layout *)layouts; last_layout != selmon->lt[selmon->sellt]; last_layout++);

		/* Disable gaps */
		last_enablegaps = enablegaps;
		enablegaps = 0;

		/* Remove borders */
		for (c = selmon->clients; c; c = c->next)
			c->bw = 0;

		setlayout(&((Arg) { .v = &layouts[monocle_pos] }));
	} else {
		/* Restore gaps */
		enablegaps = last_enablegaps;

		/* Restore borders */
		for (c = selmon->clients; c; c = c->next)
			c->bw = borderpx;

		setlayout(&((Arg) { .v = last_layout }));
	}
	togglebar(arg);
}
