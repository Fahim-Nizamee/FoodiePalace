#include "mainwindow.h"
#include "ui_mainwindow.h"

QVector<User> usersInfoArray;
class User userObject;
int currentSelectedFoodIndex;
QVector<Food> foodInfoArray;
class Food foodObject;
long long userTotalBill;
int logedInUserIndex;
QMap<QString,QPair<int,int>>cartStorage; // first one is food index, second of pair is amount or food
int orderCountOfCart = 0;

void showMap()
{
    QMap<QString,QPair<int,int>>::iterator it;

//    cartStorage["beef"] = {1,2};
//     cartStorage["chicken"] = {12,82};
//      cartStorage["lasagna"] = {16,72};
    for(it = cartStorage.begin();it != cartStorage.end();it++){
        QString food = it.key();
    qDebug() << food;
    qDebug() << it->first;
    qDebug() << it->second;
    }
 }

void readUserFile()
{
    QString userName;
    QString mobileNumber;
    int userAge;
    QString userGender;
    QString password;
    // QVector<history> userHistory;
    QString temp1;
    int historySize;
    history tempHistory;

    QFile file("users.txt");

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Not Ok 2";
        return;
    }
    QTextStream in(&file);
    usersInfoArray.clear();
    // base=0;
    while (!in.atEnd())
    {
        userName = in.readLine();
        temp1 = in.readLine();
        userGender = in.readLine();
        mobileNumber = in.readLine();
        password = in.readLine();
        userAge = temp1.split(" ")[0].toInt();
        temp1 = in.readLine();
        historySize = temp1.split(" ")[0].toInt();
        for (int i = 0; i < historySize; i++)
        {
            tempHistory.foodname = in.readLine();
            tempHistory.amount = in.readLine();
            tempHistory.bill = in.readLine();
            tempHistory.date = in.readLine();
            userObject.userHistory.push_back(tempHistory);
        }
        userObject.setAllUserInfo(userName, userAge, userGender, mobileNumber, password);
        usersInfoArray.push_back(userObject);
        userObject.userHistory.clear();
    }
}
void saveUserFile()
{
    qDebug() << "file writing";
    QFile file("users.txt");
    QFile file2("history.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Not ok";
        return;
    }
    if (!file2.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Not ok2";
        return;
    }

    QTextStream out(&file);
    QTextStream out2(&file2);
    for (int i = 0; i < usersInfoArray.size(); i++)
    {
        QString temp1;
        out << usersInfoArray[i].getUserName() << "\n";
        temp1 = QString::number(usersInfoArray[i].getUserAge());
        out << temp1 << "\n";
        out << usersInfoArray[i].getUserGender() << "\n";
        out << usersInfoArray[i].getMobileNumber() << "\n";
        out << usersInfoArray[i].getPassword() << "\n";
        out << usersInfoArray[i].userHistory.size() << "\n";
        for (int j = 0; j < usersInfoArray[i].userHistory.size(); j++)
        {
            out << usersInfoArray[i].userHistory[j].foodname << "\n";
            out << usersInfoArray[i].userHistory[j].amount << "\n";
            out << usersInfoArray[i].userHistory[j].bill << "\n";
            out << usersInfoArray[i].userHistory[j].date << "\n";

            // writing in orderHistory file which will be read in Owner version program
            // this should be the common file between two version of programs
            out2 << usersInfoArray[i].userHistory[j].foodname << "\n";
            out2 << usersInfoArray[i].userHistory[j].amount << "\n";
            out2 << usersInfoArray[i].userHistory[j].bill << "\n";
        }
    }
}
void readFoodFile()
{
    QString foodName;
    int foodPrice;
    int foodStock;
    QString temp2;
    QString temp3;
    QFile file("foodv6.txt");
    foodInfoArray.clear();

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Not Ok 2";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        foodName = in.readLine();
        temp2 = in.readLine();
        foodPrice = temp2.split(" ")[0].toInt();
        temp3 = in.readLine();
        foodStock = temp3.split(" ")[0].toInt();
        foodObject.setAllFoodInfo(foodName, foodPrice, foodStock);
        foodInfoArray.push_back(foodObject);
    }
}

void saveFoodFile()
{
    QString temp2;
    QString temp3;

    QFile file("foodv6.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Not ok";
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < foodInfoArray.size(); i++)
    {
        out << foodInfoArray[i].getFoodName() << "\n";
        temp2 = QString::number(foodInfoArray[i].getFoodPrice());
        out << temp2 << "\n";
        temp3 = QString::number(foodInfoArray[i].getFoodStock());
        out << temp3 << "\n";
    }
}

void showFile()
{
    showMap();
    for (int i = 0; i < usersInfoArray.size(); i++)
    {
        qDebug() << usersInfoArray[i].getUserName();
        qDebug() << usersInfoArray[i].getMobileNumber();
        qDebug() << usersInfoArray[i].getPassword();
        qDebug() << usersInfoArray[i].getUserAge();
        qDebug() << usersInfoArray[i].getUserGender();
        qDebug() << usersInfoArray[i].userHistory.size();
        for (int j = 0; j < usersInfoArray[i].userHistory.size(); j++)
        {
            qDebug() << usersInfoArray[i].userHistory[j].foodname;
            qDebug() << usersInfoArray[i].userHistory[j].amount;
            qDebug() << usersInfoArray[i].userHistory[j].bill;
            qDebug() << usersInfoArray[i].userHistory[j].date;
        }
    }
    QDateTime date = QDateTime::currentDateTime();
    QString getCurrentDate = date.toString("dd/MM/yyyy");
    qDebug() << getCurrentDate;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    readUserFile();
    readFoodFile();
    showFile();
    // saveUserFile();
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->graphics1->hide();
    ui->graphics2->hide();
    ui->graphics3->hide();
    ui->orderCountLabel->setText("0");
    ui->orderCountLabel_2->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// when login button is pressed it will go to login page
void MainWindow::on_logInButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    readUserFile();
}

// when login back button is pressed it will go to welcome page
void MainWindow::on_loginPageBackButton_clicked()
{
    ui->loginPageUsername->clear();
    ui->loginPagePassword->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

// when register back button is pressed
void MainWindow::on_registerPageBackButton_clicked()
{
    ui->registerPageAgeBox->setValue(0);
    ui->registerPagePassword->clear();
    ui->registerPageMobile->clear();
    ui->registerPageUsername->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

// going to register page by clicking registerButton
void MainWindow::on_RegisterButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//Go to cart
void MainWindow::on_cartButton_clicked()
{

    ui->cartGraphics->show();
    ui->cartFoodList->clear();
    ui->userBlinder1->show();
    ui->userBlinder2->show();
    ui->userBlinder3->show();

    QIcon food = QIcon(":/img/resource/hot-pot.png");
    ui->foodListFoodMenu->setIconSize(QSize(30, 30));
    QMap<QString,QPair<int,int>>::iterator it;
    qDebug() << cartStorage.size();
    for(it = cartStorage.begin();it != cartStorage.end();it++)
    {
        ui->userBlinder1->hide();
        ui->userBlinder2->hide();
        ui->userBlinder3->hide();
        QString cartSingleFood = it.key();
        QListWidgetItem *newItem = new QListWidgetItem;
        QFont f;

        f.setPointSize(14);
        newItem->setText(cartSingleFood);
        newItem->setIcon(QIcon(food));
        newItem->setFont(f);
        ui->cartFoodList->addItem(newItem);

    }
    ui->cartFoodName->setText("");
    ui->cartFoodPrice->setText("");
    ui->cartTotalPrice->setText("");
    ui->cartFoodAmount->setValue(0);
    //total bill summation
    int totalBillCart =0;
    for(it = cartStorage.begin();it != cartStorage.end();it++)
    {
      totalBillCart+= (foodInfoArray[it->first].getFoodPrice()*it->second);
    }
    ui->cartTotalBill->setText(QString::number(totalBillCart));

    ui->stackedWidget->setCurrentIndex(5);
}
//food menu
void MainWindow::on_menuButton_clicked()
{
    readFoodFile();
    ui->foodListFoodMenu->clear();
    QIcon food = QIcon(":/img/resource/hot-pot.png");
    ui->foodListFoodMenu->setIconSize(QSize(30, 30));
    for (int i = 0; i < foodInfoArray.size(); i++)
    {
        QListWidgetItem *newItem = new QListWidgetItem;
        QFont f;

        f.setPointSize(14);
        newItem->setText(foodInfoArray[i].getFoodName());
        newItem->setIcon(QIcon(food));
        newItem->setFont(f);
        ui->foodListFoodMenu->addItem(newItem);
        // ui->foodListFoodMenu->addItem(foodInfoArray[i].getFoodName());
    }
    ui->stackedWidget->setCurrentIndex(4);
}

int foodMenuCart=0;
//foodmenu to cart
void MainWindow::on_cartViewIconButton_clicked()
{
    ui->cartGraphics->show();
    ui->cartFoodList->clear();

        ui->userBlinder1->show();
        ui->userBlinder2->show();
        ui->userBlinder3->show();
    QIcon food = QIcon(":/img/resource/hot-pot.png");
    ui->foodListFoodMenu->setIconSize(QSize(30, 30));
    QMap<QString,QPair<int,int>>::iterator it;
    qDebug() << cartStorage.size();
    for(it = cartStorage.begin();it != cartStorage.end();it++)
    {
        ui->userBlinder1->hide();
        ui->userBlinder2->hide();
        ui->userBlinder3->hide();
        QString cartSingleFood = it.key();
        QListWidgetItem *newItem = new QListWidgetItem;
        QFont f;

        f.setPointSize(14);
        newItem->setText(cartSingleFood);
        newItem->setIcon(QIcon(food));
        newItem->setFont(f);
        ui->cartFoodList->addItem(newItem);

    }
    ui->cartFoodName->setText("");
    ui->cartFoodPrice->setText("");
    ui->cartTotalPrice->setText("");
    ui->cartFoodAmount->setValue(0);
    //total bill summation
    int totalBillCart =0;
    for(it = cartStorage.begin();it != cartStorage.end();it++)
    {
      totalBillCart+= (foodInfoArray[it->first].getFoodPrice()*it->second);
    }
    ui->cartTotalBill->setText(QString::number(totalBillCart));
    foodMenuCart=1;

    ui->stackedWidget->setCurrentIndex(5);
}

//cart to back
void MainWindow::on_cartPageBackButton_clicked()
{
    if(foodMenuCart==1)
    {
        ui->stackedWidget->setCurrentIndex(4);
        foodMenuCart=0;
    }
    else if(foodMenuCart==2)
    {
        ui->foodNameLable->setText(foodInfoArray[currentSelectedFoodIndex].getFoodName());
        QString foodPrice = QString::number(foodInfoArray[currentSelectedFoodIndex].getFoodPrice());
        ui->foodPriceLable->setText(foodPrice);
        QString foodStock = QString::number(foodInfoArray[currentSelectedFoodIndex].getFoodStock());
        ui->foodStockLable->setText(foodStock);
        ui->stackedWidget->setCurrentIndex(8);
        foodMenuCart=0;
    }
    else
    {
    ui->stackedWidget->setCurrentIndex(3);
    }
}

// back button of about us page
void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3); // back button in about us page
}

void MainWindow::on_aboutUsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

// Exit form history page
void MainWindow::on_historyPageBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
}

// Go to history Page;
void MainWindow::on_historyButton_clicked()
{
    ui->graphics1->hide();
    ui->graphics2->hide();
    ui->graphics3->hide();
    readUserFile();
    QStringList coloumnName;
    ui->tableWidget->setColumnCount(7);
    coloumnName << "Items"
                << ""
                << "Amount"
                << ""
                << "Bill"
                << ""
                << "Date";
    ui->tableWidget->setHorizontalHeaderLabels(coloumnName);
    int totalhistorybill = 0;
    for (int i = 0; i < usersInfoArray[logedInUserIndex].userHistory.size(); i++)
    {
        QString fName = usersInfoArray[logedInUserIndex].userHistory[i].foodname;
        int fAmount = usersInfoArray[logedInUserIndex].userHistory[i].amount.split(" ")[0].toInt();
        int fPrice = usersInfoArray[logedInUserIndex].userHistory[i].bill.split(" ")[0].toInt() ;
        QString fDate = usersInfoArray[logedInUserIndex].userHistory[i].date;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowCounter = ui->tableWidget->rowCount() - 1;
        ui->tableWidget->setItem(rowCounter, 0, new QTableWidgetItem(fName));
        ui->tableWidget->setItem(rowCounter, 2, new QTableWidgetItem(QString::number(fAmount)));
        ui->tableWidget->setItem(rowCounter, 4, new QTableWidgetItem(QString::number(fPrice)));
        ui->tableWidget->setItem(rowCounter, 6, new QTableWidgetItem(fDate));
        totalhistorybill += fPrice;
    }
    ui->totalSpendamounts->setText(QString::number(totalhistorybill));
    if(usersInfoArray[logedInUserIndex].userHistory.size()==0)
    {
        ui->graphics1->show();
        ui->graphics2->show();
        ui->graphics3->show();
    }
    ui->stackedWidget->setCurrentIndex(7);
}

// login to dashboard
void MainWindow::on_loginPageLoginButton_clicked()
{
    readUserFile();
    int f = 0;
    QString text1 = ui->loginPageUsername->text();
    text1 = text1.trimmed();
    for (int i = 0; i < usersInfoArray.size(); i++)
    {

        if (usersInfoArray[i].getUserName() == text1 && usersInfoArray[i].getPassword() == ui->loginPagePassword->text())
        {
            logedInUserIndex = i;
            f = 1;

            ui->userNameLable->setText(usersInfoArray[i].getUserName());
            QMessageBox::information(this, tr("Foodie Palace"), tr("Login successful."), QMessageBox::Ok);
            if (usersInfoArray[i].getUserGender() == "Male")
            {
                ui->editProfileButton->setStyleSheet("border-image:url(:/img/resource/manEd.png);");
            }
            else
            {
                ui->editProfileButton->setStyleSheet("border-image:url(:/img/resource/womanED.png);");
            }
            ui->loginPageUsername->clear();
            ui->loginPagePassword->clear();
            ui->stackedWidget->setCurrentIndex(3);
        }
    }
    if (f != 1)
    {
        ui->loginPageUsername->clear();
        ui->loginPagePassword->clear();
        QMessageBox::critical(this, tr("Foodie Palace"), tr("Wrong Username or Password\t\n Try again?"), QMessageBox::Ok);
    }
    showFile();
}

//new register
void MainWindow::on_regiterPageRegisterButton_clicked()
{
    readUserFile();
    QString userName = ui->registerPageUsername->text();
    userName = userName.trimmed();
    int userAge;
    QString userGender;
    QString mobileNumber;
    QString password;
    for (int i = 0; i < usersInfoArray.size(); i++)
    {
        if (userName == usersInfoArray[i].getUserName())
        {
            ui->registerPageUsername->clear();
            ui->registerPageMobile->clear();
            ui->registerPagePassword->clear();
            QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nUse unique name\nFillup all information"), QMessageBox::Ok);
            userName = "";
            break;
        }
    }

    mobileNumber = ui->registerPageMobile->text();
    password = ui->registerPagePassword->text();
    QString temp1 = ui->registerPageAgeBox->text();
    userAge = temp1.split(" ")[0].toInt();
    userGender = ui->registerPageGenderSelect->currentText();
    mobileNumber = mobileNumber.trimmed();
    bool verifyNum = true;
    for (int i = 0; i < mobileNumber.size(); i++)
    {
        if (mobileNumber[i] >= '0' && mobileNumber[i] <= '9')
            continue;
        else
        {
            verifyNum = false;
            break;
        }
    }
    password = password.trimmed();

    if (userName != "" && mobileNumber != "" && password != "" && userAge > 0 && userGender != "" && verifyNum)
    {
        userObject.userHistory.clear();
        userObject.setAllUserInfo(userName, userAge, userGender, mobileNumber, password);
        usersInfoArray.push_back(userObject);
        QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully registered\nNow Login for continue"), QMessageBox::Ok);
        ui->stackedWidget->setCurrentIndex(1);
        ui->registerPageUsername->clear();
        ui->registerPagePassword->clear();
        ui->registerPageMobile->clear();
        saveUserFile();
    }
    else
    {
        QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nUse unique name\nFillup all information"), QMessageBox::Ok);
        //    ui->regUsername->clear();
        //    ui->regPassword->clear();
        //    ui->regUserAge->clear();
        //    ui->regMobilenumber->clear();
    }
}

// logout
void MainWindow::on_logoutButton_clicked()
{
    logedInUserIndex = -1;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Foodie Palace"), tr("Logout?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->userNameLable->clear();
    }
}


// foodMenu page to Dashboard
void MainWindow::on_pushButton_clicked()
{
    ui->foodListFoodMenu->clear();
    ui->stackedWidget->setCurrentIndex(3);
}

//food list to details
void MainWindow::on_foodListFoodMenu_clicked(const QModelIndex &index)
{
    for (int i = 0; i < foodInfoArray.size(); i++)
    {
        if (foodInfoArray[i].getFoodName() == ui->foodListFoodMenu->currentItem()->text())
        {
            currentSelectedFoodIndex=i;
            //        flagName = foodInfoArray[i].getFoodName();
            ui->foodNameLable->setText(foodInfoArray[i].getFoodName());
            QString foodPrice = QString::number(foodInfoArray[i].getFoodPrice());
            ui->foodPriceLable->setText(foodPrice);
            QString foodStock = QString::number(foodInfoArray[i].getFoodStock());
            ui->foodStockLable->setText(foodStock);
            //        ui->foodNameEdit->setText(foodInfoArray[i].getFoodName());
            //        ui->foodPriceEdit->setText(foodPrice);
            //        ui->foodStockEdit->setText(foodStock);
            ui->stackedWidget->setCurrentIndex(8);
            break;
        }
    }
}

// ---------------------------------------------------------->food details to food menu
void MainWindow::on_loginPageBackButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->foodAmountSpinBox->setValue(0);
}

// Clear history
void MainWindow::on_clearAllHistoryButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Foodie Palace"), tr("Clear all history?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
    usersInfoArray[logedInUserIndex].userHistory.clear();
    saveUserFile();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    QStringList coloumnName;
    ui->tableWidget->setColumnCount(7);
    coloumnName << "Items"
                << ""
                << "Amount"
                << ""
                << "Price"
                << ""
                << "Date";
    ui->tableWidget->setHorizontalHeaderLabels(coloumnName);
    ui->graphics1->show();
    ui->graphics2->show();
    ui->graphics3->show();
    QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully cleared."), QMessageBox::Ok);

    }
}

//user profile
void MainWindow::on_editProfileButton_clicked()
{
    if(usersInfoArray[logedInUserIndex].getUserGender()=="Male")
    {
        ui->userGenderShowLable->setStyleSheet("border-image:url(:recource/CrownMan.png);");
    }
    else
        ui->userGenderShowLable->setStyleSheet("border-image:url(:recource/CrownMan.png);");

    ui->usernameLable->setText( usersInfoArray[logedInUserIndex].getUserName());
    ui->userAgeLable->setText(QString::number(usersInfoArray[logedInUserIndex].getUserAge()));
    ui->userMobileNumberLable->setText(usersInfoArray[logedInUserIndex].getMobileNumber());
    ui->stackedWidget->setCurrentIndex(9);

}

//user profile to dashboard
void MainWindow::on_profileBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

//edit userName
void MainWindow::on_usernameEditButton_clicked()
{
    int userNameFlag=0;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                         tr("Enter new username: "), QLineEdit::Normal,
                                         "", &ok);
    text = text.trimmed();
    if (ok && text != "")
    {
        for(int i=0;i<usersInfoArray.size();i++)
        {
            if(usersInfoArray[i].getUserName()==text)
            {
                userNameFlag=1;
                break;
            }
        }
        if(userNameFlag==1)
        {
            QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nYou can't use this name.\nUse unique name."), QMessageBox::Ok);
        }
        else
        {
            ui->usernameLable->setText(text);
            QMessageBox::information(this, tr("Foodie Palace"), tr("New username successfully entered.\nClick on Update button for save this information."), QMessageBox::Ok);
        }
    }
    else if (ok && text == "")
    {
      QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nYou have to enter an username."), QMessageBox::Ok);
    }
}


//edit user age
void MainWindow::on_userAgeEditButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                         tr("Enter your age: "), QLineEdit::Normal,
                                         "", &ok);
    text = text.trimmed();
    bool verifyAge = true;
    for(int i=0;i<text.size();i++)
    {
        if(text[i] >= '0' && text[i] <= '9') continue;
        else {
            verifyAge = false;
            break;
        }
    }
    if (ok && text != "" && verifyAge && text!='0')
    {
      ui->userAgeLable->setText(text);
      QMessageBox::information(this, tr("Foodie Palace"), tr("Age successfully entered.\nClick on Update button for save this information."), QMessageBox::Ok);
    }
    else
    {
      QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nInvalid age."), QMessageBox::Ok);
    }
}


//edit user mobile number
void MainWindow::on_mobileNumberEditButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                         tr("Enter your new mobile number: "), QLineEdit::Normal,
                                         "", &ok);
    text = text.trimmed();
    bool verifyNum = true;
    for(int i=0;i<text.size();i++)
    {
        if(text[i] >= '0' && text[i] <= '9') continue;
        else {
            verifyNum = false;
            break;
        }
    }

    if (ok && text != "" && verifyNum)
    {
      ui->userMobileNumberLable->setText(text);
      QMessageBox::information(this, tr("Foodie Palace"), tr("New mobile number successfully entered.\nClick on Update button for save this information."), QMessageBox::Ok);
    }
    else
    {
      QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nInvalid Mobile number."), QMessageBox::Ok);
    }
}


//edit user password
void MainWindow::on_pushButton_3_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                         tr("Enter your old password:"), QLineEdit::Password,
                                         "", &ok);
    text=text.trimmed();
    if(ok && text == usersInfoArray[logedInUserIndex].getPassword())
    {
        bool okk;
        QString text2 = QInputDialog::getText(this, tr("Foodie Palace"),
                                             tr("Enter your new password:"), QLineEdit::Password,
                                             "", &okk);
        text2=text2.trimmed();
        if(okk && text2 != "")
        {
            usersInfoArray[logedInUserIndex].setPassword(text2);
            QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully updated password."), QMessageBox::Ok);
            saveUserFile();
        }
        else if(okk)
        {
            QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!"), QMessageBox::Ok);
        }
    }
    else if(ok)
    {
        QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!\nWrong password."), QMessageBox::Ok);
    }

}

//update all userInformation
void MainWindow::on_userProfileUpdateButton_clicked()
{
    QString temp1 = ui->userAgeLable->text();
    QString userName = ui->usernameLable->text();
    QString mobileNumber = ui->userMobileNumberLable->text();
    int userAge = temp1.split(" ")[0].toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Foodie Palace"), tr("You wanna update all information?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      bool ok;
      QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                           tr("Password:"), QLineEdit::Password,
                                           "", &ok);
      text = text.trimmed();
      if(usersInfoArray[logedInUserIndex].getPassword()==text)
      {
          usersInfoArray[logedInUserIndex].setUserName(userName);
          usersInfoArray[logedInUserIndex].setMobileNumber(mobileNumber);
          usersInfoArray[logedInUserIndex].setUserAge(userAge);
          QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully updated."), QMessageBox::Ok);
          saveUserFile();
          ui->userNameLable->setText(userName);
      }
      else
      {
        QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!\nWrong password."), QMessageBox::Ok);
      }
    }
}

//add to cart
void MainWindow::on_addToCartButton_clicked()
{

    int orderAmount= ui->foodAmountSpinBox->text().split(" ")[0].toInt();
    if(foodInfoArray[currentSelectedFoodIndex].getFoodStock()>=orderAmount && orderAmount != 0)
    {
        qDebug() << foodInfoArray[currentSelectedFoodIndex].getFoodName();
        //cartStorage.push_back({currentSelectedFoodIndex,orderAmount});
        cartStorage[foodInfoArray[currentSelectedFoodIndex].getFoodName()].first = currentSelectedFoodIndex;
        cartStorage[foodInfoArray[currentSelectedFoodIndex].getFoodName()].second += orderAmount;
        orderCountOfCart++;
        int tempStock = foodInfoArray[currentSelectedFoodIndex].getFoodStock();
        tempStock -= orderAmount;
        foodInfoArray[currentSelectedFoodIndex].setFoodStock(tempStock);
        ui->foodStockLable->setText(QString::number(tempStock));
        ui->orderCountLabel->setText(QString::number(cartStorage.size()));
        ui->orderCountLabel_2->setText(QString::number(cartStorage.size()));
        ui->foodAmountSpinBox->setValue(0);
    }
    else if (orderAmount==0) {}
    else
    {
        QMessageBox::warning(this, tr("Foodie Palace"), tr("Not enough food available."), QMessageBox::Ok);
    }
}

//Food details to cart
void MainWindow::on_cartViewIconButton_2_clicked()
{
    ui->cartFoodList->clear();
    ui->cartGraphics->show();
        ui->userBlinder1->show();
        ui->userBlinder2->show();
        ui->userBlinder3->show();
    QIcon food = QIcon(":/img/resource/hot-pot.png");
    ui->foodListFoodMenu->setIconSize(QSize(30, 30));
    QMap<QString,QPair<int,int>>::iterator it;
    qDebug() << cartStorage.size();
    for(it = cartStorage.begin();it != cartStorage.end();it++)
    {
        ui->userBlinder1->hide();
        ui->userBlinder2->hide();
        ui->userBlinder3->hide();
        QString cartSingleFood = it.key();
        QListWidgetItem *newItem = new QListWidgetItem;
        QFont f;

        f.setPointSize(14);
        newItem->setText(cartSingleFood);
        newItem->setIcon(QIcon(food));
        newItem->setFont(f);
        ui->cartFoodList->addItem(newItem);

    }
    ui->cartFoodName->setText("");
    ui->cartFoodPrice->setText("");
    ui->cartTotalPrice->setText("");
    ui->cartFoodAmount->setValue(0);
    //total bill summation
    int totalBillCart =0;
    for(it = cartStorage.begin();it != cartStorage.end();it++)
    {
      totalBillCart+= (foodInfoArray[it->first].getFoodPrice()*it->second);
    }
    ui->cartTotalBill->setText(QString::number(totalBillCart));
    foodMenuCart=2;
    ui->stackedWidget->setCurrentIndex(5);
}

//select cart food
void MainWindow::on_cartFoodList_clicked(const QModelIndex &index)
{

    //QMap<QString,QPair<int,int>>::iterator it;
    for(int i=0;i<foodInfoArray.size();i++)
    {
        if(ui->cartFoodList->currentItem()->text()==foodInfoArray[i].getFoodName())
        {
            ui->cartGraphics->hide();
            ui->cartFoodName->setText(foodInfoArray[i].getFoodName());
            ui->cartFoodPrice->setText(QString::number(foodInfoArray[i].getFoodPrice()));
            ui->cartTotalPrice->setText(QString::number(foodInfoArray[i].getFoodPrice()*cartStorage[foodInfoArray[i].getFoodName()].second));
            ui->cartFoodAmount->setValue(cartStorage[foodInfoArray[i].getFoodName()].second);
            break;
        }
    }
}

//cart update
void MainWindow::on_cartUpdateButton_clicked()
{
    QString foodNameLableText=ui->cartFoodName->text();
    foodNameLableText=foodNameLableText.trimmed();
    qDebug() << foodNameLableText;

    int foodSpinBoxAmount=ui->cartFoodAmount->text().split(" ")[0].toInt();
    int tempStock = foodInfoArray[cartStorage[foodNameLableText].first].getFoodStock();
    qDebug() << tempStock;
    if(foodSpinBoxAmount>(tempStock + cartStorage[foodNameLableText].second))
    {
        QMessageBox::warning(this, tr("Foodie Palace"), tr("Not enough food available."), QMessageBox::Ok);
    }
    else if(foodSpinBoxAmount ==0)
    {
       ui->cartGraphics->show();
       tempStock +=  cartStorage[foodNameLableText].second;
       foodInfoArray[cartStorage[foodNameLableText].first].setFoodStock(tempStock);
       cartStorage.remove(foodNameLableText);

      qDebug() << cartStorage.size();
      ui->cartFoodList->clear();
          ui->userBlinder1->show();
          ui->userBlinder2->show();
          ui->userBlinder3->show();
      QIcon food = QIcon(":/img/resource/hot-pot.png");
      ui->foodListFoodMenu->setIconSize(QSize(30, 30));
      QMap<QString,QPair<int,int>>::iterator it;
      qDebug() << cartStorage.size();
      for(it = cartStorage.begin();it != cartStorage.end();it++)
      {
          ui->userBlinder1->hide();
          ui->userBlinder2->hide();
          ui->userBlinder3->hide();
          QString cartSingleFood = it.key();
          QListWidgetItem *newItem = new QListWidgetItem;
          QFont f;

          f.setPointSize(14);
          newItem->setText(cartSingleFood);
          newItem->setIcon(QIcon(food));
          newItem->setFont(f);
          ui->cartFoodList->addItem(newItem);

      }
      ui->cartFoodName->setText("");
      ui->cartFoodPrice->setText("");
      ui->cartTotalPrice->setText("");
      ui->cartFoodAmount->setValue(0);
      //total bill summation
      int totalBillCart =0;
      for(it = cartStorage.begin();it != cartStorage.end();it++)
      {
        totalBillCart+= (foodInfoArray[it->first].getFoodPrice()*it->second);
      }
      ui->cartTotalBill->setText(QString::number(totalBillCart));
      orderCountOfCart--;
      ui->orderCountLabel->setText(QString::number(cartStorage.size()));
      ui->orderCountLabel_2->setText(QString::number(cartStorage.size()));


    }

    else if(foodNameLableText != "") {
    if((tempStock+cartStorage[foodNameLableText].second) >= foodSpinBoxAmount)
    {
         tempStock = foodInfoArray[cartStorage[foodNameLableText].first].getFoodStock();
         if((cartStorage[foodNameLableText].second) < foodSpinBoxAmount)
        tempStock -= abs(foodSpinBoxAmount - cartStorage[foodNameLableText].second);
        else
           tempStock +=  abs(cartStorage[foodNameLableText].second - foodSpinBoxAmount);

         qDebug() << tempStock;
                 foodInfoArray[cartStorage[foodNameLableText].first].setFoodStock(tempStock);
        cartStorage[foodNameLableText].second = foodSpinBoxAmount;
        QMap<QString,QPair<int,int>>::iterator it;
        int totalBillCart =0;
        for(it = cartStorage.begin();it != cartStorage.end();it++)
        {
          totalBillCart+= (foodInfoArray[it->first].getFoodPrice()*it->second);
        }
        ui->cartTotalBill->setText(QString::number(totalBillCart));
    }
    }
    else
    {
         QMessageBox::warning(this, tr("Foodie Palace"), tr("You need to select an item"), QMessageBox::Ok);
    }

}

//order confirm
void MainWindow::on_confirmOrderButton_clicked()
{
    saveFoodFile();

        QMap<QString,QPair<int,int>>::iterator it;
        for(it = cartStorage.begin();it != cartStorage.end();it++){
            history temp;
            temp.foodname  = it.key();
            temp.amount = QString::number( it->second);
            temp.bill = QString::number(foodInfoArray[it->first].getFoodPrice()*it->second);
            QDateTime date = QDateTime::currentDateTime();
            QString getCurrentDate = date.toString("dd/MM/yyyy");
            temp.date = getCurrentDate;
            usersInfoArray[logedInUserIndex].userHistory.push_back(temp);
        }
        cartStorage.clear();

        saveUserFile();

//        for(int i=0;i<usersInfoArray[logedInUserIndex].userHistory.size() ; i++)
//        {
//        qDebug() << usersInfoArray[logedInUserIndex].userHistory[i].foodname;


//        }
        QMessageBox::information(this, tr("Foodie Palace"), tr("Your order successfully palced.\nPlease wait."), QMessageBox::Ok);
        ui->userBlinder1->show();
        ui->userBlinder2->show();
        ui->userBlinder3->show();
        ui->orderCountLabel->setText("0");
        ui->orderCountLabel_2->setText("0");

}

