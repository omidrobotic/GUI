#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QStringList>

#include "sql.h"

QLabel *configLabelId[50];
QLabel *configLabelName[50];
QLabel *configLabelValue[50];
QLineEdit *configLineEdit[50];
QComboBox *configComboBox[50];
QStringList list[50];
QPushButton *configButton;
QGridLayout *configHlayout = new QGridLayout;

int sizeConfig=0;

char fileLocation[50]="/home/mhz/omidgui";
char add[] = "/data";
char config[]="/config.db";
char robot[]="/robot.db";
char refree[]="/refree.db";

char configLocation[sizeof (fileLocation)];
char robotLocation[sizeof (fileLocation)];
char refreeLocation[sizeof (fileLocation)];

int dirExists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    strcat(fileLocation, add);
    strcpy(configLocation,fileLocation);
    strcpy(robotLocation,fileLocation);
    strcpy(refreeLocation,fileLocation);

    strcat(configLocation,config);
    strcat(robotLocation,robot);
    strcat(refreeLocation,refree);



    ui->saveLabel->setText("Save data in : "+qApp->applicationDirPath()+"/database");
    ui->loadLabel->setText("Load data in : "+qApp->applicationDirPath()+"/database");

    if(!dirExists(fileLocation))
    {
        int check = mkdir(fileLocation,0777);
        if (!check)
        {
            std::cout<<"Directory created\n";
            strcat(logs,"Directory created\n");
            QMessageBox msgBox;
            msgBox.setText("Directory created");
            msgBox.exec();
        }
        else
        {
            std::cout<<"Unable to create directory\n";
            strcat(logs,"Unable to create directory\n");
            QMessageBox msgBox;
            msgBox.setText("Unable to create directory");
            msgBox.exec();
        }
    }
    else
    {
        std::cout<<"Directory exist\n";
        strcat(logs,"Directory exist\n");
    }





    std::cout<<"Run in: "<<__FILE__<<"\n";
    strcat(logs,"Run in: ");
    strcat(logs,__FILE__);
    strcat(logs,"\n");


    configConfigDatabase(&configDataBase);
    openDataBase(&configDataBase);

//    configRobotsDatabase(&robotsDataBase);
//    openDataBase(&robotsDataBase);

//    configRefreeDatabase(&refreeDataBase);
//    openDataBase(&refreeDataBase);


    QMessageBox msgBox;
    msgBox.setText(logs);
    msgBox.exec();


    QPushButton *button = new QPushButton("Button One");
    QPushButton *button1 = new QPushButton("Button Two");
    QPushButton *button2 = new QPushButton("Button Three");
    QPushButton *button3 = new QPushButton("Button One");
    QPushButton *button4 = new QPushButton("Button Two");
    QPushButton *button5 = new QPushButton("Button Three");

    QGridLayout *hlayout = new QGridLayout;

    hlayout->addWidget(button,0,0,1,1);
    hlayout->addWidget(button1,0,1,1,1);
    hlayout->addWidget(button2,1,0,1,1);
    hlayout->addWidget(button3,1,1,1,1);
    hlayout->addWidget(button4,2,0,1,1);
    hlayout->addWidget(button5,3,0,1,1);





    findDataBaseId("config","ID",0,&configDataBase);
    configLabelId[0] = new QLabel("ID");
    configHlayout->addWidget(configLabelId[0],0,0,1,1);
    findDataBaseId("config","NAME",0,&configDataBase);
    configLabelName[0] = new QLabel("Name");
    configHlayout->addWidget(configLabelName[0],0,1,1,1);
    configLabelValue[0] = new QLabel("Value");
    configHlayout->addWidget(configLabelValue[0],0,2,1,1);

    int i=1;
    while (true) {


        findDataBaseId("config","TYPE",i,&configDataBase);
        if(seter.value=="Line Edit")
        {
            findDataBaseId("config","EQULVALUE",i,&configDataBase);
            configLabelValue[i] = new QLabel(QString::fromStdString(seter.value));
            configHlayout->addWidget(configLabelValue[i],i,2,1,1);

            configLineEdit[i] = new QLineEdit(QString::fromStdString(seter.value));
            configHlayout->addWidget(configLineEdit[i],i,3,1,1);
        }
        else if(seter.value=="Combo Box")
        {
            findDataBaseId("config","EQULVALUE",i,&configDataBase);
            configLabelValue[i] = new QLabel(QString::fromStdString(seter.value));
            configHlayout->addWidget(configLabelValue[i],i,2,1,1);


            QString dataValue=QString::fromStdString(seter.value);
            findDataBaseId("config","EQULSTRING",i,&configDataBase);
            QString data = QString::fromStdString(seter.value);
            list[i] = data.split(",");
            configComboBox[i]=new QComboBox;

            configComboBox[i]->addItem(dataValue);
            foreach (QString itm, list[i]) {
                if(itm!=dataValue)
               configComboBox[i]->addItem(itm);
            }


            configHlayout->addWidget(configComboBox[i],i,3,1,1);
        }
        else if(seter.value=="Radio Button")
        {

        }
        else if(seter.value=="Check Box")
        {

        }
        else {
//            configButton = new QPushButton("Push");
//            configHlayout->addWidget(configButton,i,3,1,1);
            sizeConfig=i;
            break;
        }
        findDataBaseId("config","ID",i,&configDataBase);
        configLabelId[i] = new QLabel(QString::fromStdString(seter.value));
        configHlayout->addWidget(configLabelId[i],i,0,1,1);
        findDataBaseId("config","NAME",i,&configDataBase);
        configLabelName[i] = new QLabel(QString::fromStdString(seter.value));
        configHlayout->addWidget(configLabelName[i],i,1,1,1);


        if(seter.value=="" || i>50)
            break;
        i++;
    }

    ui->robotScrollAreaWidgetContents->setLayout(hlayout);
    ui->configScrollAreaWidgetContents->setLayout(configHlayout);


//    Gui = new UpdateGui(this);
//    connect(Gui,SIGNAL(nextUpdate()),this,SLOT(nextUpdateGUI()));
//    Gui->start();


    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextUpdateGUI()));
    timer->start(1000);




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_configAdd_clicked()
{
    QString id=ui->configId->text();
    QString name=ui->configName->text();
    QString vString=ui->configString->text();
    QString value=ui->configValue->text();
    QString type=ui->configcomboBox->currentText();

    insertDataInDataBase("config",id.toInt(),(char*)name.toStdString().c_str(),(char *)value.toStdString().c_str(),(char*)vString.toStdString().c_str(),(char*)type.toStdString().c_str(),&configDataBase);

    QMessageBox msgBox;
    msgBox.setText(ui->configName->text());
    msgBox.exec();
}


void MainWindow::nextUpdateGUI()
{

   int i=1;
   while (i<sizeConfig) {
       findDataBaseId("config","EQULVALUE",i,&configDataBase);
       configLabelValue[i]->setText(QString::fromStdString(seter.value));

       QString dataSet = QString::fromStdString(seter.value);

       findDataBaseId("config","TYPE",i,&configDataBase);
       if(seter.value=="Line Edit")
        {
           QString dataGet = configLineEdit[i]->text();
           if(dataSet!=dataGet)
           {
              configLineEdit[i]->setStyleSheet("background: red");
           }
           else {
               configLineEdit[i]->setStyleSheet("background: white");
           }
        }
        else if(seter.value=="Combo Box")
        {
            QString dataGet=configComboBox[i]->currentText();
            if(dataSet!=dataGet)
            {
                configComboBox[i]->setStyleSheet("background: red");
            }
            else {
                configComboBox[i]->setStyleSheet("background: white");
                configComboBox[i]->setStyleSheet("color: black");
            }
        }


       i++;
   }
}

void MainWindow::on_saveButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(QString("Saved!!!"));
    msgBox.exec();
    int i=1;
        while (i<sizeConfig) {
            findDataBaseId("config","TYPE",i,&configDataBase);
            if(seter.value=="Line Edit")
            {
                QString value=configLineEdit[i]->text();
                updateDataBase("config","EQULVALUE",i,(char *)value.toStdString().c_str(),&configDataBase);
            }
            else if(seter.value=="Combo Box")
            {
                QString value=configComboBox[i]->currentText();
                updateDataBase("config","EQULVALUE",i,(char *)value.toStdString().c_str(),&configDataBase);
            }
            i++;
        }
    }

void MainWindow::on_refreshButton_clicked()
{
    int i=1;
    while (true) {

        if(sizeConfig>i)
        {
            findDataBaseId("config","TYPE",i,&configDataBase);
            if(seter.value=="Line Edit")
            {
                findDataBaseId("config","EQULVALUE",i,&configDataBase);
                configLabelValue[i]->setText(QString::fromStdString(seter.value));

                configLineEdit[i]->setText(QString::fromStdString(seter.value));
            }
            else if(seter.value=="Combo Box")
            {
                findDataBaseId("config","EQULVALUE",i,&configDataBase);
                configLabelValue[i]->setText(QString::fromStdString(seter.value));


                QString dataValue=QString::fromStdString(seter.value);
                findDataBaseId("config","EQULSTRING",i,&configDataBase);
                QString data = QString::fromStdString(seter.value);
                list[i] = data.split(",");
                configComboBox[i]=new QComboBox;

                configComboBox[i]->addItem(dataValue);
                foreach (QString itm, list[i]) {
                    if(itm!=dataValue)
                        configComboBox[i]->addItem(itm);
                }


            }
            else if(seter.value=="Radio Button")
            {

            }
            else if(seter.value=="Check Box")
            {

            }
            else {
                sizeConfig=i;
                break;
            }
            findDataBaseId("config","ID",i,&configDataBase);
            configLabelId[i]->setText(QString::fromStdString(seter.value));
            findDataBaseId("config","NAME",i,&configDataBase);
            configLabelName[i]->setText(QString::fromStdString(seter.value));


            if(seter.value=="" || i>50)
                break;
            i++;
        }
        else
        {
            findDataBaseId("config","TYPE",i,&configDataBase);
            if(seter.value=="Line Edit")
            {
                findDataBaseId("config","EQULVALUE",i,&configDataBase);
                configLabelValue[i] = new QLabel(QString::fromStdString(seter.value));
                configHlayout->addWidget(configLabelValue[i],i,2,1,1);

                configLineEdit[i] = new QLineEdit(QString::fromStdString(seter.value));
                configHlayout->addWidget(configLineEdit[i],i,3,1,1);
            }
            else if(seter.value=="Combo Box")
            {
                findDataBaseId("config","EQULVALUE",i,&configDataBase);
                configLabelValue[i] = new QLabel(QString::fromStdString(seter.value));
                configHlayout->addWidget(configLabelValue[i],i,2,1,1);


                QString dataValue=QString::fromStdString(seter.value);
                findDataBaseId("config","EQULSTRING",i,&configDataBase);
                QString data = QString::fromStdString(seter.value);
                list[i] = data.split(",");
                configComboBox[i]=new QComboBox;

                configComboBox[i]->addItem(dataValue);
                foreach (QString itm, list[i]) {
                    if(itm!=dataValue)
                   configComboBox[i]->addItem(itm);
                }


                configHlayout->addWidget(configComboBox[i],i,3,1,1);
            }
            else if(seter.value=="Radio Button")
            {

            }
            else if(seter.value=="Check Box")
            {

            }
            else {
    //            configButton = new QPushButton("Push");
    //            configHlayout->addWidget(configButton,i,3,1,1);
                sizeConfig=i;
                break;
            }
            findDataBaseId("config","ID",i,&configDataBase);
            configLabelId[i] = new QLabel(QString::fromStdString(seter.value));
            configHlayout->addWidget(configLabelId[i],i,0,1,1);
            findDataBaseId("config","NAME",i,&configDataBase);
            configLabelName[i] = new QLabel(QString::fromStdString(seter.value));
            configHlayout->addWidget(configLabelName[i],i,1,1,1);


            if(seter.value=="" || i>50)
                break;
            i++;
        }
    }
//    configLabelName[1]->setText(QString("aaaa"));
//    configLabelValue[13] = new QLabel(QString::fromStdString(seter.value));
//                configHlayout->addWidget(configLabelValue[13],13,2,1,1);


}

void MainWindow::on_configRemove_clicked()
{
    QString id=ui->configId->text();
    QString name=ui->configName->text();
    if(id!="")
    {
        removeDataInDataBase(id.toInt(),"config",&configDataBase);
    }
    else if(name!="")
    {
       removeDataInDataBase((char*) name.toStdString().c_str(),"config",&configDataBase);

    }
}
