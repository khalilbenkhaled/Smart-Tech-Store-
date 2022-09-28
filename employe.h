#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <iostream>


#include "QTextBrowser"
#include <QTextBrowser>
#include <QPrinter>
#include "QFileDialog"
class Employe
{

public:
    int ide, heures_sup;
    int salaire;
    QString nom, prenom, email, fonction, mdp;

public:
    Employe(int i, int h, int s, QString n, QString p, QString e, QString f, QString m);
    Employe();
    int get_ide(){ return ide; }






    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* affichert();
    QSqlQuery afficher(int id);
    void set_fonction(QString f){ fonction=f; };
    QString get_fonction(){ return fonction; };

    bool modifier(int heures_sup, int salaire, QString nom, QString prenom, QString email, QString fonction, int id);





QSqlQueryModel* trier_employe(QString q);

QSqlQueryModel* rechercher_Employe(QString);


void exporterpdf(QTextBrowser *text);

void calcul_prime(int id);
QString connection(QString email, QString mdp);

};

#endif // EMPLOYE_H
