#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "connection.h"
#include <QMainWindow>
#include "facture.h"
#include "popup.h"
#include "QTextBrowser"
#include <QDialog>
#include "QFileDialog"
#include "QTextBrowser"
#include "QPrinter"
#include "arduino.h"
#include <sstream>


#include "employe.h"


//********************************fournisseurs****************************

#include "fournisseur.h"
#include <QFileDialog>
#include"QSqlRecord"
#include"QSqlQuery"
#include <QVariant>
#include"qrcode.h"
#include <QtPrintSupport/QPrinter>
#include <QtWidgets>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>


//****************************produit****************************************
#include <QMainWindow>
#include "produit.h"
#include "arduino.h"
#include "commande.h"
#include "coupon.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
void update_label();
    void stats(QString,QString ,int,int,QString);
    void sendMail();
     void mailSent(QString) ;

    void on_pushButton_22_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();




    void on_pushButton_ajouter_clicked();



    void on_pushButton_ajouterclient_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_24_clicked();



    void on_tabclient_activated(const QModelIndex &index);



    void on_pushButton_ajouterf_clicked();

    void on_lineEdit_cin_r_textChanged(const QString &arg1);


    void on_pushButton_6_clicked();



    void on_pushButton_genererpdf_2_clicked();



    void on_pushButton_trierclient_clicked();

    void on_afficherclient2_clicked();

    void on_pushButton_ajouterclient2_clicked();

    void on_pushButton_notifclient_clicked();

    void on_pushButton_suppclient_clicked();

    void on_pushButton_statclient_clicked();

    void on_pushButton_modifierclient_clicked();

    void on_pushButton_chercher_clicked();

    void on_chart_clicked();

    void on_mailing_clicked();

    void on_retour_clicked();

    void on_envoyer_2_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_suprimer_clicked();

    void on_pushButton_generer_clicked();

    void on_trier_clicked();

    void on_pushButton_quitter_clicked();

    void on_tableViewsql_activated(const QModelIndex &index);

//fournisseurs
    void on_qrCode_clicked();

    void on_retour_2_clicked();

    void on_modifierfournisseur_clicked();

    void on_supprimerfournisseur_clicked();

    void on_trierfournisseur_clicked();

    void on_rechercherfournisseur_2_clicked();

    void on_listefournisseur_activated(const QModelIndex &index);

    void on_fournisseurs_2_currentChanged(int index);

    void on_fournisseurs_2_tabBarClicked(int index);

    void on_localisation_clicked();

    void on_qr_code_linkActivated(const QString &link);


    void on_ajouterfournisseur_clicked();

    void on_pdffournisseur_clicked();
    void on_widget_2_customContextMenuRequested(const QPoint &pos);

    void on_widget_3_customContextMenuRequested(const QPoint &pos);

//produit/mariem


    void on_affichage_afficher_clicked();

    void on_affichage_ajouter_clicked();

    void on_affichage_modifier_clicked();

    void on_affichage_supprimer_clicked();

    void on_pushButton_tri_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_statistiques_clicked();

    void on_pushButton_annuler_2_clicked();

    void on_ajout_afficher_clicked();

    void on_ajout_ajouter_clicked();

    void on_ajout_modifier_clicked();

    void on_ajout_supprimer_clicked();

    void on_pushButton_image_clicked();

    void on_pushButton_ajouterproduit_clicked();

    void on_pushButton_annuler_clicked();

    void on_modification_afficher_clicked();

    void on_modification_ajouter_clicked();

    void on_modification_modifier_clicked();

    void on_modification_supprimer_clicked();

    void on_tableView_affichage_2_activated(const QModelIndex &index);

    void on_pushButton_modifierproduit_clicked();

    void on_pushButton_annuler_3_clicked();

    void on_lineEdit_rechercheNom_textChanged(const QString &arg1);

    void on_suppression_afficher_clicked();

    void on_suppression_ajouter_clicked();

    void on_suppression_modifier_clicked();

    void on_suppression_supprimer_clicked();

    void on_tableView_affichage_3_activated(const QModelIndex &index);

    void on_pushButton_supprimer_clicked();

    void on_pushButton_annuler_4_clicked();

    void update_label_2(); //slot permettant la mise à jour du label verification du code dans arduino2

    void on_pushButton_annuler_5_clicked();

    void on_pushButton_arduino_clicked();

    void on_lineEdit_Rechercher_returnPressed();

    void on_comboBoxk_currentTextChanged(const QString &arg1);

    void on_pushButtonk_clicked();

    void on_pushButton_2k_clicked();

    void on_pushButton_Generer_PDFk_clicked();

    void on_pushButton_Generer_PDF_2k_clicked();

    void on_pushButton_ajouter_2_clicked();

    void on_pushButton_supprimer_2_clicked();

    void on_pushButton_supprimer_3_clicked();

    void on_pushButton_supprimer_4_clicked();

    void on_pushButton_ajouter_2k_clicked();

    void on_pushButton_3_clicked();

    void on_deconnection_clicked();

    void on_tableView_commande_clicked(const QModelIndex &index);

    void on_tableView_commande_doubleClicked(const QModelIndex &index);

    void on_pushButton_ajouterCommande_clicked();

    void on_chercher_cursorPositionChanged(int arg1, int arg2);

    void on_chercher_textChanged(const QString &arg1);

    void on_filter_currentTextChanged(const QString &arg1);

    void on_afficher_coupon_4_clicked();

    void on_pushButton_valideracommnde_clicked();

    void on_pushButton_supprimer_5_clicked();

    void on_pushButton_valideracommnde_5_clicked();

    void on_pushButton_addproduct_table_clicked();

    void on_pushButton_ajouterCommande_4_clicked();

    void on_pushButton_ajouterCommande_3_clicked();

    void on_pushButton_ajouterCommande_2_clicked();
    void update();

    void on_afficher_coupon_5_clicked();

    void on_afficher_coupon_3_clicked();

    void on_validerc_clicked();

    void on_pushButton_coupon_clicked();

signals:
    void setCenter(QVariant, QVariant);
       void addMarker(QVariant, QVariant);







private:
    Ui::MainWindow *ui;
    client c;
    Facture f ;
    Employe e;
     PopUp *popUp;
     QByteArray data;
     QString serialbuffer;// variable contenant les données reçues
     Arduino A; // objet temporaire
     bool loggedIn;

     //jouhayna
     fournisseur j ;
     int compteur=0;

     //mariem
     Produit P;
     QByteArray data2; //variable contenant les données reçues
     Arduino A2; //objet temporaire
};
#endif // MAINWINDOW_H
