#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_OUTPUT 8192

static void
show_status(void)
{
    FILE *fp;
    char buffer[MAX_OUTPUT];
    size_t n;
    int row;

    clear();
    mvprintw(0, 2, "obnmtui - OpenBSD Network Manager");
    mvprintw(2, 2, "Interface status");
    mvhline(3, 2, ACS_HLINE, COLS > 44 ? 40 : COLS - 4);

    fp = popen("/sbin/ifconfig -a", "r");
    if (fp == NULL) {
        mvprintw(5, 2, "Unable to execute /sbin/ifconfig.");
        mvprintw(LINES - 2, 2, "Press r to refresh, q to quit");
        refresh();
        return;
    }

    n = fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[n] = '\\0';
    (void)pclose(fp);

    mvprintw(5, 2, "Current interfaces (excerpt):");
    row = 7;
    {
        char *line = buffer;
        while (*line != '\\0' && row < LINES - 3) {
            char *end = line;
            while (*end != '\\0' && *end != '\\n')
                end++;
            {
                char saved = *end;
                *end = '\\0';
                mvprintw(row++, 2, "%.*s", COLS > 4 ? COLS - 4 : 1, line);
                *end = saved;
            }
            if (*end == '\\0')
                break;
            line = end + 1;
        }
    }

    mvprintw(LINES - 2, 2, "Press r to refresh, q to quit");
    refresh();
}

int
main(void)
{
    int ch;

    if (initscr() == NULL)
        return EXIT_FAILURE;

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    for (;;) {
        show_status();
        ch = getch();

        if (ch == 'q' || ch == 'Q')
            break;
        if (ch == 'r' || ch == 'R')
            continue;
    }

    endwin();
    return EXIT_SUCCESS;
}
