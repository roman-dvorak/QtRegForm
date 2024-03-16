#include "regWindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QComboBox>
#include <QDateEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>


regWindow::regWindow(QWidget *parent) : QWidget(parent)
{

    this->setWindowTitle("Registration Form");   
    QVBoxLayout* gridLayout = new QVBoxLayout();


    QHBoxLayout* hLayout1 = new QHBoxLayout();
    lineEditName = new QLineEdit();
    lineEditName->setPlaceholderText("Name");
    hLayout1->addWidget(new QLabel("Name:"));
    hLayout1->addWidget(lineEditName);
    gridLayout->addLayout(hLayout1);
    
    QHBoxLayout* hLayout2 = new QHBoxLayout();
    lineEditSurname = new QLineEdit();
    lineEditSurname->setPlaceholderText("Surname");
    hLayout2->addWidget(new QLabel("Surname:"));
    hLayout2->addWidget(lineEditSurname);
    gridLayout->addLayout(hLayout2);

    QHBoxLayout* hLayout3 = new QHBoxLayout();
    lineEditEmail = new QLineEdit();
    lineEditEmail->setText("@");
    hLayout3->addWidget(new QLabel("Email:"));
    hLayout3->addWidget(lineEditEmail);
    gridLayout->addLayout(hLayout3);

    QHBoxLayout* hLayout4 = new QHBoxLayout();
    radioButtonMale = new QRadioButton();
    radioButtonMale->setText("Male");
    radioButtonFemale = new QRadioButton();
    radioButtonFemale->setText("Female");

    hLayout4->addWidget(new QLabel("Sex:"));
    hLayout4->addWidget(radioButtonMale);
    hLayout4->addWidget(radioButtonFemale);
    gridLayout->addLayout(hLayout4);

    QHBoxLayout* hLayout5 = new QHBoxLayout();
    comboboxEducation = new QComboBox();
    comboboxEducation->addItem("Elementary");
    comboboxEducation->addItem("High school");
    comboboxEducation->addItem("University");
    comboboxEducation->addItem("Postgraduate");
    hLayout5->addWidget(new QLabel("Education:"));
    hLayout5->addWidget(comboboxEducation);
    gridLayout->addLayout(hLayout5);

    QHBoxLayout* hLayout6 = new QHBoxLayout();
    dateEditBirth = new QDateEdit();
    dateEditBirth->setDate(QDate::currentDate());
    dateEditBirth->setDisplayFormat("dd.MM.yyyy");
    hLayout6->addWidget(new QLabel("Day of birth:"));
    hLayout6->addWidget(dateEditBirth);
    gridLayout->addLayout(hLayout6);

    checkBoxAgree = new QCheckBox();
    checkBoxAgree->setText("I agree with terms of service");
    gridLayout->addWidget(checkBoxAgree);

    QHBoxLayout* hLayout8 = new QHBoxLayout();
    buttonValidate = new QPushButton();
    buttonValidate->setText("&Validate");
    buttonClear = new QPushButton();
    buttonClear->setText("&Clear");
    buttonQuit = new QPushButton();
    buttonQuit->setText("&Quit");
    hLayout8->addWidget(buttonValidate);
    hLayout8->addWidget(buttonClear);
    hLayout8->addWidget(buttonQuit);
    gridLayout->addLayout(hLayout8);


    setLayout(gridLayout);

    connect(buttonValidate, &QPushButton::clicked, this, &regWindow::onButtonValidate);
    connect(buttonClear, &QPushButton::clicked, this, &regWindow::onButtonClear);
    connect(buttonQuit, &QPushButton::clicked, this, &regWindow::onButtonQuit);
}

regWindow::~regWindow()
{
    delete lineEditName;
    delete lineEditSurname;
    delete lineEditEmail;
    delete radioButtonMale;
    delete radioButtonFemale;
    delete comboboxEducation;
    delete dateEditBirth;
    delete checkBoxAgree;
    delete buttonValidate;
    delete buttonClear;
    delete buttonQuit;
}


void regWindow::onButtonValidate()
{

    bool allFilled;
    bool emailValid;
    bool dateValid;
    bool adult;
    bool termsAgreed;

    allFilled = !lineEditName->text().isEmpty() && !lineEditSurname->text().isEmpty() && !lineEditEmail->text().isEmpty() &&
        (radioButtonMale->isChecked() || radioButtonFemale->isChecked()) && !dateEditBirth->text().isEmpty() &&
        checkBoxAgree->isChecked();
    emailValid = QRegularExpression("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$").match(lineEditEmail->text()).hasMatch() &&
        lineEditEmail->text().contains("@") && lineEditEmail->text().contains(".");
    dateValid = QDate::fromString(dateEditBirth->text(), "dd.MM.yyyy").isValid();
    QDate birthDate = QDate::fromString(dateEditBirth->text(), "dd.MM.yyyy");
    adult = birthDate.daysTo(QDate::currentDate()) >= 18.0*365.25;
    termsAgreed = checkBoxAgree->isChecked();
    
    bool allValid = allFilled && emailValid && dateValid && adult && termsAgreed;

    QString message = QString("Vše vyplněno: %1\n"
                   "Email validní: %2\n"
                   "Datum validní: %3\n"
                   "Dospělý: %4\n"
                   "Souhlasí: %5\n"
                   "Email vyplněn: %6")
            .arg(allFilled ? "Ano" : "Ne")
            .arg(emailValid ? "Ano" : "Ne")
            .arg(dateValid ? "Ano" : "Ne")
            .arg(adult ? "Ano" : "Ne")
            .arg(termsAgreed ? "Ano" : "Ne")
            .arg(!lineEditEmail->text().isEmpty() ? "Ano" : "Ne");

    if(allValid){
        QMessageBox::information(this, allValid ? "Registration successful." : "Registration failed." , message);
    } else {
        QMessageBox::warning(this, allValid ? "Registration successful." : "Registration failed." , message);
    }
    
}

void regWindow::onButtonClear()
{
    // Clear all fields and input elements
    lineEditName->clear();
    lineEditSurname->clear();
    lineEditEmail->setText("@");
    radioButtonMale->setChecked(false);
    radioButtonFemale->setChecked(false);
    comboboxEducation->setCurrentIndex(0);
    dateEditBirth->setDate(QDate::currentDate());
    checkBoxAgree->setChecked(false);
}

void regWindow::onButtonQuit()
{
    this->close();
}