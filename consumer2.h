/**
* Copyright (C) 2012-2014 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef CONSUMER2_H
#define CONSUMER2_H

#include <QObject>
#include <QTime>

#include "myConstants.h"
#include "common.h"

class Consumer2 : public QObject
{
	Q_OBJECT
public:
	explicit Consumer2(QObject *parent = 0);

signals:
	void bufferFillCountChanged(int cCount);
	void consumerCountChanged(int count);

	void finished();
	void error(QString err);

public slots:
	void process();

};

#endif // CONSUMER2_H
