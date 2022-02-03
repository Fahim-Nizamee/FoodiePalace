#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <iostream>
#include <QDialogButtonBox>
#include <QVector>
#include <QDialog>
#include <QInputDialog>
#include <QDir>
#include <QIcon>
#include <QListWidgetItem>
#include <QDockWidget>
#include <QFont>
#include <QSize>
#include <QPicture>
#include <QMap>
#include <QPair>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

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
    void on_logInButton_clicked();

    void on_loginPageBackButton_clicked();

    void on_registerPageBackButton_clicked();

    void on_RegisterButton_clicked();

    void on_cartButton_clicked();

    void on_menuButton_clicked();

    void on_cartViewIconButton_clicked();

    void on_cartPageBackButton_clicked();

    void on_pushButton_2_clicked();

    void on_aboutUsButton_clicked();

    void on_historyPageBackButton_clicked();

    void on_historyButton_clicked();

    void on_loginPageLoginButton_clicked();

    void on_regiterPageRegisterButton_clicked();

    void on_logoutButton_clicked();

    void on_pushButton_clicked();

    void on_foodListFoodMenu_clicked(const QModelIndex &index);

    void on_loginPageBackButton_2_clicked();

    void on_clearAllHistoryButton_clicked();

    void on_editProfileButton_clicked();

    void on_profileBackButton_clicked();

    void on_usernameEditButton_clicked();

    void on_userAgeEditButton_clicked();

    void on_mobileNumberEditButton_clicked();

    void on_pushButton_3_clicked();

    void on_userProfileUpdateButton_clicked();

    void on_addToCartButton_clicked();

    void on_cartViewIconButton_2_clicked();

    void on_cartFoodList_clicked(const QModelIndex &index);

    void on_cartUpdateButton_clicked();

    void on_confirmOrderButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


struct history{
  QString foodname;
  QString amount, bill;
  QString date;
};

class Food
{
private:
    QString foodName;
    int foodPrice;
    int foodStock;
public:
    void setAllFoodInfo(QString foodName,int foodPrice,int foodStock)
    {
        this->foodName=foodName;
        this->foodPrice=foodPrice;
        this->foodStock=foodStock;
    }
    QString getFoodName()
    {
        return foodName;
    }
    int getFoodPrice()
    {
        return foodPrice;
    }
    int getFoodStock()
    {
        return foodStock;
    }
    void setFoodName(QString newFoodName)
    {
        foodName=newFoodName;
    }
    void setFoodPrice(int newfoodPrice)
    {
        foodPrice=newfoodPrice;
    }
    void setFoodStock(int newFoodStock)
    {
        foodStock=newFoodStock;
    }
};

class User
{
  private:
    QString userName;
    int userAge;
    QString userGender;
    QString mobileNumber;
    QString password;
  public:
    QVector<history> userHistory;
    void setAllUserInfo(QString userName,int userAge,QString userGender,QString mobileNumber,QString password)
    {
        this->userName=userName;
        this->userAge=userAge;
        this->userGender=userGender;
        this->mobileNumber=mobileNumber;
        this->password=password;

    }

    QString getUserName()
    {
        return userName;
    }
    QString getMobileNumber()
    {
        return mobileNumber;
    }
    QString getPassword()
    {
        return password;
    }
    int getUserAge()
    {
        return userAge;
    }
    QString getUserGender()
    {
        return userGender;
    }
    void setUserName(QString newName)
    {
        userName=newName;
    }
    void setMobileNumber(QString newMobileNumber)
    {
        mobileNumber=newMobileNumber;
    }
    void setPassword(QString newPassword)
    {
        qDebug()<<"new pass"<<newPassword;
        password=newPassword;
    }
    void setUserAge(int age)
    {
        userAge=age;
    }

};










