/*
 * Pomodoro time management in terminal 
 * Programmed by Orange Hwang 
 * email: whiteinsalt@gmail.com
 * version: 0.6
 * Updated: with Ncurses.h
 * Bugs: 00:01... 00:00 not printed
 * date: 2nd June 2023
 * Fixed: 25th September 2023
 */
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

/*
 * work means 25 minutes to work.
 * rest means 5 minutes to take a rest.
 * big_rest means 30 minutes to take a rest.
 */
enum { work = 25, rest = 5, big_rest = 30 };

/*
 * Timer counts every second displaying the timer.
 */
void Timer(int minutesToWork, char* mesg)
{
	int minutes = minutesToWork, seconds = 0;
	char* message = mesg;

	mvprintw(2, 0, "%d minutes to %s now.\n",
		minutes, (minutes == work ?
		          "work" : (minutes == big_rest ?
			            "take a big rest" :
				    "take a little rest")));

	while (minutes > 0 || seconds > 0) {

		/* Displays the timer */
		mvprintw(5, 5, "\t%02d:%02d \t%s\n\n\n",
		         minutes, seconds, message);
		refresh();
		sleep(1);
		--seconds;

		if (seconds < 0) {
			--minutes;
			seconds = 59;
		}
	}
}

/*
 * pomodoro main
 */
void pomodoro(void)
{
	int minutes = work,
	    restMinutes = rest,
	    specialRestMinutes = big_rest,
	    number = 0;
	char messageToWork[]    = " It will be valuable for the glory of God.",
	     messageToRest[]    = " Be peace in God.",
	     messageToBigRest[] = " Have a Big resting.",
	     input[10];

	/* Ncurses starts here. */
	initscr();
	mvprintw(0, 0, "Pomodoro time management system!\n");

	for (number = 0; number < 5; ++number) {

		/* Let's go to work */
		mvprintw(3, 0, "Ready to work now?\n");
		mvprintw(3, 0, "Input(go or rest or big): ");
		refresh();
		getstr(input);

		if (strcmp(input, "go") == 0) {
			/* for working for work min */
			Timer(minutes, messageToWork);
		} else if (strcmp(input, "rest") == 0) {
			/* for resting for rest min */
			Timer(restMinutes, messageToRest);
		} else if (strcmp(input, "big") == 0) {
			/* for resting for big_rest min */
			Timer(specialRestMinutes, messageToBigRest); 
		} else {
			break;
		}
	}

	/* Ncurses ends here */
	endwin();
}

int main(int argc, char** argv)
{
	pomodoro();
	return 0;
}
