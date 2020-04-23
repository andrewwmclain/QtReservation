#ifndef RESERVATION_MAINWINDOW_H
#define RESERVATION_MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class Reservation_MainWindow; }
QT_END_NAMESPACE

enum cardType {VISA, MasterCard, Discover, AmericanExpress};
enum roomTypes {twoQueen, oneKing};
enum roomViews {atrium, standard};

class Reservation_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Reservation_MainWindow(QWidget *parent = nullptr);
    ~Reservation_MainWindow();

    const double std2QCost = 284;
    const double atr2QCost = 325;
    const double std1KCost = 290;
    const double atr1KCost = 350;
    const double oneNightParkingCost = 12.75;
    const double oneNightResortFee = 15;

private slots:
    void on_name_plainTextEdit_textChanged();

    void on_numAdults_spinBox_valueChanged(int arg1);

    void on_numChildren_spinBox_valueChanged(int arg1);

    void on_nightsParking_SpinBox_valueChanged(int arg1);

    void on_twoQueen_radioButton_clicked();

    void on_oneKing_RadioButton_clicked();

    void on_standardView_RadioButton_clicked();

    void on_atriumView_RadioButton_clicked();

    void on_nextPg1_pushButton_clicked();

    void on_VISA_radioButton_clicked();

    void on_MasterCard_RadioButton_clicked();

    void on_Discover_RadioButton_clicked();

    void on_AmericanExpress_RadioButton_clicked();

    void on_creditCard_lineEdit_textEdited(const QString &arg1);

    void on_nextPg2_pushButton_clicked();

    void on_prevPg2_PushButton_clicked();

    void on_checkin_dateEdit_userDateChanged(const QDate &date);

    void on_checkout_dateEdit_userDateChanged(const QDate &date);

    void on_exit_pushButton_clicked();

private:
    Ui::Reservation_MainWindow *ui;

    QMessageBox q;

    QString userName;
    QDate checkInDate;
    QDate checkOutDate;
    QDate currentDate;
    QDate creditCardExpiration;

    int numDays;
    int maxGuests;
    int numGuests;
    int numAdults;
    int numChildren;
    int maxNightsParking;
    int nightsParking;

    double parkingCost;
    double roomCost;
    double subTotal;
    double roomCostPerNight;
    double tax;
    double resortFee;
    double total;

    QString cardNum;
    cardType card;
    roomTypes roomType;
    roomViews roomView;

    QPixmap logo;
    QPixmap visaLogo;
    QPixmap mastercardLogo;
    QPixmap americanExpressLogo;
    QPixmap discoverLogo;
};
#endif // RESERVATION_MAINWINDOW_H
