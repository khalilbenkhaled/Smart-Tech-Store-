#include "produit.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlRecord>



Produit::Produit()
{
//ID_produit=0;
Nom_produit="";
Prix_unitaire=0;
Quantite_disponible=0;
Quantite_vendue=0;
Idf=0;
Categorie_produit="";
Image="";
}

Produit::Produit(int id,QString nom, double prixU, int qd, int qv, int idf,QString categorie, QString im)
{
   ID_produit=id;
    Nom_produit=nom;
    Prix_unitaire=prixU;
    Quantite_disponible=qd;
    Quantite_vendue=qv;
    Idf=idf;
    Categorie_produit=categorie;
    Image=im;
}

void Produit::setID_produit(int n){ID_produit=n;}
void Produit::setNom_produit(QString n){Nom_produit=n;}
void Produit::setPrix_unitaire(double n){Prix_unitaire=n;}
void Produit::setQuantite_disponible(int n){Quantite_disponible=n;}
void Produit::setQuantite_vendue(int n){Quantite_vendue=n;}
void Produit::setCategorie_produit(QString n){Categorie_produit=n;}
void Produit::setImage(QString n){Image=n;}

int Produit::getID_produit(){return ID_produit;}
QString Produit::getNom_produit(){return Nom_produit;}
double Produit::getPrix_unitaire(){return Prix_unitaire;}
int Produit::getQuantite_disponible(){return Quantite_disponible;}
int Produit::getQuantite_vendue(){return Quantite_vendue;}
QString Produit::getCategorie_produit(){return Categorie_produit;}
QString Produit::getImage(){return Image;}

bool Produit::ajouter()
{
    QSqlQuery query;
       // QString id_string= QString::number(ID_produit);
             query.prepare("insert into PRODUIT (IDP,NOM,PRIX_U,QUANTITEDISPO,QUANTITEVENDUE,IDF,CATEGORIE,IMAGE)VALUES (:ID_produit,:Nom_produit,:Prix_unitaire,:Quantite_disponible,:Quantite_vendue,:Idf,:Categorie_produit,:Image)");
             query.bindValue(":ID_produit", ID_produit);
             query.bindValue(":Nom_produit", Nom_produit);
             query.bindValue(":Prix_unitaire", Prix_unitaire);
             query.bindValue(":Quantite_disponible", Quantite_disponible);
             query.bindValue(":Quantite_vendue", Quantite_vendue);
             query.bindValue(":Categorie_produit", Categorie_produit);
             query.bindValue(":Idf", Idf);
             query.bindValue(":Image", Image);

        return query.exec();
}

QSqlQueryModel *Produit::afficher()

{
QSqlQueryModel* model=new QSqlQueryModel();
     model->setQuery("SELECT* FROM PRODUIT");
     model->setHeaderData (0, Qt:: Horizontal,QObject::tr ("ID"));
     model->setHeaderData (1, Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData (2, Qt:: Horizontal,QObject::tr ("Prix Unitaire"));
     model->setHeaderData (3, Qt:: Horizontal,QObject::tr ("Quantité disponible"));
     model->setHeaderData (4, Qt:: Horizontal,QObject::tr ("Quantité vendue"));
     model->setHeaderData (5, Qt:: Horizontal,QObject::tr ("ID fournisseur"));
     model->setHeaderData (6, Qt:: Horizontal,QObject::tr ("Catégorie"));
     model->setHeaderData (7, Qt:: Horizontal,QObject::tr ("Image "));




     return model;
}

bool Produit::modifier(int ID_produit)
{
    QSqlQuery query;
    //QString res=QString::number(id);
    query.prepare("Update PRODUIT set NOM=:Nom_produit ,PRIX_U =:Prix_unitaire , QUANTITEDISPO=:Quantite_disponible , QUANTITEVENDUE=:Quantite_vendue , IDF=:Idf ,CATEGORIE=:Categorie_produit where IDP =:id ");
    query.bindValue(":id",ID_produit);
    query.bindValue(":Nom_produit",Nom_produit);
    query.bindValue(":Prix_unitaire",Prix_unitaire);
    query.bindValue(":Quantite_disponible",Quantite_disponible);
    query.bindValue(":Quantite_vendue",Quantite_vendue);
    query.bindValue(":Categorie_produit",Categorie_produit);
    query.bindValue(":Idf", Idf);


return    query.exec();
}

bool Produit::supprimer(int id)
{
    QSqlQuery query;
          query.prepare("Delete from PRODUIT where IDP=:id");
          query.bindValue (":id", id);
         return query.exec();
}

int Produit::getIdf(QString nomf)//Tekhou esm fournisseur w trajaalk el id mteeo
{


     QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select IDF from FOURNISSEUR where NOM='"+nomf+"'");
   int idf =  model->record(0).value("IDF").toInt();

   return idf;

 }

QSqlQueryModel* Produit::afficherP(){


     QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select PRODUIT.IDP,PRODUIT.NOM, PRODUIT.PRIX_U, PRODUIT.QUANTITEDISPO, PRODUIT.QUANTITEVENDUE, PRODUIT.CATEGORIE, FOURNISSEUR.NOM  "
                     "from PRODUIT join FOURNISSEUR on FOURNISSEUR.IDF=PRODUIT.IDF "
                     "where  PRODUIT.IDP=:id");
     model->setHeaderData (0, Qt:: Horizontal,QObject::tr ("ID"));
     model->setHeaderData (1, Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData (2, Qt:: Horizontal,QObject::tr ("Prix Unitaire"));
     model->setHeaderData (3, Qt:: Horizontal,QObject::tr ("Quantité disponible"));
     model->setHeaderData (4, Qt:: Horizontal,QObject::tr ("Quantité vendue"));
     model->setHeaderData (5, Qt:: Horizontal,QObject::tr ("ID fournisseur"));
     model->setHeaderData (6, Qt:: Horizontal,QObject::tr ("Image "));
     model->setHeaderData (7, Qt:: Horizontal,QObject::tr ("Catégorie"));


    return model;

}

 QSqlQueryModel *Produit::afficher_nomrecherche(QString nom)
{
        QString res= nom;
        QSqlQueryModel *model=new QSqlQueryModel();
         model->setQuery("SELECT * FROM produit  WHERE nom like '%"+nom+"%'" );
         model->setHeaderData (0, Qt:: Horizontal,QObject::tr ("ID"));
         model->setHeaderData (1, Qt::Horizontal,QObject::tr("Nom"));
         model->setHeaderData (2, Qt:: Horizontal,QObject::tr ("Prix Unitaire"));
         model->setHeaderData (3, Qt:: Horizontal,QObject::tr ("Quantité disponible"));
         model->setHeaderData (4, Qt:: Horizontal,QObject::tr ("Quantité vendue"));
         model->setHeaderData (5, Qt:: Horizontal,QObject::tr ("ID fournisseur"));
         model->setHeaderData (6, Qt:: Horizontal,QObject::tr ("Image "));
         model->setHeaderData (7, Qt:: Horizontal,QObject::tr ("Catégorie"));

         return model;
   }

 QSqlQueryModel * Produit::tri_ID()
 {
     QSqlQueryModel * model =new QSqlQueryModel();
     model->setQuery("SELECT * FROM produit ORDER  BY CAST (IDP as number) ");
     model->setHeaderData (0, Qt:: Horizontal,QObject::tr ("ID"));
     model->setHeaderData (1, Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData (2, Qt:: Horizontal,QObject::tr ("Prix Unitaire"));
     model->setHeaderData (3, Qt:: Horizontal,QObject::tr ("Quantité disponible"));
     model->setHeaderData (4, Qt:: Horizontal,QObject::tr ("Quantité vendue"));
     model->setHeaderData (5, Qt:: Horizontal,QObject::tr ("ID fournisseur"));
     model->setHeaderData (6, Qt:: Horizontal,QObject::tr ("Image "));
     model->setHeaderData (7, Qt:: Horizontal,QObject::tr ("Catégorie"));
     return model;

 }

 bool Produit::checkint(QString x) //verifier si la valeur saisie est int ou float
 {
 bool check=true;
 if(x.isEmpty())
 {
     check=false;
     return check;
     }
 else
 {
     for(int i=0;i<x.size();i++)
     {

       if(x[i].isLetter()&&x[i]!=","&&x[i]!=".")
         {
          check=false;
          break;
         }
     }
 }

 return check;

 }

 bool Produit::checkchar(QString x) //verifier si la valeur est string
 {
 bool check=true;
 if(x.isEmpty())
 {
     check=false;
     return check;
     }
 else
 {
     for(int i=0;i<x.size();i++)
     {

         if(x[i].isDigit())
         {
          check=false;
          break;
         }
     }
 }

 return check;

 }

 void Produit::statistique(QVector<double>* ticks,QVector<QString> *labels)
 {
     QSqlQuery q;
     int i=0;
     q.exec("select NOM from PRODUIT");
     while (q.next())
     {
         QString identifiant = q.value(0).toString();
         i++;
         *ticks<<i;
         *labels <<identifiant;
     }
 }

