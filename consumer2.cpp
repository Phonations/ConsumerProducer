/**
* Copyright (C) 2012-2014 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include "consumer2.h"

Consumer2::Consumer2(QObject *parent) :
	QObject(parent)
{
}

void Consumer2::process()
{
	for (int i = 0; i < DataSize; ++i) {
		usedBytes.acquire();
		//fprintf(stderr, "%c\n", buffer[i % BufferSize]);
		freeBytes.release();
		emit bufferFillCountChanged(usedBytes.available());
		emit consumerCountChanged(i);
	}
	fprintf(stderr, "\n");
}
