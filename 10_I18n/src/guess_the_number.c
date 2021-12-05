#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int guess_the_number(int start, int end) {
    if (end == start) {
        return end;
    }
    int half = start + ((end - start + 1) / 2) - 1;
    printf(_("Is the number greater than %d? (yes/no)\n"), half);
    char answer[10];
    fgets(answer, 10, stdin);
    if (!strcmp(answer, _("yes\n"))) {
        return guess_the_number(half + 1, end);
    }
    if (!strcmp(answer, _("no\n"))) {
        return guess_the_number(start, half);
    }
    printf(_("I didn't understand your answer \"%s\". Try again\n"), answer);
    return guess_the_number(start, end);
}

int main(int argc, char* argv[]) {
    setlocale (LC_ALL, "");
	bindtextdomain ("guess_the_number", LOCALE_PATH);
	textdomain ("guess_the_number");

    printf(_("Think a number from 1 to 100\n"));
	printf(_("I know what number you made up! This is %d\n"), guess_the_number(1, 100));
    return 0;
}