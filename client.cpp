#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include <random>
#include <time.h>
#include <QSqlQuery>
#include <cstdlib>
#include <iostream>
#include <string>
#include <QMessageBox>
#include<ctype.h>
#include <QDebug>
#include <list>



client::client()
{
cin = 0;
nom="";
prenom="";
email="";
pays="";
num_cdf=0;
nb_point=0;
cadeau="";
adresse="";
}
client::client(int cin ,QString nom, QString prenom, QString email, QString adresse , QString pays)
{
    this->cin=cin;
    nb_point=0;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->adresse=adresse;
    this->pays=pays;

}
 QString client::get_prenom()
 {return prenom;}
 QString client::get_nom(){
     return nom;
 }
  QString client::get_email()
  {
      return email;
  }
   QString client::get_pays()
   {
       return pays;
   }
   QString client::get_adresse()
   {
       return adresse;
   }
   QString client::get_cadeau()
   {
       return cadeau;
   }

   int client::get_cin()
 {return cin;}
   int client::get_cdf()
 {return num_cdf;}
   int client::get_nbpoint()
 {return nb_point;}
 void client::setcin(int a)
 {
     this->cin=a;
 }
 void client::setcdf(int a)
 {
     this->num_cdf=a;
 }
 void client::setnb_point(int a)
 {
     this->nb_point=a;
 }
 void client::setprenom(QString m)
 {
     this->prenom=m;
 }
 void client::setnom(QString m)
 {
     this->nom=m;
 }
 void client::setemail(QString m)
 {
     this->email=m;
 }
 void client::setadresse(QString m)
 {
     this->adresse=m;
 }
 void client::setpays(QString m)
 {
     this->pays=m;
 }
 void client::setcadeau(QString m)
 {
     this->cadeau=m;
 }

bool client::ajouterclient()
{
    QSqlQuery query,querye;
    bool ver,ver1,ver_nom=true,ver_prenom=true,ver_adresse=true,ver_pays=true;
int alea,alea_cad;
    QString cad,cad1,pc,smart_phone,tv;
    QString cin_s=QString::number(cin);
    QString nb_ps=QString::number(nb_point);
    for(int i=0;i<email.length();i++)
    {
        if(email[i]=='@') {ver=true;}
        if(email[i]=='.') {ver1=true;}

    }


   srand(time(0));
alea=rand();
alea_cad=rand()%3;
   QString alea_s=QString::number(alea);
   QString num_cdf_s=QString::number(num_cdf);

for(int i=0 ;i<nom.length();i++)
{
if(nom[i].isDigit())
{ver_nom=false;
break;}
}
for(int i=0 ;i<adresse.length();i++)
{
if(adresse[i].isDigit())
{ver_adresse=false;
break;}
}
for(int i=0 ;i<pays.length();i++)
{
if(pays[i].isDigit())
{ver_pays=false;
break;}
}
for(int i=0 ;i<prenom.length();i++)
{
if(prenom[i].isDigit())
{ver_prenom=false;
break;}
}



if(ver_nom==false || ver_prenom==false || ver_pays==false || ver_adresse ==false || ver==false || ver1==false || pays.isEmpty() || adresse.isEmpty() || nom.isEmpty()||prenom.isEmpty()||email.isEmpty())
    return false;

if(alea_cad==0)
       {cad="smart_phone";}
       else if(alea_cad==1)
       {cad="pc";}
       else
       {cad="tv";}
querye.prepare("select * from client where email='"+email+"'");
querye.exec();
if(querye.next())
{return false;}




       query.prepare("INSERT INTO client (cin, nom, prenom,email,nb_point,adresse,num_cdf,pays,cadeau) "
                        "VALUES (:cin, :nom, :prenom,:email,0,:adresse,'"+alea_s+"',:pays,'"+cad+"')");
          query.bindValue(":cin", cin_s);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":email", email);
          query.bindValue(":nb_point", nb_ps);
          query.bindValue(":num_cdf", num_cdf_s);
          query.bindValue(":adresse", adresse);
          query.bindValue(":pays", pays);
          query.bindValue(":cadeau", cad);


          return query.exec();



}



QSqlQueryModel* client::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel;

     model->setQuery("SELECT *FROM client");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("email"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("adresse"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("pays"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nb_point"));


return model;
}
bool client::supprimerclient(int cin)
{
    QSqlQuery query;
QString cinc= QString::number(cin);

          query.prepare("Delete from client where cin = :cin");
          query.bindValue(":cin", cinc);
          return query.exec();
}
bool client::modifierclient(int cin ,QString nom, QString prenom, QString email, QString adresse , QString pays)
{
    bool ver,ver1;

    QSqlQuery query;
    QString cinc= QString::number(cin);

    for(int i=0;i<email.length();i++)
    {
        if(email[i]=='@') {ver=true;}
        if(email[i]=='.') {ver1=true;}

    }
if(! ver || ! ver1)
{return false;}


    for(int i=0 ;i<nom.length();i++)
    {
    if(nom[i].isDigit())
    {return false;
    break;}
    }

    for(int i=0 ;i<adresse.length();i++)
    {
    if(adresse[i].isDigit())
    {return false;
    break;}
    }

    for(int i=0 ;i<pays.length();i++)
    {
    if(pays[i].isDigit())
    {return false;
    break;}
    }
    for(int i=0 ;i<prenom.length();i++)
    {
    if(prenom[i].isDigit())
    {return false;
    break;}
    }
if(pays.isEmpty() || adresse.isEmpty() || nom.isEmpty()||prenom.isEmpty()||email.isEmpty())
    return false;


 query.prepare("UPDATE client SET nom=:nom,prenom=:prenom,email=:email,adresse=:adresse,pays=:pays  WHERE cin='"+cinc+"'");
     query.bindValue(":nom", nom);
     query.bindValue(":prenom", prenom);
     query.bindValue(":email", email);
     query.bindValue(":adresse", adresse);
     query.bindValue(":pays", pays);
    return query.exec();


}
QSqlQuery client::afficher_M(QString val)
{
    QSqlQuery query;
 query.prepare("select * from client where cin = '"+val+"'  ");
return query;
}

QSqlQueryModel* client::rechercher_clientnom(QString val)
{
 QSqlQueryModel* model=new QSqlQueryModel;
QSqlQuery queryid,querynom,queryprenom;
queryid.prepare("SELECT *FROM client  where cin = '"+val+"'");
if(queryid.exec())
model->setQuery("SELECT *FROM client  where cin = '"+val+"'");
else if(!queryid.exec())
{querynom.prepare("SELECT *FROM client  where nom = '"+val+"'");
    if(querynom.exec())
        model->setQuery("SELECT *FROM client  where nom = '"+val+"'");
}
else if(!querynom.exec())
{
    queryprenom.prepare("SELECT *FROM client  where prenom = '"+val+"'");
        if(queryprenom.exec())
    model->setQuery("SELECT *FROM client  where prenom = '"+val+"'");

}
    return model;
}

QSqlQueryModel* client::trier_client()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT *FROM client ORDER BY cin ASC ");
    return model;
}
QSqlQueryModel* client::trier_clientnom()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT *FROM client ORDER BY nom ASC ");
    return model;
}
QSqlQueryModel* client::trier_clientprenom()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT *FROM client ORDER BY prenom ASC ");
    return model;
}
QSqlQueryModel* client::trier_nb_points()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT *FROM client ORDER BY nb_point ASC ");
    return model;
}
QSqlQuery client::lawej(QString card)
{

    QSqlQuery query;
    query.prepare("select cin,nb_point from client where(card LIKE '"+card+"%')");



return query;

}

bool client::changer(QString card ,int NB_POINT)
{
    QSqlQuery query,querye;

    query.prepare("UPDATE client SET NB_POINT=:NB_POINT WHERE card='"+card+"' ");
            query.bindValue(":NB_POINT", NB_POINT);
            return query.exec();


}
int client::point_fidelite_client(QString val)
{
    int tottal=0,nb_pointf,nbp=0;
   QSqlQuery query,querye;
   query.prepare("SELECT totalttc FROM facture  where ( etat=0 AND cin='"+val+"') ORDER BY num DESC  ");
    query.exec();
    query.next();
     tottal = query.value(0).toInt();
    nb_pointf=tottal/5;
    querye.prepare("SELECT nb_point FROM client  where cin='"+val+"'");
   querye.exec();
   querye.next();
    nbp=querye.value(0).toInt();
    nbp=nb_pointf+nbp;
    return nbp;
}
bool client::modifierpdf(QString cin)
{
    int nb_pointf;
    QSqlQuery query;
    nb_pointf = point_fidelite_client(cin);
    query.prepare("UPDATE client SET nb_point=:nb_pointf WHERE cin='"+cin+"' ");
    query.bindValue(":nb_pointf",nb_pointf);
    return query.exec();
}
bool client::generercadeau(QString val) {
    int nb_pointc;
    QSqlQuery query,querye,queryee;
    query.prepare("SELECT nb_point FROM client  where cin='"+val+"'");
    if(query.exec())
    {query.next();
    nb_pointc=query.value(0).toInt();

    if(nb_pointc>=10000) {
        nb_pointc=nb_pointc-10000;
        queryee.prepare("UPDATE client SET etatcad='1' WHERE cin='"+val+"' ");
        queryee.exec();
        querye.prepare("UPDATE client SET nb_point=:nb_pointc WHERE cin='"+val+"' ");
        querye.bindValue(":nb_pointc", nb_pointc);
        querye.exec();
        return true;
    }
    }
    return false;
}
QSqlQueryModel* client::afficherlistecadeau()
{

    QSqlQueryModel* model=new QSqlQueryModel;

model->setQuery("SELECT *FROM client  where etatcad='1'");

return model;
}
int client::count_client_cad()
{
    int nb;
    QSqlQuery query;
    query.prepare("SELECT COUNT (*) FROM client where etatcad= '1' ");
    query.exec();
    query.next();
     nb= query.value(0).toInt();
    return nb;
}

void client::exporterpdf(QTextBrowser *text , QString val)
{
  // QString tt;
    QSqlQuery qry;
    std::list<QString> tt;
    qry.exec("select * from client WHERE cin='"+val+"'");
    while(qry.next())
    {
        tt.push_back("cin: "+qry.value(0).toString()+"\n"+"nom: "+qry.value(1).toString()+"\n"+"prenom: "+qry.value(2).toString()+"\n"+"email: "+qry.value(3).toString()+"\n"+"adresse: "+qry.value(4).toString()+"\n"+"nb_point: "+qry.value(5).toString()+"\n");

    }

    for(std::list<QString>::iterator it =tt.begin();it!=tt.end();++it)
    {
        text->setText(text->toPlainText()+*it);
    }

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    text->print(&printer);
}


