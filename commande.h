#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <map>
#include <QDate>
#include <QTextBrowser>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>

#define READY 1
#define NOT_READY 0

class Produitc{
public:
   int idp;
   QString nom;


    bool operator<(const Produitc& other) const{
        return idp < other.idp ;
    }
};

class Commande
{


    int idc, cin, ide, etat;
    QString code;
    QDate date;
    std::map<Produitc,int> lp;
public:
    Commande(int idc, int cin, int ide, int etat, QDate date, QString code="");
    Commande();

    //getters
    int get_idc(){ return idc; }
    int get_cin(){ return cin; }
    int get_ide(){ return ide; }
    int get_cin(QString client);  //change
    int get_ide(QString employe); //change
    //aa
    int get_idp(QString produit);
    int  get_etat(){ return etat; }
    QDate get_date(){ return date; }
    std::map<Produitc,int> get_lp(){ return lp;}

    //setters


    void set_cin(int cin){ this->cin = cin; }
    void set_ide(int ide){ this->ide = ide; }
    void set_etat(int etat){ this->etat = etat; }
    void set_date(QDate date){ this->date = date; }
    void set_lp(int id, int quantite){
        Produitc e;
        e.idp = id;
        this->lp[e] = quantite;
    }
/*
    bool ajouter();
    bool supprimer(int idc);
    QSqlQueryModel* afficher();
    bool modifer(int cin, int ide, int etat, QString date);

*/


    //junk


    bool save();
    bool del();
    bool exists();
    QSqlQueryModel* get_p(int idc);
     QSqlQueryModel* recherche(QString cin);
      QSqlQueryModel* tri();
QSqlQueryModel* get(bool all=false, int idc=-1, int ide=-1, int cin=-1, int etat=-1, QString clientName="", QString employeName="", QString filtered="");  //TODO make this a static function //TODO deal with products
 void exporterpdf(  int idc=-1);
    //TODO afficher (static and non static
 QString get_numtlf(int cin);
void ajouter_gas();

 QSqlQueryModel* afficher_gaz();
};

#endif // COMMANDE_H






