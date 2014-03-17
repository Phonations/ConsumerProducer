/**
* Copyright (C) 2012-2014 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef PRODUCER2_H
#define PRODUCER2_H

#include <QObject>
#include <QTime>

#include "myConstants.h"
#include "common.h"

class Producer2 : public QObject
{
	Q_OBJECT
public:
	explicit Producer2(QObject *parent = 0);

signals:
	void bufferFillCountChanged(int bCount);
	void producerCountChanged(int count);

	void finished();
	void error(QString err);

public slots:
	void process();
};

#endif // PRODUCER2_H
