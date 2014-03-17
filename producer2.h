/**
* Copyright (C) 2012-2014 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef PRODUCER2_H
#define PRODUCER2_H

#include <QObject>
#include <QTime>
#include <QSemaphore>

class Producer2 : public QObject
{
	Q_OBJECT
public:
	explicit Producer2(QSemaphore * freeBytes, QSemaphore * usedBytes, char * buffer, int buffSize, int dataSize, QObject *parent = 0);

signals:
	void bufferFillCountChanged(int bCount);
	void producerCountChanged(int count);

	void finished();
	void error(QString err);

public slots:
	void process();
private:
	char * _buffer;
	int _buffSize;
	int _dataSize;

	QSemaphore * _freeBytes;
	QSemaphore * _usedBytes;

};

#endif // PRODUCER2_H
