#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include<QString>
#include "QSqlQuery"
#include "QSqlQueryModel"
#include <QTextBrowser>
#include <list>
#include"qrcode.h"

class fournisseur
{
public:
    void setidf(int n);
    void setnom(QString n);
    void setadresse(QString n);
    void setemail(QString n);

    int get_idf();
    QString get_nom();
    QString get_adresse();
    QString get_email();
    bool verif_email(QString);
    bool verif_nom(QString);


    QSqlQueryModel * afficher();

    fournisseur();
    bool ajouter_fournisseur();
    QSqlQueryModel * afficher_fournisseur();
    bool supprimer_fournisseur(int);
    QSqlQueryModel * afficher_listfournisseur();
    bool modifier_fournisseur(int);
    fournisseur(QString,QString,QString);
    fournisseur(int,QString,QString,QString);
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * trierfournisseur();
   QSqlQueryModel * stats();
void exporterpdf(QTextBrowser *text,int id);
private:
    QString  nom, adresse, email;
    int idf;

};

#endif // FOURNISSEUR_H

