#include "smpl.h"
#include "ui_smpl.h"
SMPL::SMPL(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SMPL) // inicilization of UI
{
    ui->setupUi(this); // setting ui to current window
    ui->label_4->hide();
    ui->lineEdit_3->hide();
    ui->pushButton_5->hide();
    ui->textEdit->hide(); // hide textEdit
    ui->textEdit_2->hide(); // hide textEdit_2
    ui->pushButton_2->hide(); // hide pushButton_2
    socket = new QUdpSocket(this); // creating socket
    connect(socket,SIGNAL(readyRead()),this,SLOT(SockReady()));
    socket->bind(HostIP,port);
    SMPL::ui->pushButton_2->setIcon(QIcon(":/resources/img/enter.tuch.png"));//icon enter
    SMPL::ui->pushButton->setIcon(QIcon(":resources/img/connect1.png"));//icon enter
    ui->pushButton->setShortcut(Qt::Key_Return);

}
SMPL::~SMPL() // destructor
{
    delete ui;
}
void SMPL :: SockReady() // function if socket is ready
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(),buffer.size(),&sender,&senderPort);
    if(buffer=="\n")
    {
        ui->pushButton->hide();// here hiding and showing some ui elements
        ui->lineEdit->hide();
        ui->label->hide();
        ui->label_2->hide();
        ui->lineEdit_2->hide();
        ui->pushButton_2->show();
        ui->textEdit->show();
        ui->textEdit_2->show();
        ui->textEdit->isReadOnly();
        ui->textEdit->insertPlainText("You are connected. Welcome:)\n");
        ui->label_4->hide();
        ui->lineEdit_3->hide();
        ui->pushButton_5->hide();
        ui->pushButton_3->hide();
        ui->pushButton_2->setShortcut(Qt::Key_Return);
        ui->pushButton_2->setShortcut(Qt::Key_Enter);
    }
    else
    ui->textEdit->insertPlainText(buffer.data());
}
void SMPL::on_pushButton_clicked() // if pushButton clicked function
{
    Nick = ui->lineEdit_2->text(); // move text from lineEdit_2 to Nick
    port = ui->lineEdit->text().toInt();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->pushButton->setEnabled(false); // off the button(unclickable)
    socket->writeDatagram("\n",1,HostIP,port);

}

void SMPL::on_lineEdit_2_textChanged(const QString &arg1) //if text on lineEdit_2 changed function
{
    ui->pushButton->setEnabled(true);// make the button clickable
}

void SMPL::on_textEdit_2_textChanged() // if text on textiEdit_2 changed
{
    if(ui->textEdit_2->toPlainText() != "");
    ui->pushButton_2->setEnabled(true); // make the pushButton_2 clickable
}

void SMPL::on_pushButton_2_clicked()
{
    SMPL::ui->pushButton_2->setIcon(QIcon(":/resources/img/enter.tuch.png"));  //icon enter
    QByteArray data;
    texts = Nick + ":" + ui->textEdit_2->toPlainText() + "\n"; // forming the message with format : Nick:message , message taked from textEdit_2
    data.append(texts);
    socket->writeDatagram(data,HostIP,port);
    ui->textEdit_2->clear();
    ui->pushButton_2->setEnabled(false);
}

void SMPL::on_pushButton_3_clicked()
{
    if (flag!=1)
    {
        ui->label_4->show();
        ui->lineEdit_3->show();
        ui->pushButton_5->show();
        flag=1;
    }
    else
    {
        ui->label_4->hide();
        ui->lineEdit_3->hide();
        ui->pushButton_5->hide();
        flag=0;
    }
}

void SMPL::on_pushButton_4_clicked()
{
    SMPL::close();
}

void SMPL::on_pushButton_5_clicked()
{
    if(ui->lineEdit_3->text()!="")
    {
        HostIP=QHostAddress(ui->lineEdit_3->text());
    }
    ui->label_4->hide();
    ui->lineEdit_3->hide();
    ui->pushButton_5->hide();
    flag=0;
}
void SMPL::keyPressEvent(QKeyEvent *event)
{
   if(event->key() == Qt::Key_Escape)
   {
        socket->writeDatagram("Code:1234",9,HostIP,port);
        flagQuit=1;
        SMPL::close();
   }
   else
   if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
   {
       SMPL::ui->pushButton_2->setIcon(QIcon(":/resources/img/enter.tuch.png"));  //icon enter
       QByteArray data;
       texts = Nick + ":" + ui->textEdit_2->toPlainText() + "\n"; // forming the message with format : Nick:message , message taked from textEdit_2
       data.append(texts);
       socket->writeDatagram(data,HostIP,port);
       ui->textEdit_2->clear();
       ui->pushButton_2->setEnabled(false);
   }
}
void SMPL::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if(flagQuit!=1)
    {
    socket->writeDatagram("Code:1234",9,HostIP,port);
    }
    event->accept();
}

