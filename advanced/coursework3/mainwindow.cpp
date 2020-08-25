#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mysocket = new QLocalSocket(this);

    QStringList functionNames;
    functionNames<< "Sine integral" << "Cosine integral" << "Bessel function" << "Fresnel integral S" << "Fresnel integral C";
    for (int i =0;i<5;i++)     {
         ui->functionCombo->addItem(functionNames[i]);
    }

    ui->disconnectButton->setEnabled(false);
    ui->computeButton->setEnabled(false);
    ui->Order->setEnabled(false);


    //connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(on_connectButton_clicked()));
    //connect(ui->exitButton, SIGNAL(clicked()),this,QApplication::exit());
    connect(mysocket, SIGNAL(readyRead()), this, SLOT(onResponseReceived()));

    connect(ui->functionCombo, SIGNAL(currentTextChanged(const QString &)), this, SLOT(OnFunctionOptionChanged(const QString &)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


/////////////////////////////////////////////////////

QByteArray sendSin(double dxstart,double dxend,int npoints) {
    int nBytes = 52;
    QByteArray bytearr;
    char * sineCommand = (char *) "Sine integral\0";

    for(int i=0; i<4; i++){
        bytearr.append(nBytes<<(8*i));
    }

    for(int i=0; i<13; i++){
        bytearr.append(sineCommand[i]);
        bytearr.append('\0');
    }

    bytearr.append('\0');

    bytearr.append('\0');


    char * tmparr = (char *)&dxstart;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    tmparr = (char *)&dxend;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    for(unsigned int i=0; i<sizeof(int); i++){
    bytearr.append(npoints<<(8*i));
    }

    return bytearr;
}

QByteArray sendCos(double dxstart,double dxend,int npoints) {
    int nBytes = 56;
    QByteArray bytearr;
    char * cosineCommand = (char *) "Cosine integral\0";

    for(int i=0; i<4; i++){
        bytearr.append(nBytes<<(8*i));
    }

    for(int i=0; i<15; i++){
        bytearr.append(cosineCommand[i]);
        bytearr.append('\0');
    }

    bytearr.append('\0');

    bytearr.append('\0');


    char * tmparr = (char *)&dxstart;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    tmparr = (char *)&dxend;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    for(unsigned int i=0; i<sizeof(int); i++){
    bytearr.append(npoints<<(8*i));
    }

    return bytearr;
}

QByteArray sendBes(double dxstart,double dxend,int npoints,int order) {
    int nBytes = 60;
    QByteArray bytearr;
    char * besselCommand = (char *) "Bessel function\0";

    for(int i=0; i<4; i++){
        bytearr.append(nBytes<<(8*i));
    }

    for(int i=0; i<15; i++){
        bytearr.append(besselCommand[i]);
        bytearr.append('\0');
    }

    bytearr.append('\0');

    bytearr.append('\0');


    char * tmparr = (char *)&dxstart;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    tmparr = (char *)&dxend;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    for(unsigned int i=0; i<sizeof(int); i++){
    bytearr.append(npoints<<(8*i));
    }

    // only bessel requires order so we added here
    for(unsigned int i=0; i<sizeof(int); i++){
    bytearr.append(order<<(8*i));
    }


    return bytearr;
}

QByteArray sendFreS(double dxstart,double dxend,int npoints) {
    int nBytes = 62;
    QByteArray bytearr;
    char * fresnelSCommand = (char *) "Fresnel integral S\0";

    for(int i=0; i<4; i++){
        bytearr.append(nBytes<<(8*i));
    }

    for(int i=0; i<18; i++){
        bytearr.append(fresnelSCommand[i]);
        bytearr.append('\0');
    }

    bytearr.append('\0');

    bytearr.append('\0');


    char * tmparr = (char *)&dxstart;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    tmparr = (char *)&dxend;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    for(unsigned int i=0; i<sizeof(int); i++){
    bytearr.append(npoints<<(8*i));
    }

    return bytearr;
}

QByteArray sendFreC(double dxstart,double dxend,int npoints) {
    int nBytes = 62;
    QByteArray bytearr;
    char * fresnelSCommand = (char *) "Fresnel integral C\0";

    for(int i=0; i<4; i++){
        bytearr.append(nBytes<<(8*i));
    }

    for(int i=0; i<18; i++){
        bytearr.append(fresnelSCommand[i]);
        bytearr.append('\0');
    }

    bytearr.append('\0');

    bytearr.append('\0');


    char * tmparr = (char *)&dxstart;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    tmparr = (char *)&dxend;
    for(unsigned int i=0; i<sizeof(double); i++){
    bytearr.append(tmparr[i]);
    }

    for(unsigned int i=0; i<sizeof(int); i++){
    bytearr.append(npoints<<(8*i));
    }

    return bytearr;
}

///////////////////////////////////////////////////////

void MainWindow::on_connectButton_clicked()
{

    if(mysocket->state()!=QLocalSocket::ConnectedState){
            ui->statusBar->showMessage("Connecting to pipe , please wait!");

            mysocket->connectToServer(pipeaddress, QIODevice::ReadWrite);

            if (!mysocket->waitForConnected(2000)) {
                    ui->statusBar->showMessage("Connection timeout");

                    QMessageBox::information(this, "Failure","Could not connect");

                    return;
                }

            ui->statusBar->showMessage("Connected succesfully");
            ui->connectButton->setEnabled(false);
            ui->disconnectButton->setEnabled(true);
            ui->computeButton->setEnabled(true);

        }
        else{
            ui->statusBar->showMessage("Already connected to pipe");
        }

}

void MainWindow::on_disconnectButton_clicked()
{
    QByteArray bytearr;


    char * stopCommand = (char*)"Stop\0";

    bytearr.append(14);    //this message is going to be 14 bytes long
    bytearr.append('\0');bytearr.append('\0');bytearr.append('\0');

    for(int i=0; i<4; i++){
        bytearr.append(stopCommand[i]);
        bytearr.append('\0');
    }

    bytearr.append('\0');bytearr.append('\0');


    if (this->mysocket->state()==QLocalSocket::ConnectedState){

        mysocket->write(bytearr, 14);

        mysocket->disconnectFromServer();

        ui->computeButton->setEnabled(false);
        ui->connectButton->setEnabled(true);
        ui->disconnectButton->setEnabled(false);


        ui->statusBar->showMessage("Disconnected from pipe server");
     }else{
        ui->statusBar->showMessage("ERROR: "+mysocket->errorString());
    }
}

void MainWindow::on_computeButton_clicked()
{
    QString functionname = ui->functionCombo->currentText();
    QString xstart = ui->xStart->text().trimmed();
    QString xend = ui->xEnd->text().trimmed();
    QString npoints = ui->nPoints->text().trimmed();
    QString order = ui->Order->text().trimmed();

    bool inputVerified = true;
    bool badinput=false;

    double dxstart = xstart.toDouble(&inputVerified);
    if (inputVerified==false) {
        badinput = true;
    }
    double dxend = xend.toDouble(&inputVerified);
    if (inputVerified==false) {
        badinput = true;
    }
    int inpoints = npoints.toInt(&inputVerified);
    if (inputVerified==false) {
        badinput = true;
    }

    if(xstart=="" || xend=="" || npoints=="") {
        badinput= true;
    }

    int iorder = order.toInt(&inputVerified);

    if(ui->functionCombo->currentIndex() == 2){

        if(order==""||inputVerified==false){
            badinput= true;
        }
    }

    if (badinput) {
         QMessageBox::critical(this, "Wrong input", "check your input! and try again");
         return;
    }

    ////////// input passed the check and now will be sent ////////


    QByteArray bytearr; // array to be filled by one of our functions

    short unsigned int functionNumber = ui->functionCombo->currentIndex();

    // this is how i check which funbction was selected in functionCombo and send messages depending on that

    switch(functionNumber) {
       case 0  :
          bytearr= sendSin(dxstart,dxend,inpoints);
          ui->statusBar->showMessage("Correct input, sending request for Sine calculations to server!");
          break; //optional
       case 1  :
          bytearr= sendCos(dxstart,dxend,inpoints);
          ui->statusBar->showMessage("Correct input, sending request for Cosine calculations to server!");
          break; //optional
       case 2  :
          bytearr= sendBes(dxstart,dxend,inpoints,iorder);
          ui->statusBar->showMessage("Correct input, sending request for Bessel calculations to server!");
          break; //optional
       case 3  :
          bytearr= sendFreS(dxstart,dxend,inpoints);
          ui->statusBar->showMessage("Correct input, sending request for Fresnel S calculations to server!");
          break; //optional
       case 4  :
          bytearr= sendFreC(dxstart,dxend,inpoints);
          ui->statusBar->showMessage("Correct input, sending request for Fresnel C calculations to server!");
          break; //optional
    }


    mysocket->write(bytearr);

}

void MainWindow::on_exitButton_clicked()
{
    QApplication::exit();
}

void MainWindow::onResponseReceived() {

    QByteArray bytearr = mysocket->readAll();
    QDataStream dataStream(bytearr);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    int len = 0;
    dataStream >> len;

    if (bytearr.length() != len) {
        QMessageBox::critical(this,"ERROR", "Invalid length!");
        return;
    }

    QString responseString;

    while (true) {
        ushort responseChar = 0;
        dataStream >> responseChar;
        if (responseChar == 0)
            break;
        responseString.append(QChar(responseChar));
    }



    if (responseString != "Curve") {
        ui->statusBar->showMessage("Response message did not contain \"Curve\" ERROR");
        ui->textEdit->setText(responseString);
    }
    else {
        ui->statusBar->showMessage("successfull response");
        ui->textEdit->setText(responseString);

        QVector<double> vXpoints;
        QVector<double> vYpoints;

        double minX = 0;
        double maxX = 0;
        double minY = 0;
        double maxY = 0;

        while (!dataStream.atEnd()) {

            double dfX, dfY;
            dataStream >> dfX >> dfY;

            vXpoints.push_back(dfX);
            vYpoints.push_back(dfY);

                // we need to find minimum and maximum

            if (dfX > maxX) maxX = dfX;
            if (dfX < minX) minX = dfX;
            if (dfY > maxY) maxY = dfY;
            if (dfY < minY) minY = dfY;

        }

            QString strFunctionName = ui->functionCombo->currentText();

            ui->CustomPlotCanvas->addGraph();

            ui->CustomPlotCanvas->graph(0)->setData(vXpoints, vYpoints);

            ui->CustomPlotCanvas->graph(0)->setPen(QPen(Qt::blue));
            ui->CustomPlotCanvas->graph(0)->setLineStyle(QCPGraph::lsLine);

            ui->CustomPlotCanvas->graph(0)->setName(strFunctionName);

            ui->CustomPlotCanvas->xAxis->setLabel("X coords");
            ui->CustomPlotCanvas->yAxis->setLabel("Y coords");

            ui->CustomPlotCanvas->xAxis->setRange(minX, maxX);
            ui->CustomPlotCanvas->yAxis->setRange(minY, maxY);

            ui->statusBar->showMessage("Enjoy your painting! :D ");

            ui->CustomPlotCanvas->replot();
        }
    }

void MainWindow::OnFunctionOptionChanged(const QString &functionname) {
    if (functionname == "Bessel function") {

        ui->Order->setEnabled(true);
       } else {
        ui->Order->setEnabled(false);

       }
}
