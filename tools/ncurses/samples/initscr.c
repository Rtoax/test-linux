#include <ncurses.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *thread_win(void *arg)
{
	WINDOW *warn_win = newwin(10, 20, 2, 2);
	box(warn_win, 0, 0);

	for (int i = 0; i < 3; i++) {
		mvwprintw(warn_win, 1, 1, "New Window %d", i);
		wrefresh(warn_win);
		sleep(1);
	}

	werase(warn_win);
	wrefresh(warn_win);
	delwin(warn_win);

	sleep(3);

	return NULL;
}

int main(void)
{
	pthread_t warn_thread;

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	pthread_create(&warn_thread, NULL, thread_win, NULL);

	for (int i = 0; i < 3; i++) {
		printw("Hello World %d\n", i);
		refresh();
		sleep(1);
	}

	pthread_join(warn_thread, NULL);

	endwin();
	return 0;
}
