#include <ncurses.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t ncurses_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_win(void *arg)
{
	pthread_mutex_lock(&ncurses_mutex);

	WINDOW *warn_win = newwin(10, 20, 2, 2);
	box(warn_win, 0, 0);

	pthread_mutex_unlock(&ncurses_mutex);

	for (int i = 0; i < 3; i++) {
		pthread_mutex_lock(&ncurses_mutex);
		mvwprintw(warn_win, 1, 1, "New Window %d", i);
		wrefresh(warn_win);
		pthread_mutex_unlock(&ncurses_mutex);
		sleep(1);
	}

	pthread_mutex_lock(&ncurses_mutex);
	werase(warn_win);
	wrefresh(warn_win);
	delwin(warn_win);
	pthread_mutex_unlock(&ncurses_mutex);

	sleep(3);

	return NULL;
}

int main(void)
{
	pthread_t warn_thread;

	pthread_mutex_lock(&ncurses_mutex);
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	pthread_mutex_unlock(&ncurses_mutex);

	pthread_create(&warn_thread, NULL, thread_win, NULL);

	for (int i = 0; i < 3; i++) {
		pthread_mutex_lock(&ncurses_mutex);
		printw("Hello World %d\n", i);
		refresh();
		pthread_mutex_unlock(&ncurses_mutex);
		sleep(1);
	}

	pthread_join(warn_thread, NULL);

	pthread_mutex_lock(&ncurses_mutex);
	endwin();
	pthread_mutex_unlock(&ncurses_mutex);
	return 0;
}
