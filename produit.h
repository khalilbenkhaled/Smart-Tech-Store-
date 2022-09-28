#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVector>

class Produit
{
public:
    //setters
    void setID_produit(int n);
    void setNom_produit(QString n);
    void setPrix_unitaire(double n);
    void setQuantite_disponible(int n);
    void setQuantite_vendue(int n);
    void setCategorie_produit(QString n);
    void setImage(QString n);

    //getters
    int getID_produit();
    QString getNom_produit();
    double  getPrix_unitaire();
    int getQuantite_disponible();
    int getQuantite_vendue();
    QString getCategorie_produit();
    QString getImage();

    int getIdf(QString nomf);

    //constructeurs
    Produit();
    Produit(int,QString, double, int, int,int,QString,QString);


    //CRUD
    bool ajouter();
    QSqlQueryModel * afficher ();
    bool supprimer (int);
    bool modifier (int);

    QSqlQueryModel * afficherP ();

    QSqlQueryModel * afficher_nomrecherche(QString);
    QSqlQueryModel * tri_ID();

    void on_lineEdit_rechercheN_textChanged(const QString &arg1);

    bool checkchar(QString);
    bool checkint(QString);

     void statistique(QVector<double>* ticks,QVector<QString> *labels);






private:
    QString Nom_produit,Categorie_produit;
    int ID_produit,Quantite_disponible,Quantite_vendue;
    double Prix_unitaire;
    int Idf;
    QString Image;


};

#endif // PRODUIT_H
