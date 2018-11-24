#include "progressdialog.h"
#include "ui_progressdialog.h"


ProgressDialog::ProgressDialog(QThread* searchThread, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog),
    searchThread(searchThread)
{
    ui->setupUi(this);
    connect(ui->stopSearchButton, SIGNAL(clicked()), this, SLOT(stopSearch()));
    ui->progressBar->setValue(0);
    ui->label->setText("Scaning directory..");
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::stopSearch() {
    this->done(0);
    searchThread->requestInterruption();
}

void ProgressDialog::setRange(int max){
    ui->progressBar->setMaximum(max);
    ui->label->setText("Detecting same files..");
}

void ProgressDialog::update(int value) {
    ui->progressBar->setValue(value);
}
