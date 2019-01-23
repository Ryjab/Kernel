#include "kbqueue.h"

char mykbbuff[MAX_NB_KEY];
struct kbqueue mykbqueue; 


void init_mykbqueue()
{
	mykbqueue.front = -1;
	mykbqueue.back = 0;
	mykbqueue.reverse = 0;
}

int enkbqueue(char c)
{
	if (mykbqueue.reverse == 0)
	{
		if (mykbqueue.front+1 < MAX_NB_KEY)
		{
			mykbqueue.front++;
			mykbbuff[mykbqueue.front] = c; 
			return 1;
		}
		else if (mykbqueue.back > 0)
		{
			mykbqueue.front = 0;
			mykbbuff[mykbqueue.front] = c;
			mykbqueue.reverse = 1;
			return 1;
		}
		else
		{
			//buffer full
			return 0;
		}
	}
	else
	{
		if (mykbqueue.front + 1 < mykbqueue.back)
		{
			mykbqueue.front++;
			mykbbuff[mykbqueue.front] = c;
			return 1;
		}
		else
		{
			//buffer full
			return 0;
		}
	}
}

char dekbqueue()
{
	if(mykbqueue.back < MAX_NB_KEY)
	{
		char retour = mykbbuff[mykbqueue.back];
		mykbqueue.back++;
		return retour;
	}
	else
	{
		mykbqueue.back = 0;
		mykbqueue.reverse = 0;
		return mykbbuff[mykbqueue.back];
	}
}


int putkey(char c)
{
	return enkbqueue(c);
}

char getkey()
{
	return dekbqueue();
}