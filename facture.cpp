#include "facture.h"
#include <QModelIndex>
#include <QItemDelegate>
#include <QSize>
#include <QSpinBox>
#include <QDebug>
#include <list>
#include <QTextBrowser>
#include "client.h"

client c;
Facture::Facture()
{


    num=0;
    quantite=1;
    tauxtva=0;
    totalht=0;
    totaltva=0;
    totalttc=0;
    cin=0;
    etat=0;

}
Facture::Facture(int num ,QString cin,int totalttc, int etat)
{
    this->num=num;
int cinn=cin.toUInt();
    this->cin=cinn;
    this->totalttc=totalttc;
    this->etat=etat;
}
void Facture::setnum(int n){num=n;}
void Facture::setdatef(QDate n){datef=n;}
void Facture::settauxtva(double n){tauxtva=n;}
void Facture::settotalht(double n){totalht=n;}
void Facture::settotaltva(double n){totaltva=n;}
void Facture::settotalttc(double n){totalttc=n;}
void Facture::setquantite(int n){quantite=n;}
void Facture::setcin(int n){cin=n;}
void Facture::setetat(int n){etat=n;}


int Facture::get_num(){return num;}
QDate Facture::get_datef(){return datef;}
double Facture::get_tauxtva(){return tauxtva;}
double Facture::get_totalht(){return totalht;}
double Facture::get_totaltva(){return totaltva;}
double Facture::get_totalttc(){return totalttc;}
int Facture::get_quantite(){return quantite;}
  int Facture::get_cin(){return cin;}
  int Facture::get_etat(){return etat;}









Facture::Facture(int num,QDate datef,double tauxtva,double totalht,double totaltva,double totalttc,int quantite,int cin,int etat)
{
 this->num=num;
 this->datef=datef;
this->tauxtva=tauxtva;
this->totalht=totalht;
this->totaltva=totaltva;
this->totalttc=totalttc;
this->quantite=quantite;
this->cin=cin;
    this->etat=etat;






}




bool Facture::ajouterf()
{

QSqlQuery query;
query.prepare("INSERT INTO facture (num, datef,  tauxtva, totalht, totaltva, totalttc, quantite, cin, etat) "
                    "VALUES (:num, :datef, :tauxtva, :totalht, :totaltva, :totalttc, :quantite, :cin, :etat)");
query.bindValue(":num", num);
query.bindValue(":datef", datef);
query.bindValue(":tauxtva", tauxtva);
query.bindValue(":totalht", totalht);
query.bindValue(":totaltva", totaltva);
query.bindValue(":totalttc", totalttc);
query.bindValue(":quantite", quantite);
query.bindValue(":cin", cin);
query.bindValue(":etat", etat);
if (etat==0)
{
    QString cinn=QString::number(cin);
    c.modifierpdf(cinn);
      return true;
}

return    query.exec();
}


QSqlQueryModel * Facture::afficherf()
{
    QSqlQueryModel * model= new QSqlQueryModel();


model->setQuery("select * from facture ");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("datef"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("tauxtva"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("totalht"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("totaltva"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("totalttc"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("quantite"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("etat"));

    return model;
}



bool Facture::supprimerf(int iddd)
{
QSqlQuery query;
QString res= QString::number(iddd);
query.prepare("Delete from facture where num = :num ");
query.bindValue(":num", res);
return    query.exec();
}




bool Facture::modifierf(int numf)
{
    QSqlQuery query;
   QString res= QString::number(numf);
   query.prepare("UPDATE facture SET num=:num, datef=:datef, tauxtva=:tauxtva, totalht=:totalht, totaltva=:totaltva, totalttc=:totalttc, quantite=:quantite, cin=:cin, etat=:etat WHERE num= '"+res+"'");
   query.bindValue(":num", num);
   query.bindValue(":datef", datef);
   query.bindValue(":tauxtva", tauxtva);
   query.bindValue(":totalht", totalht);
   query.bindValue(":totaltva", totaltva);
   query.bindValue(":totalttc", totalttc);
   query.bindValue(":quantite", quantite);
   query.bindValue(":cin", cin);
   query.bindValue(":etat", etat);


   return  query.exec();


}


QSqlQueryModel * Facture::recherchef(const QString &num)
{

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from facture where(num LIKE '"+num+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datef"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("tauxtva"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("totalht"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("totaltva"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("totalttc"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("etat"));

        return model;

}




QSqlQueryModel * Facture::afficher_facture_trierf()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from facture ORDER BY datef");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datef"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("tauxtva"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("totalht"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("totaltva"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("totalttc"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("etat"));
    return model;
}




void Facture::exporterpdff(QTextBrowser *text)
{
  // QString tt;
    QSqlQuery qry;
    std::list<QString> tt;
    qry.exec("select * from facture");
    while(qry.next())
    {
        tt.push_back("num: "+qry.value(0).toString()+"\n"+"cin: "+qry.value(7).toString()+"\n"+"quantite: "+qry.value(6).toString()+"\n"+"totalttc: "+qry.value(5).toString()+"\n"+"datef: "+qry.value(1).toString()+"\n");

    }

    for(std::list<QString>::iterator it =tt.begin();it!=tt.end();++it)
    {
    text->setText(*it);
    }

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    text->print(&printer);
}


bool Facture::checkforchar(QString x)
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


