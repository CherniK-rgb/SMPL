#ifndef SMPL_H
#define SMPL_H

#include <QWidget>
#include <QUdpSocket>
#include <QMessageBox>
#include <QPushButton>
#include <QIcon>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QTextEdit>

namespace Ui { class SMPL; }

class SMPL : public QWidget
{
    Q_OBJECT
public:
   explicit SMPL(QWidget *parent = nullptr);
    ~SMPL();
    QUdpSocket* socket; // socket
    quint16 port=49159; // port of server
    QString Nick; // Nick from client
    QString texts; //message from Client
    quint16 flag,flagQuit;
    QHostAddress HostIP=QHostAddress::LocalHost;

public slots:
    void SockReady();// socket ready
private slots:

    void on_pushButton_clicked(); // button clicked

    void on_lineEdit_2_textChanged(const QString &arg1);// lineEdit_2 changed text

    void on_textEdit_2_textChanged(); // textEdit_2 changed text

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    Ui::SMPL *ui;
};
#endif // SMPL_H
