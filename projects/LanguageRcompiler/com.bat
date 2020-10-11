Flex flex.l
Bison -d bison.y
gcc lex.yy.c bison.tab.c -o flex.exe