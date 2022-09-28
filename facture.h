#ifndef FACTURE_H
#define FACTURE_H
#include<QString>
#include "QDate"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "QFileDialog"
#include "QTextBrowser"
#include <QPrinter>
#include "client.h"




class Facture
{
public:
    Facture();
    client c;
    Facture(int,QDate,double,double,double,double,int,int,int);
    Facture(int,QString,int,int);

       void setnum(int n);
       void setdatef(QDate n);
       void settauxtva(double n);
       void settotalht(double n);
       void settotaltva(double n);
       void settotalttc(double n);
       void setquantite(int n);
       void setcin(int n);
       void setetat(int n);
       int get_num();
       QDate get_datef();
       double get_tauxtva();
       double get_totalht();
       double get_totaltva();
       double get_totalttc();
        int get_quantite();
         int get_cin();
         int get_etat();

    bool ajouterf();
    QSqlQueryModel * afficherf();
    bool supprimerf(int);
    bool modifierf(int );
    QSqlQueryModel * recherchef(const QString &num);
    QSqlQueryModel *afficher_facture_trierf();
    void exporterpdff(QTextBrowser *text);
    bool checkforchar(QString);


private:

    int num;
    QDate datef;
    double tauxtva;
    double totalht;
    double totaltva;
    double totalttc;
   int quantite;
   int cin;
   int etat;






















};

#endif // FACTURE_H
