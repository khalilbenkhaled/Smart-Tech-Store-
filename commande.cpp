#include "commande.h"
#include <QDebug>
#include <iostream>

Commande::Commande(int idc, int cin, int ide, int etat, QDate date, QString code)
{
    this->idc = idc;
    this->cin = cin;
    this->ide = ide;
    this->etat = etat;
    this->date = date;
    this->code = code;
}
Commande::Commande(){

}

/*

bool Commande::ajouter(){   //TODO deal with the date

   QSqlQuery query;


   query.prepare("insert into commande(datec, etat, cin,ide, idc) values (:date, :etat, :cin, :ide, :idc)");
   query.bindValue(":idc", idc);
   query.bindValue(":ide", ide);
   query.bindValue(":cin", cin);
   query.bindValue(":etat", etat);
   query.bindValue(":date", date);


   QSqlQuery queryContenir;

    for (std::map<Produit,int>::iterator it=lp.begin(); it!=lp.end(); ++it){


          queryContenir.prepare("insert into contenir values(ide:=idp, quantite=:quantite, idc=:idc");
          queryContenir.bindValue(":idc", idc);
          queryContenir.bindValue(":idp", it->first.idp);
          queryContenir.bindValue(":quantite", it->second);
          queryContenir.exec();
   }

        return query.exec();
}



bool Commande::supprimer(int idc){

   QSqlQuery query;


   query.prepare("delete from commande where idc=:idc");

   query.bindValue(":idc", idc);

   return query.exec();
}



QSqlQueryModel* Commande::afficher(){ //TODO deal with products


   QSqlQueryModel* model = new QSqlQueryModel();



   model->setQuery("select * from commande");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("ide"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("date"));

        return model;
}



bool Commande::modifer(int cin, int ide, int etat, QString date){ //TODO deal with the date


   QSqlQuery query;


   query.prepare("update commande set cin=:cin, ide=:ide, etat=:etat, date=:date)");   // TODO: deal with the date
   query.bindValue(":ide", ide);
   query.bindValue(":cin", cin);
   query.bindValue(":etat", etat);
   query.bindValue(":date", date);

        return query.exec();
}


*/















 //JUNK

bool Commande::exists(){

   QSqlQuery query;


   query.prepare("Select idc from commande where idc=:idc");
   query.bindValue(":idc", idc);
   query.exec();

   if (query.next()) return true;
   else return false;



}



bool Commande::save(){

   QSqlQuery query;
   QSqlQuery queryContenir;


   //check if the object already exists in the database
           if (!(this->exists())){ //object does not exist
    if (code!=""){

   query.prepare("insert into commande (datec, etat, cin,ide, idc, code ) values (:date, :etat, :cin, :ide, :idc, :code)");
   query.bindValue(":idc", idc);
   query.bindValue(":ide", ide);
   query.bindValue(":cin", cin);
   query.bindValue(":etat", etat);
   query.bindValue(":date", date);
   query.bindValue(":code", code);
    }
    else{

   query.prepare("insert into commande (datec, etat, cin,ide, idc) values (:date, :etat, :cin, :ide, :idc)");
   query.bindValue(":idc", idc);
   query.bindValue(":ide", ide);
   query.bindValue(":cin", cin);
   query.bindValue(":etat", etat);
   query.bindValue(":date", date);
    }
    if (!query.exec()) return false;
}
           else{ //object exists

   query.prepare("update commande  set cin=:cin, ide=:ide, etat=:etat, datec=:date, code=:code where idc=:idc");
   query.bindValue(":ide", ide);
   query.bindValue(":idc", idc);
   query.bindValue(":cin", cin);
   query.bindValue(":etat", etat);
   query.bindValue(":date", date);
   query.bindValue(":code", code);
    if (!query.exec()) return false;

  queryContenir.prepare("delete from contenir where idc=:idc") ;
  queryContenir.bindValue(":idc",idc);
  if (!queryContenir.exec()) return false;

}

     for (std::map<Produitc,int>::iterator it=lp.begin(); it!=lp.end(); ++it){

           queryContenir.prepare("insert into contenir(idc, ide, quantite) values(:idc, :idp, :quantite)");
           queryContenir.bindValue(":idc", idc);
           queryContenir.bindValue(":idp", it->first.idp);
           queryContenir.bindValue(":quantite", it->second);
           if (!queryContenir.exec()) return false;
    }

    //do the total
    query.exec("select idc, code from commande order by idc desc");
    query.next();
    int lastId = query.value(0).toInt();
    QString codec = query.value(1).toString();
    if (codec==""){
        qDebug() <<"there is a code";
        query.prepare("update commande set total=( select sum(produit.prix_u*contenir.quantite) from contenir join produit on contenir.ide=produit.idp where contenir.idc = :idc) where commande.idc= :idc");
    }
    else{
        qDebug() <<"there is no code";
        query.prepare("select pourcentage from coupon where code=:code");
        query.bindValue(":code", code);
        query.exec();
        query.next();
        int pourcentage = query.value(0).toInt();
        query.prepare("update commande set total=(100-:pourcentage)/100*( select sum(produit.prix_u*contenir.quantite) from contenir join produit on contenir.ide=produit.idp where contenir.idc = :idc) where commande.idc= :idc");
        query.bindValue(":pourcentage", pourcentage);

    }
    query.bindValue(":idc", lastId);
    query.exec();



           return true;

}
QString Commande::get_numtlf(int cin){

   QSqlQuery q;
   q.prepare("select num_tlf from client where cin=:cin");
   q.bindValue(":cin", cin);
   q.exec();
   q.next();
   return q.value(0).toString();



}



bool Commande::del(){


   QSqlQuery query;
   QSqlQuery queryContenir;



   query.prepare("delete from commande where idc=:idc");

   query.bindValue(":idc", idc);

   queryContenir.prepare("delete from contenir where idc=:idc");

   queryContenir.bindValue(":idc", idc);

   if(!queryContenir.exec()) return false;
   if(!query.exec()) return false;
   return true;





}







QSqlQueryModel* Commande::get(bool all, int idc, int ide, int cin, int etat, QString clientName, QString employeName, QString filtered){  //TODO make this a static function //TODO deal with products


     QSqlQueryModel* model = new QSqlQueryModel();
     QString q;

           if (all){
               q = "select commande.idc, client.nom||' '||client.prenom as client,employe.nom||' '||employe.prenom as employe, to_char(commande.datec, 'MM/DD/YYYY') ,commande.etat, commande.total from commande join employe on commande.ide=employe.ide join client on client.cin=commande.cin";
}
           else if (idc!=-1){
               QString idCommande = QString::number(idc);
               q = "select commande.idc, client.nom||' '||client.prenom as client,employe.nom||' '||employe.prenom as employe,  to_char(commande.datec, 'MM/DD/YYYY') as datec,commande.etat,commande.total  from commande join employe on commande.ide=employe.ide join client on client.cin=commande.cin where idc=" + idCommande ;
}
           else if (ide!=-1){
               QString idEmploye = QString::number(ide);
               q = "select commande.idc, client.nom||' '||client.prenom as client,employe.nom||' '||employe.prenom as employe, commande.datec,commande.etat  from commande join employe on commande.ide=employe.ide join client on client.cin=commande.cin where ide=" + idEmploye ;
}
           else if (cin!=-1){
               QString idClient = QString::number(cin);
               q = "select commande.idc, client.nom||' '||client.prenom as client,employe.nom||' '||employe.prenom as employe, commande.datec,commande.etat   from commande join employe on commande.ide=employe.ide join client on client.cin=commande.cin where cin=" + idClient ;
}
           else if (etat!=-1){
               QString etatS = QString::number(etat);
               q = "select commande.idc, client.nom||' '||client.prenom as client,employe.nom||' '||employe.prenom as employe, commande.datec,commande.etat  from commande join employe on commande.ide=employe.ide join client on client.cin=commande.cin where etat=" + etatS ;
}
           else if (clientName!=""){
               q = "select commande.idc, client.nom||' '||client.prenom as client,employe.nom||' '||employe.prenom as employe, commande.datec,commande.etat  from commande join employe on commande.ide=employe.ide join client on client.cin=commande.cin  where commande.cin=(select cin from client where nom || ' ' || prenom like '%"+clientName +"%') ";
}
           else if (employeName!=""){
               q = "select commande.idc, client.nom||' '||client.prenom as client,employe.nom||' '||employe.prenom as employe, commande.datec,commande.etat    from commande join employe on commande.ide=employe.ide join client on client.cin=commande.cin  where ide=(select ide from employe where nom || ' ' || prenom like '%"+employeName +"%') ";
}
           if (filtered != ""){
                q = q + " order by datec";
                if (filtered == "asc")  q = q + " asc";
                if (filtered == "desc")  q = q + " desc";
           }



               model->setQuery(q);
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("client"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("employe"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("datec"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("total"));

                    return model;


}


 QSqlQueryModel* Commande::get_p(int idc){


     QSqlQueryModel* model = new QSqlQueryModel();
     QString idcS = QString::number(idc);
     model->setQuery("select contenir.idc, produit.nom, contenir.quantite from contenir join produit on contenir.ide=commande.idp where contenir.idc="+idcS);
     model->setQuery("select contenir.idc, produit.nom, contenir.quantite from contenir join produit on contenir.ide=produit.idp where idc="+idcS);

               model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_commande"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("produit"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));



           return model;

}


 int Commande::get_cin(QString client){

     QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select cin from client where nom||' '||prenom='"+client+"'");
   int cin =  model->record(0).value("cin").toInt();

            return cin;
 }


 int Commande::get_ide(QString employe){

     QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select ide from employe where nom||' '||prenom='"+employe+"'");
   int ide =  model->record(0).value("ide").toInt();


            return ide;

 }
 int Commande::get_idp(QString produit){


     QSqlQueryModel* model = new QSqlQueryModel();
     model->setQuery("select idp from produit where nom='"+produit+"'");
   int idp =  model->record(0).value("idp").toInt();


            return idp;




 }

 QSqlQueryModel* Commande::tri(){ //TODO deal with products


    QSqlQueryModel* model = new QSqlQueryModel();



    model->setQuery("select * from commande order by datec");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ide"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date"));

         return model;
 }

 QSqlQueryModel* Commande::recherche(QString cin){ //TODO deal with products


    QSqlQueryModel* model = new QSqlQueryModel();



    model->setQuery("select * from commande where cin like cin="+cin);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idc"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ide"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date"));

         return model;
 }



 void Commande::exporterpdf( int idc)
 {
     /*
   // QString tt;
     QSqlQuery qry;
     std::list<QString> tt;
     qry.exec("select * from client");
     Commande c;
     //commande 1
     QSqlQueryModel* m = c.get(false, idc);
     QSqlQueryModel* p = c.get_p(idc);


     QString data = "idc: "+m->record(0).value("idc").toString()+"\n"+"client: "+m->record(0).value("client").toString()+"\n"+"employe: "+m->record(0).value("employe").toString()+"\n"+"Date de creation: "+m->record(0).value("datec").toString()+"\n"+"total: "+m->record(0).value("total").toString()+"\n"+"etat: "+m->record(0).value("etat").toString()+"----------------------\nProduits";

    for(int i = 0; i < p->rowCount(); ++i){

      data += p->record(i).value("nom").toString() +" ";
      data += p->record(i).value("quantite").toString() + "\n";
    }
     text->setText(data);
*/
     QSqlQuery qry;
     std::list<QString> tt;

     Commande c;
     //commande 1
     QSqlQueryModel* m = c.get(false, idc);
     QSqlQueryModel* p = c.get_p(idc);


     QString html =
             "<style> table { font-family: arial, sans-serif; border-collapse: collapse; width: 100%; } td, th { border: 1px solid black; text-align: left; padding: 8px; } </style>"
     "<div align=right >"
        " " + m->record(0).value("datec").toString()+
     "</div>"
     "<div align=left>"
        "Client: " + m->record(0).value("client").toString() +"<br>"
        "Employe: " + m->record(0).value("employe").toString()+
     "</div>"
     "<h1 align=center>COMMANDE NUM" + m->record(0).value("idc").toString() +"</h1>"
            "<br>"
             "<br>"
     "<table align=justify  >"
             "<tr>"
               "<th>nom du produit</th>"
               "<th>quantite</th>"

             "</tr>"  ;

     for(int i = 0; i < p->rowCount(); ++i){
         html += "<tr>"
           "<td> ";
       html += p->record(i).value("nom").toString() +" </td>";
       html += " <td>" + p->record(i).value("quantite").toString() + "</td>";
       html += "</tr>";
     }




            //" </tr>"
           html += "</table>"
     "<p align=justify>"

     "</p>"
     "<div align=right>total " + m->record(0).value("total").toString() +" TND </div>";

     QTextDocument document;
     document.setHtml(html);

     QPrinter printer(QPrinter::PrinterResolution);
     printer.setOutputFormat(QPrinter::PdfFormat);
     printer.setPaperSize(QPrinter::A4);
     printer.setOutputFileName(m->record(0).value("idc").toString() + ".pdf");
     printer.setPageMargins(QMarginsF(15, 15, 15, 15));

     document.print(&printer);
 }

 void Commande::ajouter_gas(){

     QSqlQuery query;
    query.exec("select count(*) from gaz ");
    query.next();
    int n = query.value(0).toInt();
    n=n+1;





    QDate date = QDate::currentDate();


     query.prepare("insert into gaz values (:id, :date) ");
     query.bindValue(":id", n);
     query.bindValue(":date", date);
     query.exec();




 }




 QSqlQueryModel* Commande::afficher_gaz(){


    QSqlQueryModel* model = new QSqlQueryModel();



    model->setQuery("select * from gaz");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date"));


         return model;
 }




