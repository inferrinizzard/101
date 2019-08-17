# //Sean Song CMPS101 pa1 25/6/19 README README
#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 2
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

Test : Test.o List.o
	gcc -o Test Test.o List.o

Test.o : Test.c List.h
	gcc -c -std=c99 -Wall Test.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

valgrind :
	valgrind ListClient

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

submit :
	submit cmps101-pt.u19 pa1 Lex.c List.c List.h ListClient.c Makefile README
 