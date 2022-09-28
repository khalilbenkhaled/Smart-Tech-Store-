#include "coupon.h"
#include <QVariant>
#include <iostream>

Coupon::Coupon()
{

}
Coupon::Coupon(int poucentage, QDate date_exp){

    string id = get_uuid();
    this->code = QString::fromStdString(id);

    this->pourcentage = poucentage;
    this->date_exp = date_exp;
}


bool Coupon::ajouter(){




    QSqlQuery query;

    query.prepare("insert into coupon(code, pourcentage, date_exp) values (:code, :pourcentage, :date_exp)");
    query.bindValue(":code", code);
    query.bindValue(":pourcentage", pourcentage);
    query.bindValue(":date_exp", date_exp);
    return query.exec();


}



bool Coupon::supprimer(){

    QSqlQuery query;
    query.prepare("delete from coupon where code='" + code +"'");
    return query.exec();
}



QSqlQueryModel* Coupon::afficher(){ //TODO deal with products


   QSqlQueryModel* model = new QSqlQueryModel();



   model->setQuery("select * from coupon");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("pourcentage"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_exp"));

        return model;
}


string get_uuid() {
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 5);

    const char *v = "abcdef";
    const bool dash[] = { 0, 0, 0, 0};

    string res;
    for (int i = 0; i < 4; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}
