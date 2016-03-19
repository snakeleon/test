#include <ncurses.h>
#include <string.h>

char *menu[]={" File "," Edit ", " Help "},
     *file[]={" New "," Open "," Save "," Save As "," Exit "},
     *edit[]={" Undo "," Redo "," Cut "," Copy "," Paste "},
     *help[]={" Commands.... "," About... "};

char buffer0[
