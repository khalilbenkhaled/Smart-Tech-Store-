#ifndef COUPON_H
#define COUPON_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <iostream>
#include <QSqlQueryModel>
#include <iostream>
#include <string>
using namespace std;
using namespace  std;
class Coupon
{
   QString code;
   int pourcentage;
   QDate date_exp;

public:
    Coupon(int, QDate);
    Coupon();
    bool ajouter();
    bool supprimer();
    QSqlQueryModel* afficher();


};




string get_uuid();

#endif // COUPON_H
