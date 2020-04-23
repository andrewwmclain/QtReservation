#include "reservation_mainwindow.h"
#include "ui_reservation_mainwindow.h"

Reservation_MainWindow::Reservation_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Reservation_MainWindow)
{
    ui->setupUi(this);

    maxGuests = 4;
    numGuests = 1;
    numAdults = 1;
    numChildren = 0;

    numDays = 0;
    maxNightsParking = 0;
    nightsParking = 0;
    parkingCost = 0;
    roomCost = 0;
    roomCostPerNight = 0;

    currentDate.setDate(QDate::currentDate().year(),QDate::currentDate().month(), QDate::currentDate().day());
    checkInDate = currentDate;
    checkOutDate = currentDate;
    ui->checkin_dateEdit->setDate(checkInDate);
    ui->checkin_dateEdit->setMinimumDate(currentDate);
    ui->checkout_dateEdit->setDate(checkOutDate);
    ui->checkout_dateEdit->setMinimumDate(currentDate);
    ui->nightsParking_SpinBox->setMaximum(7);

    card = VISA;
    ui->VISA_radioButton->setChecked(true);
    ui->creditCard_lineEdit->setInputMask("9999-9999-9999-9999;x");
    ui->cardExpireDate_DateEdit->setMinimumDate(currentDate);

    subTotal = 0;

    logo.load(":/images/Island Resorts logo 2.PNG");
    ui->logo_label->setPixmap(logo);

    QPalette mainWindowPalette = this->palette();
    mainWindowPalette.setColor(QPalette::Window, QColor(119,216,216));
    this->setAutoFillBackground(true);
    this->setPalette(mainWindowPalette);

    this->setStyleSheet("font-family: Arial");

    visaLogo.load(":/images/VISA_logo.jpg");
    ui->VISA_label->setPixmap(visaLogo);
    ui->VISA_label->setScaledContents(true);

    mastercardLogo.load(":/images/mastercard_logo.jpg");
    ui->masterCard_label->setPixmap(mastercardLogo);
    ui->masterCard_label->setScaledContents(true);

    americanExpressLogo.load(":/images/American_Express_logo.png");
    ui->americanExpress_label->setPixmap(americanExpressLogo);
    ui->americanExpress_label->setScaledContents(true);

    discoverLogo.load(":/images/discover_logo.png");
    ui->discover_label->setPixmap(discoverLogo);
    ui->discover_label->setScaledContents(true);

    ui->nextPg1_pushButton->setStyleSheet("background-color: #eff3c6");
    ui->prevPg2_PushButton->setStyleSheet("background-color: #eff3c6");
    ui->nextPg2_pushButton->setStyleSheet("background-color: #eff3c6");
    ui->exit_pushButton->setStyleSheet("background-color: #eff3c6");
}

Reservation_MainWindow::~Reservation_MainWindow()
{
    delete ui;
}


void Reservation_MainWindow::on_name_plainTextEdit_textChanged()
{
    userName = ui->name_plainTextEdit->toPlainText();
}

void Reservation_MainWindow::on_numAdults_spinBox_valueChanged(int arg1)
{
    if(arg1 + numChildren > maxGuests){
        q.setText("Too many guests selected. Max of 3 for 1 King. Max of 4 for 2 Queen.");
        q.exec();
    }
    else{
        numAdults = arg1;
        numGuests = numAdults + numChildren;
        ui->numChildren_spinBox->setMaximum(maxGuests - numAdults);
    }
}

void Reservation_MainWindow::on_numChildren_spinBox_valueChanged(int arg1)
{
    if(arg1 + numAdults > maxGuests){
        q.setText("Too many guests selected. Max of 3 for 1 King. Max of 4 for 2 Queen.");
        q.exec();
    }
    else{
        numChildren = arg1;
        numGuests = numAdults + numChildren;
        ui->numAdults_spinBox->setMaximum(maxGuests - numChildren);
    }
}

void Reservation_MainWindow::on_nightsParking_SpinBox_valueChanged(int arg1)
{
    nightsParking = arg1;
    parkingCost = nightsParking * oneNightParkingCost;
    subTotal = roomCost + parkingCost;
    QString subTotalStr = "Subtotal: $" + QString::number(subTotal, 'f', 2);
    ui->subtotal_label->setText(subTotalStr);
}

void Reservation_MainWindow::on_twoQueen_radioButton_clicked()
{
    roomType = twoQueen;

    maxGuests = 4;
    ui->numAdults_spinBox->setMaximum(maxGuests - numChildren);
    ui->numChildren_spinBox->setMaximum(maxGuests - numAdults);

    if(numGuests > 4){
        numGuests = 4;
        if(numAdults > maxGuests){
            numAdults = maxGuests;
        }
        numChildren = maxGuests - numAdults;
        q.setText("Too many guests selected. Max of 3 for 1 King. Max of 4 for 2 Queen.");
        q.exec();
    }
    else{
        if(ui->atriumView_RadioButton->isChecked()){
            roomCostPerNight = atr2QCost;
        }
        else if(ui->standardView_RadioButton->isChecked()){
            roomCostPerNight = std2QCost;
        }
        roomCost = roomCostPerNight * numDays;
        subTotal = roomCost + parkingCost;
        QString subTotalStr = "Subtotal: $" + QString::number(subTotal, 'f', 2);
        ui->subtotal_label->setText(subTotalStr);
    }

}

void Reservation_MainWindow::on_oneKing_RadioButton_clicked()
{
    roomType = oneKing;

    maxGuests = 3;
    ui->numAdults_spinBox->setMaximum(maxGuests - numChildren);
    ui->numChildren_spinBox->setMaximum(maxGuests - numAdults);

    if(numGuests > 3){
        if(numAdults > maxGuests){
            numAdults = maxGuests;
        }
        numChildren = maxGuests - numAdults;
        q.setText("Too many guests selected. Max of 3 for 1 King. Max of 4 for 2 Queen.");
        q.exec();
    }
    else{
        if(ui->atriumView_RadioButton->isChecked()){
            roomCostPerNight = atr1KCost;
        }
        else if(ui->standardView_RadioButton->isChecked()){
            roomCostPerNight = std1KCost;
        }
        roomCost = roomCostPerNight * numDays;
        subTotal = roomCost + parkingCost;
        QString subTotalStr = "Subtotal: $" + QString::number(subTotal, 'f', 2);
        ui->subtotal_label->setText(subTotalStr);
    }
}

void Reservation_MainWindow::on_standardView_RadioButton_clicked()
{
    roomView = standard;

    if(ui->oneKing_RadioButton->isChecked()){
        roomCostPerNight = std1KCost;
    }
    else if(ui->twoQueen_radioButton->isChecked()){
        roomCostPerNight = std2QCost;
    }
    roomCost = numDays * roomCostPerNight;
    subTotal = roomCost;
    QString subTotalStr = "Subtotal: $" + QString::number(subTotal, 'f', 2);
    ui->subtotal_label->setText(subTotalStr);
}

void Reservation_MainWindow::on_atriumView_RadioButton_clicked()
{
    roomView = atrium;

    if(ui->oneKing_RadioButton->isChecked()){
        roomCostPerNight = atr1KCost;
    }
    else if(ui->twoQueen_radioButton->isChecked()){
        roomCostPerNight = atr2QCost;
    }
    roomCost = numDays * roomCostPerNight;
    subTotal = roomCost + parkingCost;
    QString subTotalStr = "Subtotal: $" + QString::number(subTotal, 'f', 2);
    ui->subtotal_label->setText(subTotalStr);
}

void Reservation_MainWindow::on_nextPg1_pushButton_clicked()
{
    if(userName.size() == 0){
        q.setText("Please enter a name for the reservation.");
        q.exec();
    }
    else if(numGuests > maxGuests){
        q.setText("Too many guests for room type.");
        q.exec();
    }
    else if(numAdults < 1){
        q.setText("Minimum of 1 adult.");
        q.exec();
    }
    else if(!(ui->twoQueen_radioButton->isChecked()) && !(ui->oneKing_RadioButton->isChecked())){
        q.setText("Select room size.");
        q.exec();
    }
    else if(!(ui->atriumView_RadioButton->isChecked()) && !(ui->standardView_RadioButton->isChecked())){
        q.setText("Select view type.");
        q.exec();
    }
    else if(numDays < 1){
        q.setText("Minimum stay is at least one night.");
        q.exec();
    }
    else if(numDays > 7){
        q.setText("Maximum stay is 7 nights.");
        q.exec();
    }
    else if(nightsParking > maxNightsParking){
        q.setText("Parking cannot exceed stay length.");
        q.exec();
    }
    else{
        QString roomCostStr = "Room Cost: $" + QString::number(roomCost, 'f', 2);
        ui->roomCost_label->setText(roomCostStr);

        tax = 0.15 * roomCost;
        QString taxStr = "Tax: $" + QString::number(tax, 'f', 2);
        ui->tax_Label->setText(taxStr);

        QString parkingFeeStr = "Parking Fee: $" + QString::number(parkingCost, 'f', 2);
        ui->parkingFee_Label->setText(parkingFeeStr);

        resortFee = oneNightResortFee * numDays;
        QString resortFeeStr = "Resort Fee: $" + QString::number(resortFee, 'f', 2);
        ui->resortFee_Label->setText(resortFeeStr);

        total = subTotal + tax + resortFee;
        QString totalStr = "Total Due: $" + QString::number(total, 'f', 2);
        ui->totalDue_Label->setText(totalStr);

        ui->stackedWidget->setCurrentIndex(1);
    }
}

void Reservation_MainWindow::on_VISA_radioButton_clicked()
{
    cardNum.clear();
    card = VISA;
    ui->creditCard_lineEdit->clearMask();
    ui->creditCard_lineEdit->clear();
    ui->creditCard_lineEdit->setInputMask("9999-9999-9999-9999;x");
}

void Reservation_MainWindow::on_MasterCard_RadioButton_clicked()
{
    cardNum.clear();
    card = MasterCard;
    ui->creditCard_lineEdit->clearMask();
    ui->creditCard_lineEdit->clear();
    ui->creditCard_lineEdit->setInputMask("9999-9999-9999-9999;x");
}

void Reservation_MainWindow::on_Discover_RadioButton_clicked()
{
    cardNum.clear();
    card = Discover;
    ui->creditCard_lineEdit->clearMask();
    ui->creditCard_lineEdit->clear();
    ui->creditCard_lineEdit->setInputMask("9999-9999-9999-9999;x");
}

void Reservation_MainWindow::on_AmericanExpress_RadioButton_clicked()
{
    cardNum.clear();
    card = AmericanExpress;
    ui->creditCard_lineEdit->clearMask();
    ui->creditCard_lineEdit->clear();
    ui->creditCard_lineEdit->setInputMask("9999-999999-99999;x");
}

void Reservation_MainWindow::on_creditCard_lineEdit_textEdited(const QString &arg1)
{
    cardNum = arg1;
}

void Reservation_MainWindow::on_nextPg2_pushButton_clicked()
{
    switch(card){
        case AmericanExpress:
        if(cardNum.size() != 17 || cardNum.at(0) != '3'){
            q.setText("Invalid card number");
            q.exec();
            return;
        };
        break;

        case VISA:
        if(cardNum.size() != 19 || cardNum.at(0) != '4'){
            q.setText("Invalid card number");
            q.exec();
            return;
        };
        break;

        case MasterCard:
        if(cardNum.size() != 19 || cardNum.at(0) != '5'){
            q.setText("Invalid card number");
            q.exec();
            return;
        };
        break;

        case Discover:
        if(cardNum.size() != 19 || cardNum.at(0) != '6'){
            q.setText("Invalid card number");
            q.exec();
            return;
        };
        break;
    }
    q.setText("Transaction successfully processed!");
    q.exec();

    ui->checkInDatePg3_label->setText("Check-in Date: " + checkInDate.toString());
    ui->checkOutDatePg3_Label->setText("Check-out Date: " + checkOutDate.toString() + " (" +
                                       QString::number(numDays) + " night(s))" );
    if(roomType == twoQueen){
        if(roomView == standard){
            ui->roomTypePg3_Label->setText("Room Type: 2 Queen (Standard View)");
        }
        else{
            ui->roomTypePg3_Label->setText("Room Type: 2 Queen (Atrium View)");
        }
    }
    else{
        if(roomView == standard){
            ui->roomTypePg3_Label->setText("Room Type: 1 King (Standard View)");
        }
        else{
            ui->roomTypePg3_Label->setText("Room Type: 1 King (Atrium View)");
        }
    }

    ui->parkingPg3_Label->setText("Parking: " + QString::number(nightsParking) + " night(s)");
    ui->guestsPg3_Label->setText("Guests: " + QString::number(numAdults) + " adults, " +
                                 QString::number(numChildren) + " children");

    ui->totalCostPg3_Label->setText("Total: $" + QString::number(total, 'f', 2));
    ui->cardNumPg3_Label->setText("Paid with card ending in: " +
                                  cardNum.right(4));

    ui->stackedWidget->setCurrentIndex(2);
}

void Reservation_MainWindow::on_prevPg2_PushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Reservation_MainWindow::on_checkin_dateEdit_userDateChanged(const QDate &date)
{
    checkInDate.setDate(date.year(), date.month(), date.day());

    if(checkInDate > checkOutDate){
        checkOutDate = checkInDate;
        ui->checkout_dateEdit->setDate(checkOutDate);
    }

    numDays = checkInDate.daysTo(checkOutDate);
    maxNightsParking = numDays;

    roomCost = numDays * roomCostPerNight;
    subTotal = parkingCost + roomCost;

    QString subTotalStr = "Subtotal: $" + QString::number(subTotal, 'f', 2);
    ui->subtotal_label->setText(subTotalStr);
    QString numNightsStr = QString::number(numDays) + " Night(s)";
    ui->numDays_Label->setText(numNightsStr);
}

void Reservation_MainWindow::on_checkout_dateEdit_userDateChanged(const QDate &date)
{
    checkOutDate.setDate(date.year(), date.month(), date.day());

    if(checkOutDate < checkInDate){
        checkInDate = checkOutDate;
        ui->checkin_dateEdit->setDate(checkInDate);
    }

    numDays = checkInDate.daysTo(checkOutDate);
    maxNightsParking = numDays;

    roomCost = numDays * roomCostPerNight;
    subTotal = parkingCost + roomCost;

    QString subTotalStr = "Subtotal: $" + QString::number(subTotal, 'f', 2);
    ui->subtotal_label->setText(subTotalStr);
    QString numNightsStr = QString::number(numDays) + " Night(s)";
    ui->numDays_Label->setText(numNightsStr);
}

void Reservation_MainWindow::on_exit_pushButton_clicked()
{
    close();
}
