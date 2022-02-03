#ifndef FOODIEPALACE_H
#define FOODIEPALACE_H

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
namespace Ui { class FoodiePalace; }
QT_END_NAMESPACE

class FoodiePalace : public QMainWindow
{
    Q_OBJECT

public:
    FoodiePalace(QWidget *parent = nullptr);
    ~FoodiePalace();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_regButton_clicked();

    void on_regBackButton_clicked();

    void on_pushButton_3_clicked();

    void on_logoutButtonOwner_clicked();

    void on_foodMenuOwnerButton_clicked();

    void on_foodMenuPartnerButton_clicked();

    void on_foodMenuBackButton_clicked();

    void on_logoutButtonPartner_clicked();

    void on_regNextButton_clicked();

    void on_foodListFoodMenu_clicked(const QModelIndex &index);

    void on_detailsBackButton_clicked();

    void on_updateButton_clicked();

    void on_adminListButton_clicked();

    void on_userListBackButton_clicked();

    void on_UserListWidget_clicked(const QModelIndex &index);

    void on_userDetailsBackButton_clicked();

    void on_foodAddButton_clicked();

    void on_addNewFoodBackButton_clicked();

    void on_addNewFoodToMenuButton_clicked();

    void on_detailsBackButton_2_clicked();

    void on_removeUserButton_clicked();

    void on_transferOwnershipButton_clicked();

    void on_userInformationEditOwnerPushButton_clicked();

    void on_usernameEditButton_clicked();

    void on_userAgeEditButton_clicked();

    void on_mobileNumberEditButton_clicked();

    void on_userProfileUpdateButton_clicked();

    void on_profileBackButton_clicked();

    void on_userInformationEditPartnerButton_clicked();

    void on_pushButton_2_clicked();

    void on_profileBackButton_2_clicked();

    void on_sellingHistoryOwnerButton_clicked();

    void on_sellingHistoryPartnerButton_clicked();

    void on_clearHistory_clicked();

    void on_foodAddButton_2_clicked();

private:
    Ui::FoodiePalace *ui;
};
#endif // FOODIEPALACE_H
class Owner
{
private:
    int userIndex;
    QString userName;
    int userAge;
    QString userGender;
    QString mobileNumber;
    QString password;
    QString isOwner;
public:
    void setAllOwnerInfo(int userIndex,QString userName,int userAge,QString userGender,QString mobileNumber,QString password,QString isOwner )
    {
        this->userIndex=userIndex;
        this->userName=userName;
        this->userAge=userAge;
        this->userGender=userGender;
        this->mobileNumber=mobileNumber;
        this->password=password;
        this->isOwner=isOwner;
    }
    int getUserIndex()
    {
        return userIndex;
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
    QString getIsOwner()
    {
        return isOwner;
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
    void setIsOwner(QString newIsOwner)
    {
        isOwner=newIsOwner;
    }
    void setUserAge(int age)
    {
        userAge=age;
    }

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

