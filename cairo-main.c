#include "cairo-demo.h"
#include "cairo-operators.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void
draw(cairo_t *cr, int width, int height);

void
help(const char *name)
{
	fprintf(stdout,
		"usage: %s [options]\n"
		" -h, --help     display this help\n"
		" -o <op>, --operator=<op>\n"
		"                draw the specified operator demonstration\n"
		" -v, --version  output version information and exit\n",
		name);
}

int
main(int argc, char **argv)
{
	int i, opt;
	bool png = false;
	cairo_demo_t *demo;
	cairo_demo_draw_function_t draw = draw;
	struct option options[] = {
		{ "help", no_argument, NULL, 'h' },
		{ "operator", required_argument, NULL, 'o' },
		{ "png", no_argument, NULL, 'p' },
		{ "version", no_argument, NULL, 'v' },
		{ NULL, no_argument, NULL, '\0' }
	};
	const char *sopts = ":ho:v";
	while (-1 != (opt = getopt_long(argc, argv, sopts, options, &i))) {
		switch (opt) {
		case 'h': /* help */
			help(argv[0]);
			return EXIT_SUCCESS;
		case 'o': /* operator */
			draw = cairo_operators_get_function(optarg);
			break;
		case 'p': /* png */
			png = true;
			break;
		case 'v': /* version */
			fprintf(stdout, "%s/%s\n", NAME, VERSION);
			return EXIT_SUCCESS;
		case ':': /* unrecognized */
		default:
			fprintf(stderr, "try `%s --help' for more "
					"information\n", argv[0]);
			return EXIT_FAILURE;
		}
	}
	demo = cairo_demo_new(NAME, 256, 256);
	if (!demo) {
		exit(EXIT_FAILURE);
	}
	cairo_demo_set_draw_function(demo, draw);
	exit(cairo_demo_run(demo));
}