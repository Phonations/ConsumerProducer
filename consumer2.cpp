/**
* Copyright (C) 2012-2014 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include <QDebug>
#include <QThread>
#include "consumer2.h"

Consumer2::Consumer2(QSemaphore *freeBytes, QSemaphore *usedBytes, char *buffer, int buffSize, int dataSize, QObject *parent) :
	QObject(parent)
{
	_freeBytes = freeBytes;
	_usedBytes = usedBytes;
	_buffer = buffer;
	_buffSize = buffSize;
	_dataSize = dataSize;
}


void Consumer2::process()
{
	for (int i = 0; i < _dataSize; ++i) {
		_usedBytes->acquire();
		fprintf(stderr, "<= %c : %d\n", _buffer[i % _buffSize], i);
		QThread::msleep(1);
		_freeBytes->release();
		emit bufferFillCountChanged(_usedBytes->available());
		emit consumerCountChanged(i);
	}
	fprintf(stderr, "\n");
}
