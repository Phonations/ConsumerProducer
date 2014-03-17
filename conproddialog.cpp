#include "conproddialog.h"
#include "ui_conproddialog.h"
#include "QDebug"


ConProdDialog::ConProdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConProdDialog)
{
    ui->setupUi(this);

	dataSize = 1000;
	_buffSize = 8192;
	_buffer = new char [_buffSize];
	freeBytes = new QSemaphore(100);
	usedBytes = new QSemaphore(100);

    // progress bar range setup
	ui->producerProgressBar->setRange(0, dataSize);
	ui->consumerProgressBar->setRange(0, dataSize);
	ui->bufferProgressBar->setRange(0, 100);

	mProducer = new Producer2(freeBytes, usedBytes, _buffer, _buffSize, dataSize);
	mConsumer = new Consumer2(freeBytes, usedBytes, _buffer, _buffSize, dataSize);


	thread1 = new QThread();
	thread2 = new QThread();
	mProducer->moveToThread(thread1);
	connect(mProducer, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(thread1, SIGNAL(started()), mProducer, SLOT(process()));
	connect(mProducer, SIGNAL(finished()), thread1, SLOT(quit()));
	connect(mProducer, SIGNAL(finished()), mProducer, SLOT(deleteLater()));
	connect(thread1, SIGNAL(finished()), thread1, SLOT(deleteLater()));

	mConsumer->moveToThread(thread2);
	connect(mConsumer, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(thread2, SIGNAL(started()), mConsumer, SLOT(process()));
	connect(mConsumer, SIGNAL(finished()), thread2, SLOT(quit()));
	connect(mConsumer, SIGNAL(finished()), mConsumer, SLOT(deleteLater()));
	connect(thread2, SIGNAL(finished()), thread2, SLOT(deleteLater()));



    // connect signal/slot for the buffer progress bar
	connect(mConsumer, SIGNAL(bufferFillCountChanged(int)),
			  this, SLOT(onBufferValueChanged(int)));
    connect(mProducer, SIGNAL(bufferFillCountChanged(int)),
              this, SLOT(onBufferValueChanged(int)));

    // connect signal/slot for consumer/producer progress bar
    connect(mConsumer, SIGNAL(consumerCountChanged(int)),
              this, SLOT(onConsumerValueChanged(int)));
    connect(mProducer, SIGNAL(producerCountChanged(int)),
              this, SLOT(onProducerValueChanged(int)));
}

ConProdDialog::~ConProdDialog()
{
	delete freeBytes;
	delete usedBytes;
	delete _buffer;
    delete ui;
}

void ConProdDialog::onBufferValueChanged(int bCount)
{
    ui->bufferProgressBar->setValue(bCount);
}

void ConProdDialog::onProducerValueChanged(int pCount)
{
    ui->producerProgressBar->setValue(pCount);
}

void ConProdDialog::onConsumerValueChanged(int cCount)
{
	ui->consumerProgressBar->setValue(cCount);
}

void ConProdDialog::errorString(QString str)
{
	qDebug() << "-----------------------";
	qDebug() << "Erreur : " << str;
	qDebug() << "-----------------------";
}

// start button clicked
void ConProdDialog::on_startButton_clicked()
{
    // disable the start button
    ui->startButton->setEnabled(false);

	// threads start
	thread1->start();
	thread2->start();

}

