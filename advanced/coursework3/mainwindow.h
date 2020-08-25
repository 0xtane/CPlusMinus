#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtWidgets>
#include <QtNetwork>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_connectButton_clicked();

    void on_disconnectButton_clicked();

    void on_computeButton_clicked();

    void on_exitButton_clicked();

    void onResponseReceived();

    void OnFunctionOptionChanged(const QString &functionname);

private:
    Ui::MainWindow *ui;
    QLocalSocket *mysocket;
    QString pipeaddress = QString("\\\\.\\pipe\\ICS0025");
};
#endif // MAINWINDOW_H
