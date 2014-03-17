#ifndef CONPRODDIALOG_H
#define CONPRODDIALOG_H

#include <QDialog>
#include "consumer2.h"
#include "producer2.h"

#include <QSemaphore>
#include <QThread>


namespace Ui {
class ConProdDialog;
}

class ConProdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConProdDialog(QWidget *parent = 0);
    ~ConProdDialog();

public slots:
    void onBufferValueChanged(int);
    void onProducerValueChanged(int);
    void onConsumerValueChanged(int);
	void errorString(QString);

private slots:
    void on_startButton_clicked();

private:
    Ui::ConProdDialog *ui;
	Producer2 *mProducer;
	Consumer2 *mConsumer;
	QThread* thread1;
	QThread* thread2;

	QSemaphore * freeBytes;
	QSemaphore * usedBytes;

	int _buffSize;
	char * _buffer;

	int dataSize;
};

#endif // CONPRODDIALOG_H
