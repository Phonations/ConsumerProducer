/**
* Copyright (C) 2012-2014 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <QDebug>

#include "producer2.h"

Producer2::Producer2(QSemaphore *freeBytes, QSemaphore *usedBytes, char *buffer, int buffSize, int dataSize, QObject *parent) :
	QObject(parent)
{
	_freeBytes = freeBytes;
	_usedBytes = usedBytes;
	_buffer = buffer;
	_buffSize = buffSize;
	_dataSize = dataSize;
}



void Producer2::process()
{
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	for (int i = 0; i < _dataSize; ++i) {
		_freeBytes->acquire();
		_buffer[i % _buffSize] = "ACGT"[(int)qrand() % 4];
		fprintf(stderr, "=> %c : %d\n", _buffer[i % _buffSize], i);
		_usedBytes->release();
		if(i % 20 == 0)
		emit bufferFillCountChanged(_usedBytes->available());
		emit producerCountChanged(i);
	}
}
