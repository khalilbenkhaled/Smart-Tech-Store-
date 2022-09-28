#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include "client.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <iostream>
#include <string>
#include <stdio.h>
#include "facture.h"
#include "drilldownchart.h"
#include "drilldownslice.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QTime>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QSqlQuery>
#include "QDate"
#include "QtDebug"
#include <QPixmap>
#include<QSystemTrayIcon>
#include <QApplication>
#include <QModelIndex>
#include <QItemDelegate>
#include <QSize>
#include <QSpinBox>
#include "smtp.h"
#include <QDesktopServices>
#include <QPieSlice>
#include <QPieSeries>
#include <QIntValidator>
#include <QtGui>
#include "QString"
#include<QUrl>
#include <QPainter>
#include <QtCharts>
#include <QRectF>
#include <QStaticText>
#include "arduino.h"
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QThread>
#include <chrono>
#include <windows.h>
#include<QTimer>
#include <array>
#include <stdlib.h>
//#include <float.h>
//#include <sstream>
//jouhayna

#include "fournisseur.h"
#include <QQuickItem>
#include"qrcode.h"
//#include "QIntValidator"
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>

//#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>

#include <strstream>
//#include <sstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>




//************qrcode**********
#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <utility>
#include "qrcode.h"
//****************************
//delaration de C.S
#include <QRegExpValidator>
using qrcodegen::QrCode;


//#include "qrcodegen.hpp"

#include "drilldownchart.h"
#include "drilldownslice.h"
#include <QPieSeries>
#include <QChartView>
#include <QLayout>

QValidator::State test(QString input);

QValidator::State test(QString input)
{
  QRegularExpression r1("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9])(?=.*?[#?!@$%^&*-]).{8,}$");
  //QRegularExpression r1("test test");
  if(input.isEmpty()) return QValidator::Intermediate;
  if(r1.match(input).hasMatch()) return QValidator::Acceptable;
  else return QValidator::Invalid;

}
//*********************************************************
using namespace std;
QSerialPort *serialPort;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->listefournisseur->setModel(j.afficher_listfournisseur());
ui->tableView_affichage->setModel (P.afficher ());
ui->tableView_affichage_2->setModel (P.afficher ());
ui->tableView_affichage_3->setModel (P.afficher ());

//-----------------------map--------------------
ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
   ui->quickWidget->show();

   auto obj = ui->quickWidget->rootObject();
   connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
   connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

   emit setCenter(36.27561, 9.86718);
   emit addMarker(36.27561, 9.86718);

   //-----------------------------------------arduino1---------------
    serialbuffer="";
     int ret=A.connect_arduino(); // lancer la connexion à arduino
     switch(ret){
     case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
         break;
     case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
     case(-1):qDebug() << "arduino is not available";
     }
      QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
      //le slot update_label suite à la reception du signal readyRead (reception des données).

      //---------------arduino2-----------------
      ui->fermerPorte->setVisible(false);
      int ret2=A2.connect_arduino(); // lancer la connexion à arduino
         switch(ret2){
         case(0):qDebug()<< "arduino is available and connected to : "<< A2.getarduino_port_name();
             A2.write_to_arduino("1");
             break;
         case(1):qDebug() << "arduino is available but not connected to :" <<A2.getarduino_port_name();
                break;
         case(-1):qDebug() << "arduino is not available";
         }
         QObject::connect(A2.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));




      //********************fournisseurs***************


   // ui->contenu->setCurrentIndex(4);
    //ui->listefournisseur->setModel(j.afficher_listfournisseur());
    //-----------------------map--------------------
   /* ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
       ui->quickWidget->show();

       auto obj = ui->quickWidget->rootObject();
       connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
       connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

       emit setCenter(36.27561, 9.86718);
       emit addMarker(36.27561, 9.86718);*/

ui->listefournisseur->setModel(j.afficher_listfournisseur());
       ui->tableViewsql->setModel(f.afficherf());


       f.setnum(ui->lineEdit_numfacture->text().toInt());
       f.setdatef(ui->lineEdit_datefacture->date());
       f.settauxtva(ui->lineEdit_tauxtva->text().toDouble());
       f.settotalht(ui->lineEdit_totalht->text().toDouble());
       f.settotaltva(ui->lineEdit_totaltva->text().toDouble());
       f.settotalttc(ui->lineEdit_totalttc->text().toDouble());
     f.setquantite(ui->lineEdit_quantite->text().toInt());
     f.setcin(ui->lineEdit_codeclient->text().toInt());
   ui->tabclient->setModel(c.afficher());//affichage lors de construction
   ui->lineEdit_cin->setValidator(new QIntValidator(0,99999999,this));
   ui->lineEdit_n-> setStyleSheet ( "background-color: black" );
   QString count= QString::number( c.count_client_cad());//compter les nombre des clients avec cadeaux
   ui->lineEdit_n->setText(count);
   ui->comboBox->setStyleSheet("background-color : black");



// fffffff
DrilldownChart *chart = new DrilldownChart();
chart->setTheme(QChart::ChartThemeLight);
chart->setAnimationOptions(QChart::AllAnimations);
chart->legend()->setVisible(true);
chart->legend()->setAlignment(Qt::AlignRight);





QPieSeries *yearSeries = new QPieSeries(this);
yearSeries->setName("Sales by year - All");









 QSqlQuery q;
q.exec("select pays, count(*) from client group by pays");





while(q.next()) {
    QPieSeries *series = new QPieSeries(this);


    *yearSeries << new DrilldownSlice(q.value(1).toInt(), q.value(0).toString(), series);
}


chart->changeSeries(yearSeries);

QChartView *chartView = new QChartView(chart);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setGeometry(0,0,650,400);
chartView->setParent(ui->widget);






loggedIn = false ;
ui->deconnection->hide();
ui->tableView_employe->setModel(e.affichert());
ui->contenu->setCurrentIndex(25);
QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update()));
Commande x;
ui->table_gaz->setModel(x.afficher_gaz());
Coupon w;
Coupon c;

ui->afficher_coupon_2->setModel(w.afficher()); //HAHAHAAHAHA


}
void MainWindow::update_label()
{
    data=A.read_from_arduino();
    serialbuffer+=QString::fromStdString(data.toStdString());

    if(serialbuffer.length()<11)
    {
        data=A.read_from_arduino();
        serialbuffer+=QString::fromStdString(data.toStdString());

    }
    else
    {

        qDebug() << serialbuffer;




   using namespace std;
     QSqlQuery query;







 QString card=data;


   QSqlQuery q;


q=c.lawej(serialbuffer);
    q.exec();

     q.next();

   int  id= q.value(0).toInt();
  int nbp= q.value(1).toInt();
  nbp=nbp+20;
   QString idd=QString::number(id);
   QString nbpp=QString::number(nbp);
   c.changer(serialbuffer,nbp);






    QByteArray a=idd.toUtf8();
    QByteArray b=nbpp.toUtf8();





Sleep(1000);
    A.write_to_arduino(a);
   Sleep(5000);
A.write_to_arduino(b);
     serialbuffer="";
 }
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_22_clicked()
{
   ui->contenu->setCurrentIndex(1);
   ui->tabclient->setModel(c.afficher());
}

void MainWindow::on_pushButton_15_clicked()
{

    if (!loggedIn) return ;
   ui->contenu->setCurrentIndex(1);
}


void MainWindow::on_pushButton_16_clicked()
{
    if (!loggedIn) return ;
   ui->contenu->setCurrentIndex(4);
}

void MainWindow::on_pushButton_17_clicked()
{
    if (!loggedIn) return ;
    Commande c;

    ui->tableView_2->setModel(c.get_p(-1)); //HAHAHAAHAHA
   ui->tableView_commande->setModel(c.get(true,-1,-1,-1, -1,"","","asc"));
   ui->contenu->setCurrentIndex(11);
}

void MainWindow::on_pushButton_18_clicked()
{

    if (!loggedIn) return ;
   ui->contenu->setCurrentIndex(15);
}

void MainWindow::on_pushButton_19_clicked()
{

    if (!loggedIn) return ;
   ui->contenu->setCurrentIndex(16);
ui->listefournisseur->setModel(j.afficher_listfournisseur());


}

void MainWindow::on_pushButton_20_clicked()
{

    if (!loggedIn) return ;
    ui->contenu->setCurrentIndex(23);
    ui->tableView_affichage->setModel (P.afficher ());
}


void MainWindow::on_pushButton_ajouterclient_clicked()
{
    bool ver2;

    QString email=ui->lineEdit_email->text();

     int cin= ui->lineEdit_cin->text().toInt();
    QString pays=ui->lineEdit_pays->text();
    QString adresse=ui->lineEdit_adress->text();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();

    client c(cin,nom,prenom,email,adresse,pays);
     ver2=c.ajouterclient();


    if(ver2)
    {
        ui->tabclient->setModel(c.afficher());//refresh

        QMessageBox::information(nullptr, QObject::tr("S"),
                    QObject::tr("client ajouter.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::information(nullptr, QObject::tr("S"),
                    QObject::tr("client non ajouter\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_21_clicked()
{
     ui->contenu->setCurrentIndex(0);
}

void MainWindow::on_pushButton_23_clicked()
{
     ui->contenu->setCurrentIndex(2);
}

void MainWindow::on_pushButton_24_clicked()
{
     ui->contenu->setCurrentIndex(3);

}

void MainWindow::on_pushButton_suppclient_clicked()
{

    int supp = ui->lineEdit_cin_s->text().toInt();//cin a supprimer
bool test;
        test=c.supprimerclient(supp);
        if(test)
        {

            ui->tabclient->setModel(c.afficher());//refresh
            QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                        QObject::tr("client supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un client"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_ajouterclient2_clicked()
{

    ui->contenu->setCurrentIndex(0);
}

void MainWindow::on_afficherclient2_clicked()
{

    ui->contenu->setCurrentIndex(1);

}

void MainWindow::on_tabclient_activated(const QModelIndex &index)
{

    QString val=ui->tabclient->model()->data(index).toString();
    ui->contenu->setCurrentIndex(3);

QSqlQuery query;
query=c.afficher_M(val);
if(query.exec())
{
while(query.next())
{

     ui->lineEdit_cin_m->setText(query.value(0).toString());
    ui->lineEdit_nom_m->setText(query.value(1).toString());
     ui->lineEdit_prenom_m->setText(query.value(2).toString());
           ui->lineEdit_email_m->setText(query.value(3).toString());
     ui->lineEdit_adresse_m->setText(query.value(4).toString());
     ui->lineEdit_pays_m->setText(query.value(8).toString());
}
}
}




void MainWindow::on_pushButton_modifierclient_clicked()
{
    bool ver;

    int mod=ui->lineEdit_cin_m->text().toInt();
    QString nom=ui->lineEdit_nom_m->text();
    QString prenom=ui->lineEdit_prenom_m->text();
    QString email=ui->lineEdit_email_m->text();
    QString adresse=ui->lineEdit_adresse_m->text();
    QString pays=ui->lineEdit_pays_m->text();

    ver=c.modifierclient(mod,nom,prenom,email,adresse,pays);
    if(ver==true)
    {
        ui->tabclient->setModel(c.afficher());//refresh

        QMessageBox::information(nullptr, QObject::tr("S"),
                    QObject::tr("client modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::information(nullptr, QObject::tr("S"),
                    QObject::tr("client non modifier\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->contenu->setCurrentIndex(1);

}



void MainWindow::on_pushButton_trierclient_clicked()
{

    ui->tabclient->setModel( c.trier_client());
    if(ui->comboBox->currentIndex()==0)
    {
        ui->tabclient->setModel( c.trier_client());
    }
    if(ui->comboBox->currentIndex()==1)
    {
        ui->tabclient->setModel( c.trier_clientnom());

    }
    if(ui->comboBox->currentIndex()==2)
    {
        ui->tabclient->setModel( c.trier_clientprenom());
    }
    if(ui->comboBox->currentIndex()==3)
    {
        ui->tabclient->setModel( c.trier_nb_points());
    }


}

void MainWindow::on_pushButton_ajouterf_clicked() {

    QString id;
    int num,etat;
    int tottal;
    num=ui->lineEdit_num->text().toInt();
    id=ui->lineEdit_id->text();
    etat=ui->lineEdit_etat->text().toInt();
    tottal=ui->lineEdit_tottal->text().toInt();
    Facture f(num,id,tottal,etat);
    if(f.ajouterf()) {
      if(c.generercadeau(id)){
          popUp = new PopUp();
          popUp->setPopupText("le client dont l'id est " + id + " a un cadeau");
          popUp->setGeometry(QApplication::desktop()->width() - 36 - popUp->width(),
                 QApplication::desktop()->height() -52 - popUp->height(),
                 popUp->width(),
                 popUp->height());
          popUp->show();
          QMessageBox::information(nullptr, QObject::tr("S"),
                      QObject::tr("client ajouter.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

          QString count= QString::number( c.count_client_cad());
          ui->lineEdit_n->setText(count);
          ui->comboBox->setStyleSheet("background-color : black");

      }


    else
      {  QMessageBox::information(nullptr, QObject::tr("S"),
                    QObject::tr("client non ajouter.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        }

}
}

void MainWindow::on_lineEdit_cin_r_textChanged(const QString &arg1)
{

    ui->table_rechercher->setModel( c.rechercher_clientnom(arg1));

}

void MainWindow::on_pushButton_notifclient_clicked()
{
  ui->contenu->setCurrentIndex(2);
  ui->tablelistecadeau->setModel(c.afficherlistecadeau());//refresh

}

/*void MainWindow::on_pushButton_genererpdf_clicked()
{
    c.exporterpdf(ui->textBrowserpdf);
}*/

void MainWindow::on_pushButton_genererpdf_2_clicked()
{
    QString val=ui->lineEdit_cin_g->text();
    c.exporterpdf(ui->textBrowserpdf , val);

}

void MainWindow::on_pushButton_6_clicked()
{
    ui->contenu->setCurrentIndex(5);

}



void MainWindow::on_pushButton_statclient_clicked()
{
    ui->contenu->setCurrentIndex(5);
   /* DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);





    QPieSeries *yearSeries = new QPieSeries(this);
    yearSeries->setName("stat - All");




     QSqlQuery q;
    q.exec("select pays, count(*) from client group by pays");





    while(q.next()) {
        QPieSeries *series = new QPieSeries(this);


        *yearSeries << new DrilldownSlice(q.value(1).toInt(), q.value(0).toString(), series);
    }


    chart->changeSeries(yearSeries);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->widget);*/
}















void MainWindow::on_pushButton_chercher_clicked()
{
    ui->tableViewsql->setModel(f.recherchef(ui->lineEdit_numfacture->text()));

}
void MainWindow::stats(QString table,QString critere,int valeur1,int valeur2,QString unite)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString valeur1QString=QString::number(valeur1);
    QString valeur2QString=QString::number(valeur2);

                model->setQuery("select * from "+table+" where "+critere+"<"+valeur1QString);

                float countFirst=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+" between " +valeur1QString+ " and "+valeur2QString);
                float countSecond=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+">"+valeur2QString);
                float countThird=model->rowCount();
                float total=countFirst+countSecond+countThird;
                QString a=QString("moins de "+valeur1QString+" "+unite+" "+QString::number((countFirst*100)/total,'f',2)+"%" );

                QString b=QString("entre "+valeur1QString+ " et " +valeur2QString+" "+unite+" "+QString::number((countSecond*100)/total,'f',2)+"%" );
                QString c=QString("Plus que "+valeur2QString +" "+unite+" "+QString::number((countThird*100)/total,'f',2)+"%" );

                QPieSeries *series = new QPieSeries();
                series->append(a,countFirst);
                series->append(b,countSecond);
                series->append(c,countThird);
        if (countFirst!=0)
        {QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());}
        if ( countSecond!=0)
        {
                 // Add label, explode and define brush for 2nd slice
                 QPieSlice *slice1 = series->slices().at(1);
                 //slice1->setExploded();
                 slice1->setLabelVisible();
        }
       if(countThird!=0)
        {
                 // Add labels to rest of slices
                 QPieSlice *slice2 = series->slices().at(2);
                 //slice1->setExploded();
                 slice2->setLabelVisible();
        }
                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                if(critere=="CAPACITE_STADE")
                    critere="Capacite";
                chart->setTitle("Pourcentage Par " +critere+":Nombre Des " +table+" :" +QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();

}

void MainWindow::on_chart_clicked()
{
     stats("facture","TOTALTTC",500,1000,"TOTAL TTC");
}

void MainWindow::on_mailing_clicked()
{
     ui->contenu->setCurrentIndex(6);
}

void MainWindow::on_retour_clicked()
{
    ui->contenu->setCurrentIndex(4);
}
void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("alarassaa147@gmail.com", "xwgasmdtzmkoiltb","smtp.gmail.com",465,30000);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    smtp->sendMail("promotion", ui->lineEdit_12->text() , ui->lineEdit_11->text(),ui->textEdit_2->toPlainText());
}



void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}



void MainWindow::on_envoyer_2_clicked()
{
     connect(ui->envoyer_2, SIGNAL(clicked()),this, SLOT(sendMail()));
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    bool check=true;
    bool check2=true;
    bool check3=true;
    bool check4=true;
    bool check5=true;
    bool check6=true;
    bool check7=true;
     int check8=0;

        int  num= ui->lineEdit_numfacture->text().toInt();
        QDate  datef= ui->lineEdit_datefacture->date();
        double  tauxtva= ui->lineEdit_tauxtva->text().toDouble();
        double  totalht= ui->lineEdit_totalht->text().toDouble();
        double  totaltva= ui->lineEdit_totaltva->text().toDouble();
        double  totalttc= ui->lineEdit_totalttc->text().toDouble();
        int quantite=  ui->lineEdit_quantite->text().toInt();
        int cin=  ui->lineEdit_codeclient->text().toInt();
        int etat=  ui->lineEdit_etat->text().toInt();


        QString numcheck= ui->lineEdit_numfacture->text();
        QString checktauxtva=ui->lineEdit_tauxtva->text();
        QString  checktotalht= ui->lineEdit_totalht->text();
        QString  checktotaltva= ui->lineEdit_totaltva->text();
        QString  checktotalttc= ui->lineEdit_totalttc->text();
        QString checkquantite=  ui->lineEdit_quantite->text();
        QString checkcin=  ui->lineEdit_codeclient->text();

      check = f.checkforchar(numcheck);
      check2 = f.checkforchar(checktauxtva);
       check3 = f.checkforchar(checktotalht);
        check4 = f.checkforchar(checktotaltva);
         check5 = f.checkforchar(checktotalttc);
          check6 = f.checkforchar(checkquantite);
           check7 = f.checkforchar(checkcin);

           if(etat==0)
           {
               check8=1;
           }
           else
           {
               check8=0;
           }


      Facture f(num,datef,tauxtva,totalht,totaltva,totalttc,quantite,cin,etat);





    if(check&&check2&&check3&&check4&&check5&&check6&&check7&&check8==1)
    {

        bool test=f.ajouterf();
        if(test)
      {
            if(c.generercadeau(checkcin)){
                popUp = new PopUp();
                popUp->setPopupText("le client dont l'id est " + checkcin + " a un cadeau");
                popUp->setGeometry(QApplication::desktop()->width() - 36 - popUp->width(),
                       QApplication::desktop()->height() -52 - popUp->height(),
                       popUp->width(),
                       popUp->height());
                popUp->show();
                QMessageBox::information(nullptr, QObject::tr("S"),
                            QObject::tr("client ajouter.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

                QString count= QString::number( c.count_client_cad());
                ui->lineEdit_n->setText(count);
                ui->comboBox->setStyleSheet("background-color : black");

            }



      ui->tableViewsql->setModel(f.afficherf());
      QMessageBox::information(nullptr, QObject::tr("Ajouter une facture"),
                        QObject::tr("Contract ajouté.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);



      }
        else

                  QMessageBox::critical(nullptr, QObject::tr("Ajouter une facture"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
              QObject::tr("Erreur verifier votre input !.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);


    }

}

void MainWindow::on_pushButton_modifier_clicked()
{
    bool check=true;
    bool check2=true;
    bool check3=true;
    bool check4=true;
    bool check5=true;
    bool check6=true;
    bool check7=true;
    int check8=0;

    int  num= ui->lineEdit_numfacture->text().toInt();
    QDate  datef= ui->lineEdit_datefacture->date();
    double  tauxtva= ui->lineEdit_tauxtva->text().toDouble();
    double  totalht= ui->lineEdit_totalht->text().toDouble();
    double  totaltva= ui->lineEdit_totaltva->text().toDouble();
    double  totalttc= ui->lineEdit_totalttc->text().toDouble();
    int quantite=  ui->lineEdit_quantite->text().toInt();
    int cin=  ui->lineEdit_codeclient->text().toInt();
    int etat=  ui->lineEdit_etat_2->text().toInt();

    QString numcheck= ui->lineEdit_numfacture->text();
    QString checktauxtva=ui->lineEdit_tauxtva->text();
    QString  checktotalht= ui->lineEdit_totalht->text();
    QString  checktotaltva= ui->lineEdit_totaltva->text();
    QString  checktotalttc= ui->lineEdit_totalttc->text();
    QString checkquantite=  ui->lineEdit_quantite->text();
    QString checkcin=  ui->lineEdit_codeclient->text();

  check = f.checkforchar(numcheck);
  check2 = f.checkforchar(checktauxtva);
   check3 = f.checkforchar(checktotalht);
    check4 = f.checkforchar(checktotaltva);
     check5 = f.checkforchar(checktotalttc);
      check6 = f.checkforchar(checkquantite);
       check7 = f.checkforchar(checkcin);
       if(etat==0||etat==1)
       {
           check8=1;
       }
       else
       {
           check8=0;
       }




    Facture f(num,datef,tauxtva,totalht,totaltva,totalttc,quantite,cin,etat);
    bool test=f.modifierf(num);
    if(check&&check2&&check3&&check4&&check5&&check6&&check7&&check8==1)
    {
    if(test)
  {
        if(etat==0)
        {
            ui->tableViewsql->setModel(f.afficherf());
            QMessageBox::information(nullptr, QObject::tr("Modifer une facture"),
                                     QObject::tr("Contract Modifier.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
f.exporterpdff(ui->textpdf);
            bool test2=f.supprimerf(num);
            if(test2)
            {
                ui->tableViewsql->setModel(f.afficherf());//refresh

                QMessageBox::information(nullptr, QObject::tr("archiver une facture"),
                            QObject::tr("Contract archiver.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("archiver une facture"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);


        }



  }
    else

              QMessageBox::critical(nullptr, QObject::tr("Modifier une facture"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
              QObject::tr("Erreur verifier votre input !.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);


    }

}

void MainWindow::on_pushButton_suprimer_clicked()
{
    int num = ui->lineEdit_numfacture->text().toInt();
    bool test=f.supprimerf(num);
    if(test)
    {
        ui->tableViewsql->setModel(f.afficherf());//refresh

        QMessageBox::information(nullptr, QObject::tr("Supprimer une facture"),
                    QObject::tr("Contract supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une facture"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_generer_clicked()
{
     f.exporterpdff(ui->textpdf);
}

void MainWindow::on_trier_clicked()
{
    ui->tableViewsql->setModel(f.afficher_facture_trierf());
}

void MainWindow::on_pushButton_quitter_clicked()
{
    close();
}

void MainWindow::on_tableViewsql_activated(const QModelIndex &index)
{

    QString val=ui->tableViewsql->model()->data(index).toString();

    QSqlQuery query;

    query.prepare("select * from facture where num = '"+val+"' ");
if(query.exec())
{
while(query.next())
{


    ui->lineEdit_numfacture->setText(query.value(0).toString());
    ui->lineEdit_datefacture->setDate(query.value(1).toDate());
    ui->lineEdit_tauxtva->setText(query.value(2).toString());
    ui->lineEdit_totalht->setText(query.value(3).toString());
    ui->lineEdit_totaltva->setText(query.value(4).toString());
    ui->lineEdit_totalttc->setText(query.value(5).toString());
    ui->lineEdit_quantite->setText(query.value(6).toString());
    ui->lineEdit_codeclient->setText(query.value(7).toString());
    ui->lineEdit_etat->setText(query.value(8).toString());


}
}
}










//*********************************fournisseurs*************************************************
void MainWindow::on_ajouterfournisseur_clicked()
{
    QString nom=ui->nomfournisseurajout->text();

      QString adresse=ui->adressefournisseurajout->text();

      QString email=ui->emailfournisseurajout->text();

      fournisseur j (rand(),nom,adresse,email);

      QMessageBox msgBox;

      bool testnom=j.verif_nom(nom);

      bool testmail=j.verif_email(email);

       if(testnom!=false)
       {
         if(testmail)
         {

             bool  test=j.ajouter_fournisseur();

if (test) {
ui->listefournisseur->setModel(j.afficher_listfournisseur());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un fournisseur"),
                          QObject::tr("fournisseur ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
}
else
{  QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
          QObject::tr("Erreur !.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);
}

}
         else {QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                                     QObject::tr("Erreur Mail!.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);}
       }
         else {QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                                    QObject::tr("Erreur Nom!.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}
}



void MainWindow::on_pdffournisseur_clicked()
{
    int id=ui->identifiantfournisseuraffichage->text().toInt();
j.exporterpdf(ui->textbrowserfournisseurpdf, id);
}





void MainWindow::on_qrCode_clicked()
{
    int tabeq=ui->listefournisseur->currentIndex().row();
               QVariant idd=ui->listefournisseur->model()->data(ui->listefournisseur->model()->index(tabeq,0));
               QString idf=idd.toString();
              // QString code=idd.toSTring();
               QSqlQuery qry;
               qry.prepare("select * from FOURNISSEUR where code=:code");
               qry.bindValue(":code",idf);
               qry.exec();

                QString nom,adresse,email;//attributs
                //int idf;


              while(qry.next()){

                  idf=qry.value(1).toString();
                   nom=qry.value(2).toString();
                    adresse=qry.value(3).toString();
                   email=qry.value(4).toString();



               }
               idf=QString(idf);
              //QString text = idf ;
                      idf="CODE:\t" +idf+ "NOM\t:" +nom+ "adresse:\t" +adresse+ "email:\t" +email ;
               QrCode qr = QrCode::encodeText(idf.toUtf8().constData(), QrCode::Ecc::HIGH);

               // Read the black & white pixels
               QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
               for (int y = 0; y < qr.getSize(); y++) {
                   for (int x = 0; x < qr.getSize(); x++) {
                       int color = qr.getModule(x, y);  // 0 for white, 1 for black

                       // You need to modify this part
                       if(color==0)
                           im.setPixel(x, y,qRgb(254, 254, 254));
                       else
                           im.setPixel(x, y,qRgb(0, 0, 0));
                   }
               }
               im=im.scaled(200,200);
              ui->qr_code->setPixmap(QPixmap::fromImage(im));
}




void MainWindow::on_retour_2_clicked()
{
    ui->listefournisseur->setModel(j.afficher_listfournisseur());
}




void MainWindow::on_modifierfournisseur_clicked()
{
    bool test=true;
int idf=ui->identifiantfournisseuraffichage->text().toInt();
        QString nom=ui->nomfournisseuraffichage->text();
            QString adresse=ui->adressefournisseuraffichage->text();
            QString email=ui->emailfournisseuraffichage->text();

            fournisseur j (nom,adresse,email);

            QMessageBox msgBox;
test=j.modifier_fournisseur(idf);
            if(test==true)
            {msgBox.setText("Modification avec succes.");
                ui->listefournisseur->setModel(j.afficher_listfournisseur());}

            else{ msgBox.setText("echec de la modification");}
                    msgBox.exec();
}





void MainWindow::on_supprimerfournisseur_clicked()
{
    fournisseur f1;
            f1.setidf(ui->identifiantfournisseuraffichage->text().toInt());
            bool test=f1.supprimer_fournisseur(f1.get_idf());
            QMessageBox msgBox;
            if (test){
                msgBox.setText("supression avec succes");
                ui->listefournisseur->setModel(j.afficher_listfournisseur());
            }
}






void MainWindow::on_trierfournisseur_clicked()
{
     ui->listefournisseur->setModel(j.trierfournisseur());
}




void MainWindow::on_rechercherfournisseur_2_clicked()
{
    QString idf=ui->rechercherfournisseuraffichage->text();
    ui->listefournisseur->setModel(j.rechercher(idf));
}

void MainWindow::on_listefournisseur_activated(const QModelIndex &index)
{
    QString val=ui->listefournisseur->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT* from fournisseur where idf=:val or nom=:val or adresse=:val or email=:val  ");
        query.bindValue(":val",val);
        query.bindValue(":val",val);
        query.bindValue(":val",val);
        query.bindValue(":val",val);


        if(query.exec()){

                while(query.next()){
                  ui->identifiantfournisseuraffichage->setText(query.value(0).toString());
                  ui->nomfournisseuraffichage->setText(query.value(1).toString());
                  ui->adressefournisseuraffichage->setText(query.value(2).toString());
                  ui->emailfournisseuraffichage->setText(query.value(3).toString());

                }
}



}

void MainWindow::on_fournisseurs_2_currentChanged(int index)//stat
{
    DrilldownChart *chart = new DrilldownChart();
        chart->setTheme(QChart::ChartThemeLight);
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);





        QPieSeries *yearSeries = new QPieSeries(this);
        yearSeries->setName("stat - All");




         QSqlQuery q;
        q.exec("select FOURNISSEUR.nom, count(idp) from PRODUIT join FOURNISSEUR on PRODUIT.idf = FOURNISSEUR.idf group by FOURNISSEUR.nom");





        while(q.next()) {
            QPieSeries *series = new QPieSeries(this);


            *yearSeries << new DrilldownSlice(q.value(1).toInt(), q.value(0).toString(), series);
        }


        chart->changeSeries(yearSeries);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setParent(ui->widget);
            chartView->setGeometry(0,0,650,400);
    chartView->show();
}
//statistiquefournisseurs
/*void MainWindow::on_fournisseurs_2_tabBarClicked(int index)
{
    DrilldownChart *chart = new DrilldownChart();
        chart->setTheme(QChart::ChartThemeLight);
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);





        QPieSeries *yearSeries = new QPieSeries(this);
        yearSeries->setName("stat - All");




         QSqlQuery q;
        q.exec("select FOURNISSEUR.nom, count(idp) from PRODUIT join FOURNISSEUR on PRODUIT.idf = FOURNISSEUR.idf group by FOURNISSEUR.nom");





        while(q.next()) {
            QPieSeries *series = new QPieSeries(this);


            *yearSeries << new DrilldownSlice(q.value(1).toInt(), q.value(0).toString(), series);
        }


        chart->changeSeries(yearSeries);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setParent(ui->widget);
            chartView->setGeometry(0,0,650,400);
    chartView->show();
}*/





void MainWindow::on_localisation_clicked()
{
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
       ui->quickWidget->show();

       auto obj = ui->quickWidget->rootObject();
       connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
       connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

       emit setCenter(ui->latitude->text().toFloat(),ui->longitude->text().toFloat());
       emit addMarker(ui->latitude->text().toFloat(),ui->longitude->text().toFloat());
}




//******************produit/mariem*****************************************
void MainWindow::on_affichage_afficher_clicked()
{
    ui->contenu->setCurrentIndex(23);
    ui->tableView_affichage->setModel (P.afficher ());
}

void MainWindow::on_affichage_ajouter_clicked()
{
    ui->contenu->setCurrentIndex(20);
    ui->tableView_affichage->setModel (P.afficher ());
}

void MainWindow::on_affichage_modifier_clicked()
{
    ui->lineEdit_id_m->clear();
    ui->lineEdit_nom_mod->clear();
    ui->lineEdit_prix->clear();
    ui->lineEdit_qd->clear();
    ui->lineEdit_qv->clear();
    ui->lineEdit_f->clear();

    ui->contenu->setCurrentIndex(21);
    ui->tableView_affichage_2->setModel (P.afficher ());
}

void MainWindow::on_affichage_supprimer_clicked()
{
    ui->contenu->setCurrentIndex(22);
    ui->tableView_affichage_3->setModel (P.afficher ());
    ui->lineEdit_id_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_prix_2->clear();
    ui->lineEdit_qd_2->clear();
    ui->lineEdit_qv_2->clear();
    ui->lineEdit_categorie_2->clear();
    ui->lineEdit_f_2->clear();
}

void MainWindow::on_pushButton_tri_clicked()
{
    ui->tableView_affichage->setModel(P.tri_ID());
}

void MainWindow::on_lineEdit_rechercheNom_textChanged(const QString &arg1)
{
    QString ch = arg1;

                         if (ch=="")
                         {
                             ui->tableView_affichage->setModel(P.afficher());
                         }
                         else
                         {
                           ui->tableView_affichage->setModel(P.afficher_nomrecherche(ch)) ;
                         }
}

void MainWindow::on_pushButton_pdf_clicked()  //generation de pdf produit
{

    {
          QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      "/home",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
          qDebug()<<dir;
          QPdfWriter pdf(dir+"/Pdfdetention.pdf");
                                 QPainter painter(&pdf);
                                int i = 4000;

                                     painter.setPen(Qt::blue);

                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des Produits");
                                     painter.setFont(QFont("Arial", 30));

                                     painter.drawPixmap(QRect(7600,70,2000,1500),QPixmap("C:/Users/marie/OneDrive/Bureau/logo c++.png"));
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.setPen(Qt::blue);
                                     painter.drawText(300,3300,"ID");
                                     painter.drawText(1300,3300,"Nom");
                                     painter.drawText(2500,3300,"Prix Unitaire");
                                     painter.drawText(3600,3300,"Quantité disponible");
                                     painter.drawText(5000,3300,"Quantité Vendue");
                                     painter.drawText(6300,3300,"Fournisseur");
                                     painter.drawText(8200,3300,"Catégorie");
                                      //painter.drawText(8400,3300,"Image");
                                     QTextDocument previewDoc;
                                     QString pdfdetention = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");




                                     QTextCursor cursor(&previewDoc);



                                     QSqlQuery query;
                                     query.prepare("select * from PRODUIT");
                                     query.exec();
                                     while (query.next())
                                     {
                                         painter.drawText(300,i,query.value(0).toString());
                                         painter.drawText(1300,i,query.value(1).toString());
                                         painter.drawText(2800,i,query.value(2).toString());
                                         painter.drawText(3900,i,query.value(3).toString());
                                         painter.drawText(5300,i,query.value(4).toString());
                                         painter.drawText(6600,i,query.value(5).toString());
                                          //painter.drawText(7300,i,query.value(7).toString());
                                         painter.drawText(8200,i,query.value(6).toString());





                                        i = i +500;
                                     }
                                     int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                         QMessageBox::Yes |  QMessageBox::No);
                                         if (reponse == QMessageBox::Yes)
                                         {
                                             QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pdfdetention.pdf"));

                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();


    }


}

}

void MainWindow::on_pushButton_excel_clicked() //generation Excel produit
{
    QTableView *table;
                           table = ui->tableView_affichage;

                           QString filters("CSV files (.xlsx);;All files (.*)");
                           QString defaultFilter("CSV files (*.xlsx)");
                           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                              filters, &defaultFilter);
                           QFile file(fileName);

                           QAbstractItemModel *model =  table->model();
                           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                               QTextStream data(&file);
                               QStringList strList;
                               for (int i = 0; i < model->columnCount(); i++) {
                                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                                   else
                                       strList.append("");
                               }
                               data << strList.join(";") << "\n";
                               for (int i = 0; i < model->rowCount(); i++) {
                                   strList.clear();
                                   for (int j = 0; j < model->columnCount(); j++) {

                                       if (model->data(model->index(i, j)).toString().length() > 0)
                                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                                       else
                                           strList.append("");
                                   }
                                   data << strList.join(";") + "\n";
                               }
                               file.close();
                               QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                                         QObject::tr("Export avec succes .\n"
                                                                     "Click OK to exit."), QMessageBox::Ok);
                           }
        }
        QString currDate()
        {
            QDate date = QDate::currentDate();
            return date.toString("dd.MM.yyyy");
}

void MainWindow::on_pushButton_statistiques_clicked() //generation stats produit
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("select * from PRODUIT where QUANTITEVENDUE>50");
         float plus50=model->rowCount();

         model->setQuery("select * from PRODUIT where QUANTITEVENDUE <50");
         float moins50=model->rowCount();

         float total=plus50+moins50;
             QString a=QString("plus 50 . " +QString::number((plus50*100)/total,'f',2)+"%" );
             QString b=QString("moins 50 .  "+QString::number((moins50*100)/total,'f',2)+"%" );
             QPieSeries *series = new QPieSeries();
             series->append(a,plus50);
             series->append(b,moins50);
         if (plus50!=0)
         {QPieSlice *slice = series->slices().at(0);
             slice->setLabelVisible();
             slice->setPen(QPen());}
         if ( moins50!=0)
         {
             QPieSlice *slice1 = series->slices().at(1);
             slice1->setLabelVisible();
         }

         QChart *chart = new QChart();


         chart->addSeries(series);
         chart->setTitle("Produit :Nb Produits: "+ QString::number(total));
         chart->legend()->hide();


         QChartView *chartView = new QChartView(chart);
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->resize(1000,500);
         chartView->show();

}

void MainWindow::on_pushButton_annuler_2_clicked()
{
    close();
}

void MainWindow::on_ajout_afficher_clicked()
{
    ui->contenu->setCurrentIndex(23);
    ui->tableView_affichage->setModel (P.afficher ());
}

void MainWindow::on_ajout_ajouter_clicked()
{
    ui->contenu->setCurrentIndex(20);
    ui->tableView_affichage->setModel (P.afficher ());
}

void MainWindow::on_ajout_modifier_clicked()
{
    ui->contenu->setCurrentIndex(21);
    ui->tableView_affichage_2->setModel (P.afficher ());

    ui->lineEdit_id_m->clear();
    ui->lineEdit_nom_mod->clear();
    ui->lineEdit_prix->clear();
    ui->lineEdit_qd->clear();
    ui->lineEdit_qv->clear();
    ui->lineEdit_f->clear();
}

void MainWindow::on_ajout_supprimer_clicked()
{
    ui->contenu->setCurrentIndex(22);
    ui->tableView_affichage_3->setModel (P.afficher ());
    ui->lineEdit_id_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_prix_2->clear();
    ui->lineEdit_qd_2->clear();
    ui->lineEdit_qv_2->clear();
    ui->lineEdit_categorie_2->clear();
    ui->lineEdit_f_2->clear();
}

void MainWindow::on_pushButton_image_clicked() //ajout image produit
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName =QFileDialog::getOpenFileName(this, tr("Open Images"), "D:/2A13/Projet C++..qt/smart_tech_2A13/images", tr("Image Files (*.png *.jpg *.bmp)"));
//to select and show the picture
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        image=image.scaledToWidth(ui->label_image->width(),Qt::SmoothTransformation);
            ui->label_image->setPixmap(QPixmap::fromImage(image));
            ui->lineEdit_image->insert(fileName);
    }
}

void MainWindow::on_pushButton_ajouterproduit_clicked() //ajout produit
{
    //controle de saisie
    bool test1=true;
    bool test2=true;
    bool test3=true;
    bool test4=true;
    bool test5=true;

    QString nomtest=ui->lineEdit_NomProduit->text();
    QString prixUtest=ui->lineEdit_PrixUnitaire->text();
    QString quantiteDtest=ui->lineEdit_QuantiteDisponible->text();
    QString quantiteVtest=ui->lineEdit_QuantiteVendue->text();
    QString nomftest=ui->lineEdit_Fournisseur->text();

    test1=P.checkchar(nomtest);
    test2=P.checkint(prixUtest);
    test3=P.checkint(quantiteDtest);
    test4=P.checkint(quantiteVtest);
    test5=P.checkchar(nomftest);

   // int id=ui->lineEdit_IdProduit->text().toInt();

    //normal
    srand(time(0));
  int id;
  id=rand();
    QString nom=ui->lineEdit_NomProduit->text();
    double prixU=ui->lineEdit_PrixUnitaire->text().toDouble();
    int quantiteD=ui->lineEdit_QuantiteDisponible->text().toInt();
    int quantiteV=ui->lineEdit_QuantiteVendue->text().toInt();
    QString categorie=ui->comboBox_3->currentText();
    QString image=ui->lineEdit_image->text();

    QString nomf=ui->lineEdit_Fournisseur->text();
    int idf;
    idf=P.getIdf(nomf);


    Produit P (id,nom,prixU,quantiteD,quantiteV,idf,categorie,image);

           if(test1&&test2&&test3&&test4&&test5)
           {
            bool test=P.ajouter();
            if(test)
            {  QMessageBox::information(nullptr, QObject::tr("Ajouter un produit"),
                                        QObject::tr("Produit ajoute\n"
                                                    "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
                ui->tableView_affichage->setModel (P.afficher ());
                ui->tableView_affichage_2->setModel (P.afficher ());

            }
            else
            {  QMessageBox::warning(nullptr, QObject::tr("erreur"),
                                    QObject::tr("Echec de l'ajout.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}

           }
           else
           {  QMessageBox::critical(nullptr, QObject::tr("erreur"),
                                   QObject::tr("Veuillez vérifier la saisie des inputs.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);}

    ui->lineEdit_NomProduit->clear();
    ui->lineEdit_PrixUnitaire->clear();
    ui->lineEdit_QuantiteDisponible->clear();
    ui->lineEdit_QuantiteVendue->clear();
    ui->comboBox_3->clear();
    ui->lineEdit_Fournisseur->clear();
    ui->label_image->clear();
    ui->lineEdit_image->clear();
}

void MainWindow::on_pushButton_annuler_clicked()
{
     close();
}

void MainWindow::on_modification_afficher_clicked()
{
     ui->contenu->setCurrentIndex(23);
}

void MainWindow::on_modification_ajouter_clicked()
{
    ui->contenu->setCurrentIndex(20);
    ui->tableView_affichage->setModel (P.afficher ());
}

void MainWindow::on_modification_modifier_clicked()
{
    ui->contenu->setCurrentIndex(21);
    ui->tableView_affichage_2->setModel (P.afficher ());

    ui->lineEdit_id_m->clear();
    ui->lineEdit_nom_mod->clear();
    ui->lineEdit_prix->clear();
    ui->lineEdit_qd->clear();
    ui->lineEdit_qv->clear();
    ui->lineEdit_f->clear();
}

void MainWindow::on_modification_supprimer_clicked()
{
    ui->contenu->setCurrentIndex(22);
    ui->tableView_affichage_3->setModel (P.afficher ());

    ui->lineEdit_id_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_prix_2->clear();
    ui->lineEdit_qd_2->clear();
    ui->lineEdit_qv_2->clear();
    ui->lineEdit_categorie_2->clear();
    ui->lineEdit_f_2->clear();
}

void MainWindow::on_tableView_affichage_2_activated(const QModelIndex &index) //tableau d'affichage dans modifier
{
    QString val=ui->tableView_affichage_2->model()->data(index).toString();
    QSqlQuery qry;

    qry.prepare("select produit.*, fournisseur.nom as fournisseur from PRODUIT join fournisseur on produit.idf=fournisseur.idf where IDP='"+val+"' or produit.NOM='"+val+"' or PRIX_U='"+val+"' or QUANTITEDISPO='"+val+"' or QUANTITEVENDUE='"+val+"' or CATEGORIE='"+val+"'");
    if (qry.exec())
        { while (qry.next())
        {
            ui->lineEdit_id_m->setText(qry.value(0).toString());
            ui->lineEdit_nom_mod->setText(qry.value(1).toString());
            ui->lineEdit_prix->setText(qry.value(2).toString());
            ui->lineEdit_qd->setText(qry.value(3).toString());
            ui->lineEdit_qv->setText(qry.value(4).toString());
            ui->comboBox_4->setEditText(qry.value(7).toString());
            ui->lineEdit_f->setText(qry.value(8).toString());

        }
    }
}

void MainWindow::on_pushButton_modifierproduit_clicked() //modification produit
{
    //controle de saisie
    bool test1=true;
    bool test2=true;
    bool test3=true;
    bool test4=true;
    bool test5=true;

    QString nomtest=ui->lineEdit_nom_mod->text();
    QString prixUtest=ui->lineEdit_prix->text();
    QString quantiteDtest=ui->lineEdit_qd->text();
    QString quantiteVtest=ui->lineEdit_qv->text();
    QString nomftest=ui->lineEdit_f->text();

    test1=P.checkchar(nomtest);
    test2=P.checkint(prixUtest);
    test3=P.checkint(quantiteDtest);
    test4=P.checkint(quantiteVtest);
    test5=P.checkchar(nomftest);

    //normal
    int id=ui->lineEdit_id_m->text().toInt();
    QString nom=ui->lineEdit_nom_mod->text();
    double prixU=ui->lineEdit_prix->text().toDouble();
    int quantiteD=ui->lineEdit_qd->text().toInt();
    int quantiteV=ui->lineEdit_qv->text().toInt();
    QString categorie=ui->comboBox_4->currentText();

    QString nomf=ui->lineEdit_f->text();

    QString image;
    int idf;
    idf=P.getIdf(nomf);

    Produit P (id,nom,prixU,quantiteD,quantiteV,idf,categorie,image);

    if(test1&&test2&&test3&&test4&&test5 )
    { bool test=P.modifier(id);
  if(test)
{

QMessageBox::information(nullptr, QObject::tr("modifier un produit"),
                  QObject::tr("Produit modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
                  ui->tableView_affichage_2->setModel (P.afficher ());


}
  else
      QMessageBox::critical(nullptr, QObject::tr("modifier un produit"),
                  QObject::tr("Erreur !\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {  QMessageBox::critical(nullptr, QObject::tr("erreur"),
                            QObject::tr("Veuillez vérifier la saisie des inputs.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}

  ui->lineEdit_id_m->clear();
  ui->lineEdit_nom_mod->clear();
  ui->lineEdit_prix->clear();
  ui->lineEdit_qd->clear();
  ui->lineEdit_qv->clear();
  ui->comboBox_4->clear();
  ui->lineEdit_f->clear();
}

void MainWindow::on_pushButton_annuler_3_clicked()
{
    close();
}



void MainWindow::on_suppression_afficher_clicked()
{
    ui->contenu->setCurrentIndex(23);
    ui->tableView_affichage->setModel (P.afficher ());
}

void MainWindow::on_suppression_ajouter_clicked()
{
    ui->contenu->setCurrentIndex(20);
    ui->tableView_affichage->setModel (P.afficher ());
}

void MainWindow::on_suppression_modifier_clicked()
{
    ui->contenu->setCurrentIndex(21);
    ui->tableView_affichage_2->setModel (P.afficher ());

    ui->lineEdit_id_m->clear();
    ui->lineEdit_nom_mod->clear();
    ui->lineEdit_prix->clear();
    ui->lineEdit_qd->clear();
    ui->lineEdit_qv->clear();
    ui->lineEdit_f->clear();
}

void MainWindow::on_suppression_supprimer_clicked()
{
    ui->contenu->setCurrentIndex(22);
    ui->tableView_affichage_3->setModel (P.afficher ());

    ui->lineEdit_id_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_prix_2->clear();
    ui->lineEdit_qd_2->clear();
    ui->lineEdit_qv_2->clear();
    ui->lineEdit_categorie_2->clear();
    ui->lineEdit_f_2->clear();
}

void MainWindow::on_tableView_affichage_3_activated(const QModelIndex &index) //tableau affichage dans supprimer
{
    QString val=ui->tableView_affichage_3->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select produit.*, fournisseur.nom as fournisseur from PRODUIT join fournisseur on produit.idf=fournisseur.idf where IDP='"+val+"' or produit.NOM='"+val+"' or PRIX_U='"+val+"' or QUANTITEDISPO='"+val+"' or QUANTITEVENDUE='"+val+"' or CATEGORIE='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            ui->lineEdit_id_2->setText(qry.value(0).toString());
            ui->lineEdit_nom_2->setText(qry.value(1).toString());
            ui->lineEdit_prix_2->setText(qry.value(2).toString());
            ui->lineEdit_qd_2->setText(qry.value(3).toString());
            ui->lineEdit_qv_2->setText(qry.value(4).toString());
            ui->lineEdit_categorie_2->setText(qry.value(6).toString());
            ui->lineEdit_f_2->setText(qry.value(8).toString());

        }
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    Produit P;
   int id=ui->lineEdit_id_2->text().toInt();
   bool test=P.supprimer (id);
           //P.getID_produit());
    QMessageBox msgBox;
    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tableView_affichage_3->setModel (P.afficher ());
    ui->lineEdit_id_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_prix_2->clear();
    ui->lineEdit_qd_2->clear();
    ui->lineEdit_qv_2->clear();
    ui->lineEdit_categorie_2->clear();
    ui->lineEdit_f_2->clear();
    }

    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}

void MainWindow::on_pushButton_annuler_4_clicked()
{
    close();
}

void MainWindow::update_label_2()
{
    data2=A2.read_from_arduino();
    qDebug() << "les donees ont ete lus";
    qDebug()<< data2;
    if(data2=="1"){
        ui->fermerPorte->setVisible(true);
        qDebug() << "1 a ete recu";
        ui->label_arduino2->setText(" Detection de badge "); // si les données reçues de arduino via la liaison série sont égales à 1


     }
}

void MainWindow::on_pushButton_annuler_5_clicked()
{
    close();
}

void MainWindow::on_pushButton_arduino_clicked()
{
    ui->contenu->setCurrentIndex(24);
}

void MainWindow::on_lineEdit_Rechercher_returnPressed()
{
    QString q = ui->lineEdit_Rechercher->text();
 ui->tableView_employe->setModel(e.rechercher_Employe(q));
}

void MainWindow::on_comboBoxk_currentTextChanged(const QString &arg1)
{
    ui->tableView_employe->setModel(e.trier_employe(arg1));

}

void MainWindow::on_pushButtonk_clicked()
{
   ui->contenu->setCurrentIndex(12) ;
}

void MainWindow::on_pushButton_2k_clicked()
{

   ui->contenu->setCurrentIndex(14) ;
}

void MainWindow::on_pushButton_Generer_PDFk_clicked()
{
    e.exporterpdf(ui->textBrowser);

}

void MainWindow::on_pushButton_Generer_PDF_2k_clicked()
{
    DrilldownChart *chart = new DrilldownChart();
        chart->setTheme(QChart::ChartThemeLight);
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);





        QPieSeries *yearSeries = new QPieSeries(this);
        yearSeries->setName("stat - All");




         QSqlQuery q;
        q.exec("select nom || ' ' || prenom, heures_sup from employe");





        while(q.next()) {
            QPieSeries *series = new QPieSeries(this);


            *yearSeries << new DrilldownSlice(q.value(1).toInt(), q.value(0).toString(), series);
        }


        chart->changeSeries(yearSeries);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(0,0,650,400);
    chartView->show();
    chartView->setParent(ui->widget);

    q.exec("select nom || ' ' || prenom from employe order by heures_sup desc");
    q.next();
    QString em = q.value(0).toString();
    ui->lineEdit_em->setText(em);
    ui->contenu->setCurrentIndex(5);
}

void MainWindow::on_pushButton_ajouter_2_clicked()
{
    /*
    int ide = ui->lineEdit_ID->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_prenom->text();
    QString email = ui->lineEdit_email->text();
    QString fonction = ui->lineEdit_fonction->text();
    QString mdp = ui->lineEdit_mdp_a->text();
    int heures_sup = ui->lineEdit_heuresSup->text().toInt();
    int salaire = ui->lineEdit_salaire->text().toInt();

    if (test(mdp)!=QValidator::Acceptable) {
        QMessageBox::information(nullptr, QObject::tr("verification"),
                                    QObject::tr("pass incorrect"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
        return ;
}
*/
}

void MainWindow::on_pushButton_supprimer_2_clicked()
{
    int ide = ui->lineEdit_ides->text().toInt();

    Employe e;

    e.supprimer(ide);

  ui->tableView_employe->setModel(e.affichert());
       ui->contenu->setCurrentIndex(15);

}


void MainWindow::on_pushButton_supprimer_3_clicked()
{
    qDebug() << "modifier clicked";
    int ids = ui->lineEdit_ides->text().toInt();
   Employe e;
   QSqlQuery resultat = e.afficher(ids);
   resultat.first();
   int id = resultat.value(0).toInt();
   QString nom = resultat.value(1).toString();
   QString prenom = resultat.value(2).toString();
   QString email = resultat.value(3).toString();
   QString fonction = resultat.value(4).toString();
   int salaire = resultat.value(5).toInt();
   int heures_sup = resultat.value(6).toInt();

   ui->contenu->setCurrentIndex(13);
  ui->lineEdit_ID_2->setText(QString::number(id));
  ui->lineEdit_nom_4->setText(nom);
  ui->lineEdit_prenom_3->setText(prenom);
  ui->lineEdit_email_3->setText(email);
  ui->lineEdit_fonction_2->setText(fonction);
  ui->lineEdit_heuresSup_3->setText(QString::number(heures_sup));
  ui->lineEdit_heuresSup_4->setText(QString::number(salaire)) ;
}

void MainWindow::on_pushButton_supprimer_4_clicked()
{
    std::cout<<"hello";
   QString nom = ui->lineEdit_nom_4->text();
   QString prenom = ui->lineEdit_prenom_3->text();
   QString email = ui->lineEdit_email_3->text();
   QString fonction = ui->lineEdit_fonction_2->text();
   int heures_sup = ui->lineEdit_heuresSup_3->text().toInt();
   int salaire =  ui->lineEdit_heuresSup_4->text().toInt();
   int id =  ui->lineEdit_ID_2->text().toInt();

 std::cout << id <<std::endl;
  Employe e;
  e.modifier(heures_sup, salaire, nom, prenom, email, fonction, id);



  ui->contenu->setCurrentIndex(15);

   Employe e0;

 e0.calcul_prime(id);
 ui->tableView_employe->setModel(e0.affichert());
}

void MainWindow::on_pushButton_ajouter_2k_clicked()
{
    int ide = ui->lineEdit_IDk->text().toInt();
    QString nom = ui->lineEdit_nom_3k->text();
    QString prenom = ui->lineEdit_prenom_2k->text();
    QString email = ui->lineEdit_email_2k->text();
    QString fonction = ui->lineEdit_fonctionk->text();
    QString mdp = ui->lineEdit_mdp_ak->text();
    int heures_sup = ui->lineEdit_heuresSupk->text().toInt();
    int salaire = ui->lineEdit_salairek->text().toInt();

    if (test(mdp)!=QValidator::Acceptable) {
        QMessageBox::information(nullptr, QObject::tr("verification"),
                                    QObject::tr("pass incorrect"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
        return ;
}
    Employe e(ide, heures_sup, salaire, nom, prenom, email, fonction, mdp);
        e.ajouter();
        ui->contenu->setCurrentIndex(15);

         Employe e0;

       ui->tableView_employe->setModel(e0.affichert());
}

void MainWindow::on_pushButton_3_clicked()
{
    QString email = ui->login_email->text();
    QString mdp = ui->login_mdp->text();
     Employe e1;
   QString fonction = e1.connection(email,mdp);
   qDebug() << fonction <<email <<mdp;


   if (fonction != "") {
       loggedIn=true;
       ui->contenu->setCurrentIndex(0);
       ui->deconnection->show();
       ui->login_email->clear();
       ui->login_mdp->clear();
       e.set_fonction(fonction);
   }

   else{
       QMessageBox::information(nullptr, QObject::tr("login"),
                                   QObject::tr("email or pass incorrect"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
   }

}

void MainWindow::on_deconnection_clicked()
{
    loggedIn=false;
     ui->contenu->setCurrentIndex(25);
    ui->deconnection->hide();
}

void MainWindow::on_tableView_commande_clicked(const QModelIndex &index)
{
    int idc = index.data().toInt();
    Commande c;
    QSqlQueryModel* model = c.get_p(idc);

          ui->tableView_2->setModel(model);
}

void MainWindow::on_tableView_commande_doubleClicked(const QModelIndex &index)
{
    ui->pushButton_valideracommnde_5->show();
    ui->pushButton_supprimer_5->show();
    //clear the page
    ui->lineEdit_a_idc->setText("");
    ui->lineEdit_a_cin->setText("");
    ui->lineEdit_a_ide->setText("");
    ui->lineEdit_a_date->clear();
    ui->lineEdit_a_idp->setText("");
    ui->lineEdit_a_quantitep->setText("");
    ui->tableWidget_a_commandeProduit->setRowCount(0);
    ui->label_13->show();
    ui->checkBox_etat->show();


    //get and load the data
   int idc = index.data().toInt();
    Commande c;
    QSqlQueryModel* sqlQueryModel = c.get(false,idc);
       QString idcs = sqlQueryModel->record(0).value("idc").toString();
        QString cin = sqlQueryModel->record(0).value("client").toString();
        QString ide = sqlQueryModel->record(0).value("employe").toString();
        int etat = sqlQueryModel->record(0).value("etat").toInt();

        QDate date = sqlQueryModel->record(0).value("datec").toDate();


ui->lineEdit_a_idc->setText(idcs);
ui->lineEdit_a_cin->setText(cin);
ui->lineEdit_a_ide->setText(ide);
ui->lineEdit_a_date->setDate(date);

if (etat==1) ui->checkBox_etat->setChecked(true);
else ui->checkBox_etat->setChecked(false);



QTableWidget* table = ui->tableWidget_a_commandeProduit;

QSqlQueryModel * data = c.get_p(idc);

    for(int i = 0; i < data->rowCount(); ++i){

      table->insertRow(table->rowCount());
      table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(data->record(i).value("nom").toString()));
      table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(data->record(i).value("quantite").toString()));
    }




    ui->pushButton_supprimer->show();
    ui->contenu->setCurrentIndex(8);

}

void MainWindow::on_pushButton_ajouterCommande_clicked()
{
    ui->label_37->hide();
    ui->checkBox_etat->hide();
    ui->pushButton_supprimer_5->hide();
    ui->pushButton_valideracommnde_5->hide();
   ui->contenu->setCurrentIndex(8);
   //clear the page
   ui->lineEdit_a_idc->setText("");
   ui->lineEdit_a_cin->setText("");
   ui->lineEdit_a_ide->setText("");
   ui->lineEdit_a_date->clear();
   ui->lineEdit_a_idp->setText("");
   ui->lineEdit_a_quantitep->setText("");
   ui->tableWidget_a_commandeProduit->setRowCount(0);
    ui->checkBox_etat->setChecked(false);

}

void MainWindow::on_chercher_cursorPositionChanged(int arg1, int arg2)
{

}

void MainWindow::on_chercher_textChanged(const QString &arg1)
{
    //qDebug() << arg1;
    Commande c;
    if (!arg1.isEmpty()) {
        QSqlQueryModel* data = c.get(false,-1,-1,-1,-1,arg1);
        ui->tableView_2->setModel(c.get_p(-1)); //HAHAHAAHAHA
        ui->tableView_commande->setModel(data);
    }
    else
        ui->tableView_commande->setModel(c.get(true));
}

void MainWindow::on_filter_currentTextChanged(const QString &arg1)
{
    QString data = ui->filter->currentText();
    QSqlQueryModel* model;
    Commande c;
    if (data == "date asc") model = c.get(true,-1,-1,-1, -1,"","","asc");
    else if (data == "date desc") model = c.get(true,-1,-1,-1, -1,"","","desc");
    ui->tableView_2->setModel(c.get_p(-1)); //HAHAHAAHAHA
    ui->tableView_commande->setModel(model);
}

void MainWindow::on_afficher_coupon_4_clicked()
{
    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);





    QPieSeries *yearSeries = new QPieSeries();
    yearSeries->setName("Sales by year - All");






    const QStringList months = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };


     QSqlQuery q;
    //q.exec("select pays, count(*) from client group by pays");
    q.exec("select extract(month from datec) as month, count(*) from commande where extract(year from datec) =2000 group by extract(month from datec)");





    while(q.next()) {
        QPieSeries *series = new QPieSeries();


        *yearSeries << new DrilldownSlice(q.value(1).toInt(), months[q.value(0).toInt()-1], series);
    }


    chart->changeSeries(yearSeries);

    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->widget);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(0,0,650,400);
    chartView->show();
    ui->contenu->setCurrentIndex(5);
}

void MainWindow::on_pushButton_valideracommnde_clicked()
{
    QString idc = ui->lineEdit_a_idc->text();
    int id = ui->lineEdit_a_idc->text().toInt();
    QString client = ui->lineEdit_a_cin->text();
    QString employe = ui->lineEdit_a_ide->text();
    QString code = ui->codeCoupon_ajouter->text();
    int etat;
    if (ui->checkBox_etat->isChecked()) etat = READY;
    else etat = NOT_READY;

    QDate date = ui->lineEdit_a_date->date();
 int idcs = idc.toInt();

 Commande test;
 int cin = test.get_cin(client);
 qDebug() <<client;
 if (cin==0) ui->lineEdit_a_cin->setStyleSheet("background-color: red");
 else ui->lineEdit_a_cin->setStyleSheet("background-color: white");
 int ide = test.get_ide(employe);
 if (ide==0) ui->lineEdit_a_ide->setStyleSheet("background-color: white; color:black");
 else ui->lineEdit_a_ide->setStyleSheet("background-color: white; color:black");
    Commande c(idcs, cin, ide, etat, date, code);
    QTableWidget* table = ui->tableWidget_a_commandeProduit;
    for (int i=0;i<table->rowCount();i++){
           QString produit =  table->item(i,0)->text();
           int quantite =  table->item(i,1)->text().toInt();
           int idp = test.get_idp(produit);
             c.set_lp(idp, quantite);
    }



if (cin!=0 && ide!=0){
    if (etat == READY) { //send an sms notification if the order is ready
       QSqlQueryModel* model = c.get(idcs);
       int prev_etat = model->record(0).value("etat").toInt();
       std::cout << "ETAT" << etat;
       if (prev_etat == NOT_READY){ //check if the order wasn't ready already
           QString num = c.get_numtlf(cin);
           qDebug () << num;
           QProcess process;
           //process.start("python C:/Users/khalil/Desktop/smart_tech_2A13/sms_notification.py "+num);
           process.start("python C:/Users/khalil/Desktop/smart_tech_2A13-Integration2/sms_notification.py ");

           //process.start("python C:\Users\khalil\Desktop\smart_tech_2A13-Integration2\sms_notification.py ");
           process.waitForFinished(); // PORQEEEEEEEEEEEEEEEEEEEEEEEEEEEE MARIAAAA
       }

       }

    c.save();
    c.exporterpdf(id);
    ui->contenu->setCurrentIndex(11);

    ui->tableView_2->setModel(c.get_p(-1)); //HAHAHAAHAHA
    ui->tableView_commande->setModel(c.get(true));
}
else {
    QMessageBox::critical(nullptr, QObject::tr("Error"),
                        QObject::tr("vérifier vos informations"), QMessageBox::Cancel);
}

}

void MainWindow::on_pushButton_supprimer_5_clicked()
{
    QString idc = ui->lineEdit_a_idc->text();
    int cin = ui->lineEdit_a_cin->text().toInt();
    int ide = ui->lineEdit_a_ide->text().toInt();
    //int idp = ui->lineEdit_a_idp->text().toUInt();
    int etat=0;
    QDate date = ui->lineEdit_a_date->date();
 int idcs = idc.toInt();


    Commande c(idcs, cin, ide, etat, date);
    c.del();

    Commande c_;
    ui->tableView_commande->setModel(c_.get(true));
    ui->tableView_2->setModel(c.get_p(-1)); //HAHAHAAHAHHHAAHAHAHA
    ui->contenu->setCurrentIndex(11);

}

void MainWindow::on_pushButton_valideracommnde_5_clicked()
{
    QTextBrowser *textb;
    textb = ui->textBrowser;
    int id = ui-> lineEdit_a_idc->text().toInt();
    Commande c;
    c.exporterpdf(id);
}

void MainWindow::on_pushButton_addproduct_table_clicked()
{
    QString idp = ui->lineEdit_a_idp->text();
    Commande test;
        if(test.get_idp(idp)==0) ui->lineEdit_a_idp->setStyleSheet("background-color: red");
   else{
    ui->lineEdit_a_idp->setStyleSheet("background-color: white; color:black");
    QString quantite = ui->lineEdit_a_quantitep->text();

   QTableWidget* table = ui->tableWidget_a_commandeProduit;

   for (int i=0;i<table->rowCount();i++){
          QString produit =  table->item(i,0)->text();

          if (idp==produit){
              table->setItem(i, 1, new QTableWidgetItem(quantite));
     ui->lineEdit_a_idp->setText("");
     ui->lineEdit_a_quantitep->setText("");
              return;
          }

   }

   table->insertRow(table->rowCount());


     table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(idp));
     table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(quantite));


     ui->lineEdit_a_idp->setText("");
     ui->lineEdit_a_quantitep->setText("");
}

}

void MainWindow::on_pushButton_ajouterCommande_4_clicked()
{
    A.write_to_arduino("3");
    qDebug() << "stop pressed";
    ui->ga->setText(" pasFUITE");
}

void MainWindow::on_pushButton_ajouterCommande_3_clicked()
{
    A.write_to_arduino("2");
    qDebug() << "start pressed";
}

void MainWindow::on_pushButton_ajouterCommande_2_clicked()
{
   ui->contenu->setCurrentIndex(26) ;
}
void MainWindow::update(){

    Commande c;
    data = A.read_from_arduino();

    if (data=="1"){
    ui->ga->setText("FUITE");
        c.ajouter_gas();
          ui->table_gaz->setModel(c.afficher_gaz());

    }




}

void MainWindow::on_afficher_coupon_5_clicked()
{

   ui->contenu->setCurrentIndex(27) ;
}

void MainWindow::on_afficher_coupon_3_clicked()
{

   ui->contenu->setCurrentIndex(28) ;
}

void MainWindow::on_validerc_clicked()
{
    QDate date = ui->datec->date();
    int pourcentage = ui->pourcentage->text().toInt();
    Coupon c(pourcentage, date);
    c.ajouter();
    ui->contenu->setCurrentIndex(28);
    ui->datec->clear();
    ui->pourcentage->clear();

   ui->afficher_coupon_2->setModel(c.afficher()); //HAHAHAAHAHA

}

void MainWindow::on_pushButton_coupon_clicked()
{
   ui->contenu->setCurrentIndex(29) ;
}
