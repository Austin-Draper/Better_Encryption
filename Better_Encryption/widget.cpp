#include "widget.h"
#include "ui_widget.h"
#include "encrypt.h"


/*
 * TODO
 * after project is working...
 * 1. remove all unnecessary code
 * 2. optimize (such as remaking strings many times instead of just once
 * 3. make a list of possible improvements such as dynamic creation of vectors in github readme
 * 4. One such improvement is lines 235-286. Fails if first line of encrypted message is all numbers
 * 5. Line 451 using > 94 makes it so \n is nearly never different. Decryption doesn't print new lines if \n in vector 2 is different than vector 3
 * 6. Set up a "waiting" and a "complete" page after encrypt and decrypt are pressed
 */

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_encryptButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All files (*.*);;Text File (*.txt);;Word Document (*.doc);;Word Document XML (*.docx)");
    encrypt slave;//change name later
    slave.encryption(filename);
}

void Widget::on_decryptButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All files (*.*);;Text File (*.txt);;Word Document (*.doc);;Word Document XML (*.docx)");
    encrypt slave;//change name later
    slave.decryption(filename);
}
