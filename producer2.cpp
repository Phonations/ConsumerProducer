/**
* Copyright (C) 2012-2014 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include "producer2.h"

Producer2::Producer2(QObject *parent) :
	QObject(parent)
{
}

void Producer2::process()
{
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	for (int i = 0; i < DataSize; ++i) {
		freeBytes.acquire();
		buffer[i % BufferSize] = "ACGT"[(int)qrand() % 4];
		usedBytes.release();
		if(i % 20 == 0)
		emit bufferFillCountChanged(usedBytes.available());
		emit producerCountChanged(i);
	}
}
