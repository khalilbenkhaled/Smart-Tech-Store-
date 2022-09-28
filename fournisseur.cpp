#include "fournisseur.h"
#include "QtSql"
#include "QSqlQuery"
#include <QTextBrowser>
#include "QFileDialog"
#include <QPrinter>
#include <list>
#include"qrcode.h"

fournisseur::fournisseur()
{
nom="";
adresse="";
email="";

}

fournisseur::fournisseur(QString nom, QString adresse, QString email)
{
    this->nom=nom;
    this->adresse=adresse;
    this->email=email;

}
fournisseur::fournisseur(int id,QString nom, QString adresse, QString email)
{
    this->idf=id;

    this->nom=nom;
    this->adresse=adresse;
    this->email=email;

}

void fournisseur::setidf(int n)
{idf=n;}

void fournisseur::setnom(QString n)
{nom=n;}

void fournisseur::setadresse(QString n)
{adresse=n;}

 void fournisseur::setemail(QString n)
 {email=n;}



 int fournisseur::get_idf(){return  idf;}
 QString fournisseur::get_nom(){return nom;}
 QString fournisseur::get_adresse(){return adresse;}

 QString fournisseur::get_email(){return email;}





 QSqlQueryModel * fournisseur::afficher_listfournisseur()
 {QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("SELECT * FROM FOURNISSEUR");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("idf"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("qrcode"));

     return model;
 }

 QSqlQueryModel * fournisseur::afficher()
 {QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("select * from FOURNISSEUR");



     return model;
 }

 bool fournisseur::ajouter_fournisseur()
 {
     QSqlQuery query;

     query.prepare("INSERT INTO fournisseur (idf,nom,adresse,email)"
                   "VALUES (:idf,:nom,:adresse,:email)" );
     query.bindValue(0,idf);
     query.bindValue(1,nom);
     query.bindValue(2,adresse);
     query.bindValue(3,email);

     return query.exec();

 }


 bool fournisseur::modifier_fournisseur(int idf)
 {


     QSqlQuery query;
     query.prepare("UPDATE fournisseur SET  nom=:nom, adresse=:adresse, email=:email  WHERE idf=:idf " );
     query.bindValue(":nom",nom);
     query.bindValue(":adresse",adresse);
     query.bindValue(":email",email);

     query.bindValue(":idf",idf);

     return query.exec();
 }

 bool fournisseur::supprimer_fournisseur(int idf )
 {
     QSqlQuery query ;
     query.prepare("Delete from fournisseur where idf=:idf");
     query.bindValue(0,idf);
     return query.exec();
 }



 bool fournisseur::verif_email(QString ch)
 {bool test=false ; int i,j;
  for (i=1;i<ch.length();i++)
 { if(ch[i]=='@')
      { for (j=i+1;j<ch.length();j++)
          {if ((ch[j]=='.'))
              {test=true;
                  break;}

         }}}
  return test ;


  }

 bool fournisseur::verif_nom(QString ch)
 {bool test=true ; int i;
  for (i=0;i<ch.length();i++)
 { if(ch[i] =='0' || ch[i] =='1' ||ch[i] =='2' || ch[i] =='3' || ch[i] =='4' || ch[i] =='5' || ch[i] =='6' ||  ch[i] =='7' || ch[i] =='8'
              ||ch[i] =='9' )

              {test=false;
                  break;}
}
  return test ;


  }

 QSqlQueryModel * fournisseur::rechercher(QString idf)
 {
 QSqlQueryModel * model=new QSqlQueryModel();
     QString idd=idf;
  model->setQuery("select * from FOURNISSEUR where idf='"+idd+"'");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("idf"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));


  return  model;
 }


 QSqlQueryModel* fournisseur::trierfournisseur()
 {

     QSqlQueryModel* model= new QSqlQueryModel();
     model->setQuery("SELECT* FROM FOURNISSEUR ORDER by nom");
     return model;


 }

 QSqlQueryModel * fournisseur::stats()
 {
     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("SELECT nom,email from FOURNISSEUR");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("email"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("stats"));

         return model;
 }


 void fournisseur::exporterpdf(QTextBrowser *text, int id)
 {
   // QString tt;
     QSqlQuery qry;
     std::list<QString> tt;
     qry.prepare("select * from fournisseur where idf=:idf");
     qry.bindValue(":idf",id);
     qry.exec();
     while(qry.next())
     {
 tt.push_back("idf: "+qry.value(0).toString()+"\n"+"nom: "+qry.value(1).toString()+"\n"+"adresse: "+qry.value(2).toString()+"\n"+"email: "+qry.value(3).toString()+"\n");
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
