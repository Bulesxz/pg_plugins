/*-------------------------------------------------------------------------
 *
 * pg_wal_blocks.c
 *		Tracker of relation blocks touched by WAL records
 *
 * Copyright (c) 1996-2015, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *		pg_wal_blocks/pg_wal_blocks.c
 *
 *-------------------------------------------------------------------------
 */

#include "postgres_fe.h"
#include "getopt_long.h"

#define PG_WAL_BLOCKS_VERSION "0.1"

const char *progname;

/* Mode parameters */
static bool verbose = false;

static void
usage(const char *progname)
{
	printf("%s tracks relation blocks touched by WAL records.\n\n", progname);
	printf("Usage:\n %s [OPTION] [WAL_SEGMENT]...\n\n", progname);
	printf("Options:\n");
	printf("  -v             write some progress messages as well\n");
	printf("  -V, --version  output version information, then exit\n");
	printf("  -?, --help     show this help, then exit\n");
	printf("\n");
	printf("Report bugs to https://github.com/michaelpq/pg_plugins.\n");
}

int
main(int argc, char **argv)
{
	static struct option long_options[] = {
		{"help", no_argument, NULL, '?'},
		{"version", no_argument, NULL, 'V'},
		{"verbose", no_argument, NULL, 'v'},
		{NULL, 0, NULL, 0}
	};
	int		c;
	int		option_index;

	progname = get_progname(argv[0]);

	if (argc <= 1)
	{
		fprintf(stderr, "%s: no arguments specified\n", progname);
		exit(1);
	}

	/* Process command-line arguments */
	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0)
		{
			usage(progname);
			exit(0);
		}
		if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0)
		{
			puts("pg_wal_blocks " PG_WAL_BLOCKS_VERSION);
			exit(0);
		}
	}

	while ((c = getopt_long(argc, argv, "v", long_options, &option_index)) != -1)
	{
		switch (c)
		{
			case '?':
				fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
				exit(1);
			case 'v':
				verbose = true;
				break;
		}
	}

	if ((optind + 1) < argc)
	{
		fprintf(stderr,
				"%s: too many command-line arguments (first is \"%s\")\n",
				progname, argv[optind + 2]);
		exit(1);
	}

	/*
	 * TODO, extract WAL path and file name
	 * Leave if no start WAL file specified.
	 */

	exit(0);
}