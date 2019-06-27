#ifndef KBQUEUE_H
#define KBQUEUE_H
#define NULL ((void*)0)
#define MAX_NB_KEY 1024


char getkey();
int putkey(char c);


struct kbqueue
{
	int front, back;
	int reverse;
};


#endif