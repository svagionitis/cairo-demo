#include "cairo-demo.h"
#include "cairo-draw.h"
#include "cairo-operators.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
help(const char *name)
{
	fprintf(stdout,
		"usage: %s [options]\n"
		" -h, --help     display this help\n"
		" -o <op>, --operator=<op>\n"
		"                draw the specified operator demonstration\n"
		" -p <file>, --png=<file>\n"
		"                draw the demonstration to a PNG file\n"
		" -v, --version  output version information and exit\n",
		name);
}

int
main(int argc, char **argv)
{
	int i, opt;
	cairo_demo_t *demo;
	const char *image = NULL, *png = NULL;
	cairo_demo_draw_function_t draw = NULL;
	struct option options[] = {
		{ "help", no_argument, NULL, 'h' },
		{ "image", required_argument, NULL, 'i' },
		{ "operator", required_argument, NULL, 'o' },
		{ "png", required_argument, NULL, 'p' },
		{ "version", no_argument, NULL, 'v' },
		{ NULL, no_argument, NULL, '\0' }
	};
	const char *sopts = ":hi:o:p:v";
	while (-1 != (opt = getopt_long(argc, argv, sopts, options, &i))) {
		switch (opt) {
		case 'h': /* help */
			help(argv[0]);
			return EXIT_SUCCESS;
		case 'i': /* image */
			image = optarg;
			break;
		case 'o': /* operator */
			draw = cairo_operators_get_function(optarg);
			break;
		case 'p': /* png */
			png = optarg;
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
	demo = cairo_demo_new(argc, argv, NAME, 256, 256);
	if (!demo) {
		exit(EXIT_FAILURE);
	}
	if (draw) {
		cairo_demo_set_draw_function(demo, draw);
	}
	if (image) {
		cairo_demo_set_image(demo, image);
	}
	if (png) {
		cairo_demo_set_png(demo, png);
	}
	exit(cairo_demo_run(demo));
}
