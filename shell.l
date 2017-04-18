/* lexical Analyser for the shell */

%{
#include <string.h>
#inlcude "y.tab.h"
%}

%%
\n { retutn NEWLINE; }
[ \t] { //do nothing. Discard the spaces and tabs}
">" {return GREAT;}
"<" {return LESS;}
">>" {return GREATGREAT;}
">&" {return GREATAMPERSANT;}
"|" {return PIPE;}
"&" {return AMPERSANT;}
[^ \t\n][^ \t\n]* {yyval.string_val = strdup(yytext); return WORD;} /* Assuming that the name has only alpha chars */
. {return NOTOKEN;}
%%