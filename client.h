#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQueryModel>
#include <QTextBrowser>
#include <QPrinter>
#include "QFileDialog"

class client
{
public:

    client();
    client(int, QString , QString , QString , QString , QString );
    void setprenom(QString m);
    void setnom(QString m);
    void setemail(QString m);
    void setadresse(QString m);
    void setpays(QString m);
    void setcadeau(QString m);

    void setcin(int a);
    void setnb_point(int a);
    void setcdf(int a);

    QString get_prenom();
    QString get_nom();
    QString get_email();
    QString get_adresse();
    QString get_cadeau();
    QString get_pays();
    int get_cin();
    int get_cdf();
    int get_nbpoint();
    bool modifierclient(int, QString , QString , QString , QString , QString );
    bool ajouterclient();
    bool supprimerclient(int );
    bool supprimer_check(int);
    QSqlQuery afficher_M(QString);
QSqlQueryModel* afficher();
QSqlQueryModel* rechercher_client(QString);
QSqlQueryModel* rechercher_clientnom(QString);
QSqlQueryModel* rechercher_clientprenom(QString);
QSqlQueryModel* trier_client();
QSqlQueryModel* trier_clientnom();
QSqlQueryModel* trier_clientprenom();
QSqlQueryModel* trier_nb_points();
int point_fidelite_client(QString);
bool modifierpdf(QString );
bool generercadeau(QString);
QSqlQueryModel* afficherlistecadeau();
int count_client_cad();
void exporterpdf(QTextBrowser *text , QString);
QSqlQuery  lawej(QString card);
bool changer(QString card ,int NB_POINT);
private:
    QString prenom,nom,email,adresse,pays,cadeau;
    int cin,nb_point,num_cdf;

};

#endif // CLIENT_H
