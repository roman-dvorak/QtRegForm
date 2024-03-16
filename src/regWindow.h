#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QWidget> 
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QDateEdit>
#include <QCheckBox>

class regWindow : public QWidget
{
    Q_OBJECT

public:
    explicit regWindow(QWidget *parent = nullptr);
    ~regWindow();

private:


    
    QLineEdit* lineEditName;
    QLineEdit* lineEditSurname;
    QLineEdit* lineEditEmail;
    QRadioButton* radioButtonMale;
    QRadioButton* radioButtonFemale;
    QComboBox* comboboxEducation;
    QDateEdit* dateEditBirth;
    QCheckBox* checkBoxAgree;
    QPushButton* buttonValidate;
    QPushButton* buttonClear;
    QPushButton* buttonQuit;
    
    void onButtonValidate();
    void onButtonClear();
    void onButtonQuit();

};

#endif // REGWINDOW_H