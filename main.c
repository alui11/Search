/* driver.c */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

#include <curses.h>

/* Functions */
void scroller();

void	    usage(const char *program_name, int status) {
	fprintf(stderr, "Usage: %s PATH [OPTIONS] [EXPRESSION]\n", program_name);
	fprintf(stderr, "\nOptions:\n");
	fprintf(stderr, "    -executable     File is executable or directory is searchable to user\n");
	fprintf(stderr, "    -readable       File readable to user\n");
	fprintf(stderr, "    -writable       File is writable to user\n\n");
	fprintf(stderr, "    -type [f|d]     File is of type f for regular file or d for directory\n\n");
	fprintf(stderr, "    -empty          File or directory is empty\n\n");
	fprintf(stderr, "    -empty          File or directory is empty\n\n");
	fprintf(stderr, "    -name  pattern  Base of file name matches shell pattern\n");
	fprintf(stderr, "    -path  pattern  Path of file matches shell pattern\n\n");
	fprintf(stderr, "    -perm  mode     File's permission bits are exactly mode (octal)\n");
	fprintf(stderr, "    -newer file     File was modified more recently than file\n\n");
	fprintf(stderr, "    -uid   n        File's numeric user ID is n\n");
	fprintf(stderr, "    -gid   n        File's numeric group ID is n\n");
	fprintf(stderr, "\nExpressions:\n\n");
	fprintf(stderr, "    -print          Display file path (default)\n");
	fprintf(stderr, "    -exec cmd {} ;  Execute command on path\n");
	exit(status);
}

/* Main Execution */

int	    main(int argc, char *argv[]) {

	Settings settings = {
		.access = 0,
		.uid = -1,
		.gid = -1,
	}; 

	if(argc==1){
		usage(argv[0], 1);
	}

	const char *path = argv[1];

	int argind = 1;
	if(argv[argind][0] != '-'){
		argind++;
	}
	while(argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
		char * arg = argv[argind++];
		if(streq(arg, "-executable")){
			settings.access |= X_OK;
		}else if(streq(arg, "-readable")){
			settings.access |= R_OK;
		}else if(streq(arg, "-writable")){
			settings.access |= W_OK;
		}else if(streq(arg, "-type")){
			settings.type = argv[argind++][0];
		}else if(streq(arg, "-empty")){
			settings.empty = true;
		}else if(streq(arg, "-name")){
			settings.name = argv[argind++];
		}else if(streq(arg, "-path")){
			settings.path = argv[argind++];
		}else if(streq(arg, "-perm")){
			int perm = (argv[argind][0] - '0')*64;
			perm += (argv[argind][1] - '0')*8;
			perm += (argv[argind++][2] - '0');
			settings.perm = perm;
		}else if(streq(arg, "-newer")){
			time_t time = get_mtime(argv[argind++]);
			settings.newer = time;
		}else if(streq(arg, "-uid")){
			settings.uid = atoi(argv[argind++]);
		}else if(streq(arg, "-gid")){
			settings.gid = atoi(argv[argind++]);
		}else if(streq(arg, "-print")){
			settings.print = true;
		}else if(streq(arg, "-exec")){
			int exec_argc = 0;
			char *exec_argv[BUFSIZ];
			while(strcmp(argv[argind], ";")){
				exec_argv[exec_argc] = argv[argind];
				exec_argc++;
				argind++;
			}
			settings.exec_argc = exec_argc;
			settings.exec_argv = exec_argv;
		}else if(streq(arg, "-help")){
			usage(argv[0], 0);
		}else if(streq(arg, "-tswift")){
			scroller();
		}else{
			usage(argv[0], 1);
		}
	}

	const Settings *s = &settings;
	//printf("%s\n", path);
	search(path, s);

	return EXIT_SUCCESS;
}

void scroller()
{

	char *text = "Hello, how are you? ";
	char *scroll;
	int text_length;

	int i, max_x, max_y;

	// Get text length
	text_length = strlen(text);

	// Initialize screen for ncurses
	initscr();
	// Don't show cursor
	curs_set(0);
	// Get terminal dimensions
	//   getmaxyx(stdscr, max_y, max_x);
	// Clear the screen
	clear();

	getmaxyx(stdscr, max_y, max_x);
	scroll = malloc(2 * max_x + 1);

	for (i=0; i< 2*max_x; i++) {
		scroll[i] = text[i % text_length];
	}

	scroll[2*max_x - 1]='\0';


	// Scroll text back across the screen
	for (i=0; i < 10000; i++) {

		mvaddnstr(0,0,&scroll[i%max_x], max_x);
		refresh();
		usleep(20000);
	}
	// Wait for a keypress before quitting
	getch();

	endwin();

}
