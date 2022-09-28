#include<ctype.h>
#include <QDebug>
#include <list>
#include "employe.h"

Employe::Employe(int i, int h, int s, QString n, QString p, QString e, QString f, QString m)
{
    ide = i;
    heures_sup = h;
    salaire = s;
    nom = n;
    prenom = p;
    email = e;
    fonction = f;
    mdp = m;
}


Employe::Employe(){

   }


bool Employe::ajouter(){
    qDebug() << "inside ajouter";
    /*
bool ver2=false,ver1=false;
   for(int i=0;i<email.length();i++)
       {
           if(email[i]=='@') {ver2=true;}
           if(email[i]=='.') {ver1=true;}

       }

   if(!ver1 || !ver2) return false;
   */


   QSqlQuery query;
   query.prepare("insert into EMPLOYE(IDE, NOM, PRENOM, EMAIL, FONCTION, SALAIRE, HEURES_SUP, PASS) values (:ide, :nom, :prenom, :email, :fonction, :salaire, :heures_sup, :pass)");

   query.bindValue(":ide",ide);
   query.bindValue(":nom", nom);
   query.bindValue(":prenom", prenom);
   query.bindValue(":email", email);
   query.bindValue(":fonction", fonction);
   query.bindValue(":salaire", salaire);
   query.bindValue(":heures_sup", heures_sup);
   query.bindValue(":pass", mdp);


  return query.exec();
}


bool Employe::supprimer(int id){

    QSqlQuery query;


    query.prepare("delete from employe where ide= :id");
    query.bindValue(":id", id);


    return query.exec();




}
QSqlQueryModel* Employe::affichert(){


   QSqlQueryModel* model = new QSqlQueryModel();



   model->setQuery("select ide,nom,prenom,email,fonction,salaire,heures_sup from employe order by ide asc");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ide"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonction"));
   model->setHeaderData(5, Qt::Horizontal, QObject::tr("salaire"));
   model->setHeaderData(6, Qt::Horizontal, QObject::tr("heures_sup"));

        return model;
}

QSqlQuery Employe::afficher(int id){


    QSqlQuery query;


    query.prepare("select * from employe where ide=:id");
    query.bindValue(":id", id);

     query.exec();
        return query;



}



bool Employe::modifier(int heures_sup, int salaire, QString nom, QString prenom, QString email, QString fonction, int ide){



    QSqlQuery query;

    query.prepare("update employe set heures_sup=:h, salaire=:s, nom=:n, prenom=:prenom, email=:email, fonction=:fonction where ide=:ide");

    query.bindValue(":h", heures_sup);
    query.bindValue(":s", salaire);
    query.bindValue(":n", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":fonction", fonction);
    query.bindValue(":ide", ide);


        return  query.exec();






}
QSqlQueryModel* Employe::trier_employe(QString q)
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT * FROM employe ORDER BY "+ q );
    return model;
}



QSqlQueryModel* Employe::rechercher_Employe(QString val)
{
 QSqlQueryModel* model=new QSqlQueryModel;
if (val!="")
model->setQuery("SELECT * FROM Employe  where  IDE  like '"+val+"'");
else
model->setQuery("SELECT * FROM Employe");
return model;
}


void Employe::exporterpdf(QTextBrowser *text)
{
  // QString tt;
    QSqlQuery qry;
    std::list<QString> tt;
    qry.exec("select * from Employe order by ide");
    while(qry.next())
    {
        tt.push_back("IDE: "+qry.value(0).toString()+"\n"+"nom: "+qry.value(1).toString()+"\n"+"prenom: "+qry.value(2).toString()+"\n"+"email: "+qry.value(3).toString()+"\n"+"fonction: "+qry.value(4).toString()+"\n"+"salaire: "+qry.value(5).toString()+"\nHeures sup:" + qry.value(5).toString());

    }

    for(std::list<QString>::iterator it =tt.begin();it!=tt.end();++it)
    {
        text->setText(text->toPlainText()+*it  + "\n ------------------------------------------ \n" );
    }

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    text->print(&printer);
}

void Employe::calcul_prime(int id){

  QSqlQuery qry;
qry.prepare("select heures_sup, salaire from employe where ide=:id ")  ;
qry.bindValue(":id", id);
qry.exec();
qry.next();

int h = qry.value(0).toInt();
int s = qry.value(1).toFloat();
qDebug() << "s"<<s<<"h"<<h;

if (h>=100) {
s = s+s*0.05;
h=h-100;
qry.prepare("update employe set heures_sup=:h, salaire=:s where ide=:id");
qry.bindValue(":id", id);
qry.bindValue(":s", s);
qry.bindValue(":h", h);
qry.exec();
}


}



QString Employe::connection(QString email, QString mdp){


   QSqlQuery q;


   q.prepare("SELECT fonction from employe where email=:email and pass=:password");
   q.bindValue(":email", email);
   q.bindValue(":password", mdp);
   q.exec();

   if (q.next()) return q.value(0).toString();
   else return "";






}








