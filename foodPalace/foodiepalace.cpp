#include "foodiepalace.h"
#include "ui_foodiepalace.h"
QVector<Owner> ownerInfoArray;
class Owner ownerObject;

QVector<Food> foodInfoArray;
class Food foodObject;
int base = 0;
int ownerFlag = 0;
long long int totalBill=0;
QMap<QString , QPair<int , int>>historyData;
QVector<QString>historyFoodnames;
QMap<QString,int>checkFoodName;
void readHistoryFile()
{
    historyData.clear();
    historyFoodnames.clear();
    checkFoodName.clear();
    QString foodName;
    int foodPrice;
    int foodAmount;
    QFile file("history.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        foodName = in.readLine();
        QString temp1;
        temp1 = in.readLine();
        QString temp2;
        temp2 = in.readLine();
        foodAmount = temp1.split(" ")[0].toInt();
        foodPrice = temp2.split(" ")[0].toInt();
        historyData[foodName].first+=foodAmount;
        historyData[foodName].second+=foodPrice;
        if(checkFoodName[foodName]==0){
        checkFoodName[foodName] = 1;
        historyFoodnames.push_back(foodName);
    }
    }

}

void saveHistoryFile()
{
    historyData.clear();
    historyFoodnames.clear();
    checkFoodName.clear();
    QFile file("history.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
      qDebug() << "Not ok";
      return;
    }
    QString A = "";

    QTextStream out(&file);
    out<<A;
}


void readOwnerFile()
{
  int userIndex;
  QString userName;
  QString mobileNumber;
  int userAge;
  QString userGender;
  QString password;
  QString isOwner;
  QString temp1;

  QFile file("nm.txt");

  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    qDebug() << "Not Ok 2";
    return;
  }
  QTextStream in(&file);
  ownerInfoArray.clear();
  base=0;
  while (!in.atEnd())
  {
    userIndex = base + 1;
    userName = in.readLine();
    temp1 = in.readLine();
    userGender = in.readLine();
    mobileNumber = in.readLine();
    password = in.readLine();
    isOwner = in.readLine();
    userAge = temp1.split(" ")[0].toInt();
    if (isOwner == "Owner")
    {
      ownerFlag = 1;
    }

    ownerObject.setAllOwnerInfo(userIndex, userName, userAge, userGender, mobileNumber, password, isOwner);
    ownerInfoArray.push_back(ownerObject);
    base++;
  }
}
void saveOwnerFile()
{
  QFile file("nm.txt");

  if (!file.open(QFile::WriteOnly | QFile::Text))
  {
    qDebug() << "Not ok";
    return;
  }

  QTextStream out(&file);
  for (int i = 0; i < ownerInfoArray.size(); i++)
  {
    QString temp1;
    temp1 = QString::number(ownerInfoArray[i].getUserAge());
    out << ownerInfoArray[i].getUserName() << "\n";
    out << temp1 << "\n";
    out << ownerInfoArray[i].getUserGender() << "\n";
    out << ownerInfoArray[i].getMobileNumber() << "\n";
    out << ownerInfoArray[i].getPassword() << "\n";
    out << ownerInfoArray[i].getIsOwner() << "\n";
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
        qDebug() << historyFoodnames.size();
        for(int i=0;i<historyFoodnames.size();i++){
        qDebug() <<historyFoodnames[i];
        qDebug() << historyData[historyFoodnames[i]].first;
        qDebug() << historyData[historyFoodnames[i]].second;
    }
}
FoodiePalace::FoodiePalace(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FoodiePalace)
{
  readFoodFile();
  //readHistoryFile();
  //showFile();
  ui->setupUi(this);
  ui->stackedWidget->setCurrentIndex(0);
}

FoodiePalace::~FoodiePalace()
{
  delete ui;
}

// login_button
void FoodiePalace::on_pushButton_clicked()
{

  ui->stackedWidget->setCurrentIndex(1);
  ownerInfoArray.clear();
  readOwnerFile();
}

// from login to Opening page (Back)button
void FoodiePalace::on_pushButton_4_clicked()
{
  ui->loginUserName->clear();
  ui->loginPassword->clear();
  ui->stackedWidget->setCurrentIndex(0);
}

// login to next button

void FoodiePalace::on_pushButton_5_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
}

// opening page to reg page
void FoodiePalace::on_regButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
  ownerInfoArray.clear();
  readOwnerFile();
  if (ownerFlag == 1)
  {
    ui->comboBox->hide();
  }
}

// reg page to opening page
void FoodiePalace::on_regBackButton_clicked()
{
  ui->regUsername->clear();
  ui->regPassword->clear();
  ui->regMobilenumber->clear();
  ui->stackedWidget->setCurrentIndex(0);
}

int fowner = 0;
// login page to Owner deshboard
void FoodiePalace::on_pushButton_3_clicked()
{
int f = 0;
    readOwnerFile();
  for (int i = 0; i < ownerInfoArray.size(); i++)
  {

    if (ui->loginUserName->text() == ownerInfoArray[i].getUserName() && ui->loginPassword->text() == ownerInfoArray[i].getPassword())
    {
      f = 1;

      if (ownerInfoArray[i].getIsOwner() == "Owner")
      {
        fowner = 1;
        QMessageBox::information(this, tr("Foodie Palace"), tr("Login successful."), QMessageBox::Ok);
        if(ownerInfoArray[i].getUserGender()=="Male")
        {
            ui->userInformationEditOwnerPushButton->setStyleSheet("border-image:url(:/new/prefix1/CrownMan.png);");
        }
        else if(ownerInfoArray[i].getUserGender()=="Female")
        {
            ui->userInformationEditOwnerPushButton->setStyleSheet("border-image:url(:/new/prefix1/CrownWoman.png);");
        }
        ui->stackedWidget->setCurrentIndex(3);
        ui->usernameLableOwner->setText(ownerInfoArray[i].getUserName());
      }
      else
      {

        QMessageBox::information(this, tr("Foodie Palace"), tr("Login successful."), QMessageBox::Ok);
        if(ownerInfoArray[i].getUserGender()=="Male")
        {
            ui->userInformationEditPartnerButton->setStyleSheet("border-image:url(:/new/prefix1/manEd.png);");
        }
        else if(ownerInfoArray[i].getUserGender()=="Female")
        {
            ui->userInformationEditPartnerButton->setStyleSheet("border-image:url(:/new/prefix1/womanED.png);");
        }
        ui->stackedWidget->setCurrentIndex(4);
        ui->usernameLablePartner_2->setText(ownerInfoArray[i].getUserName());
      }
      ui->loginUserName->clear();
      ui->loginPassword->clear();
    }
  }
  if (f != 1)
  {
    ui->loginUserName->clear();
    ui->loginPassword->clear();
    QMessageBox::critical(this, tr("Foodie Palace"), tr("Wrong Username or Password\t\n Try again?"), QMessageBox::Ok);
  }
}

// logout from Owner desh board to login page
void FoodiePalace::on_logoutButtonOwner_clicked()
{

  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, tr("Foodie Palace"), tr("Logout?"),
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes)
  {
    ui->stackedWidget->setCurrentIndex(0);
    ui->usernameLableOwner->clear();
    fowner = 0;
    saveFoodFile();
  }
}

// logout from Partner desh board to login page
void FoodiePalace::on_logoutButtonPartner_clicked()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, tr("Foodie Palace"), tr("Logout?"),
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes)
  {
    ui->stackedWidget->setCurrentIndex(0);
    ui->usernameLablePartner_2->clear();
    saveFoodFile();
  }
}

// Owner deshboard (Food menu button to Food menu list)
void FoodiePalace::on_foodMenuOwnerButton_clicked()
{

    QIcon food = QIcon(":/new/prefix1/hot-pot.png");
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
    //ui->foodListFoodMenu->addItem(foodInfoArray[i].getFoodName());
  }
  ui->stackedWidget->setCurrentIndex(5);
}

// Partner deshboard (Food menu button to Food menu list)
void FoodiePalace::on_foodMenuPartnerButton_clicked()
{
    QIcon food = QIcon(":/new/prefix1/hot-pot.png");
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
    //ui->foodListFoodMenu->addItem(foodInfoArray[i].getFoodName());
  }
  ui->stackedWidget->setCurrentIndex(5);
}

// Food menu to desh board
void FoodiePalace::on_foodMenuBackButton_clicked()
{
  if (fowner == 1)
  {
    ui->stackedWidget->setCurrentIndex(3);
    ui->foodListFoodMenu->clear();
  }
  else
  {
    ui->stackedWidget->setCurrentIndex(4);
    ui->foodListFoodMenu->clear();
  }
}

// Register button
void FoodiePalace::on_regNextButton_clicked()
{
    readOwnerFile();
  int userIndex;
  QString userName = ui->regUsername->text();
  userName = userName.trimmed();
  int userAge;
  QString userGender;
  QString mobileNumber;
  QString password;
  QString isOwner;
  if (ownerFlag == 0)
  {
    isOwner = ui->comboBox->currentText();
  }
  else
  {
    isOwner = "Partner";
  }
  for (int i = 0; i < ownerInfoArray.size(); i++)
  {
    if (userName == ownerInfoArray[i].getUserName())
    {
      ui->regUsername->clear();
      ui->regPassword->clear();
      ui->regMobilenumber->clear();
      QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nUse unique name\nFillup all information"), QMessageBox::Ok);
      userName = "";
      break;
    }
  }

  userIndex = base + 1;
  mobileNumber = ui->regMobilenumber->text();
  password = ui->regPassword->text();
  QString temp1 = ui->regUserAge->text();
  userAge = temp1.split(" ")[0].toInt();
  userGender = ui->genderComboBox->currentText();
  mobileNumber = mobileNumber.trimmed();
  bool verifyNum = true;
  for(int i=0;i<mobileNumber.size();i++)
  {
      if(mobileNumber[i] >= '0' && mobileNumber[i] <= '9') continue;
      else {
          verifyNum = false;
          break;
      }
  }
  password = password.trimmed();

  if (userName != "" && mobileNumber != "" && password != "" && userAge > 0 && userGender != "" && verifyNum)
  {
    ownerObject.setAllOwnerInfo(userIndex, userName, userAge, userGender, mobileNumber, password, isOwner);
    ownerInfoArray.push_back(ownerObject);
    QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully registered\nNow Login for continue"), QMessageBox::Ok);
    ui->stackedWidget->setCurrentIndex(1);
    ui->regUsername->clear();
    ui->regPassword->clear();
    ui->regUserAge->clear();
    ui->regMobilenumber->clear();
    saveOwnerFile();
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
QString flagName;

// food item detail view
void FoodiePalace::on_foodListFoodMenu_clicked(const QModelIndex &index)
{
  for (int i = 0; i < foodInfoArray.size(); i++)
  {
    if (foodInfoArray[i].getFoodName() == ui->foodListFoodMenu->currentItem()->text())
    {
      flagName = foodInfoArray[i].getFoodName();
      ui->foodNameLable->setText(foodInfoArray[i].getFoodName());
      QString foodPrice = QString::number(foodInfoArray[i].getFoodPrice());
      ui->foodPriceLable->setText(foodPrice);
      QString foodStock = QString::number(foodInfoArray[i].getFoodStock());
      ui->foodStockLable->setText(foodStock);
      ui->foodNameEdit->setText(foodInfoArray[i].getFoodName());
      ui->foodPriceEdit->setText(foodPrice);
      ui->foodStockEdit->setText(foodStock);
      ui->stackedWidget->setCurrentIndex(6);
      break;
    }
  }
}

// back to food list
void FoodiePalace::on_detailsBackButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(5);
}

// food details update
void FoodiePalace::on_updateButton_clicked()
{
  int errorFlag = 0;
  int nameErrorFlag =0;
  for (int i = 0; i < foodInfoArray.size(); i++)
  {
    if (foodInfoArray[i].getFoodName() == flagName)
    {
      QString temp1 = ui->foodStockEdit->text();
      QString temp2 = ui->foodPriceEdit->text();
      QString foodName = ui->foodNameEdit->text();
      temp1 = temp1.trimmed();
      temp2 = temp2.trimmed();
      foodName = foodName.trimmed();
      for(int k=0;k<foodInfoArray.size();k++)
      {
          if(foodInfoArray[k].getFoodName()==foodName && foodInfoArray[k].getFoodName() != foodInfoArray[i].getFoodName())
          {
              QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nThis name already in"), QMessageBox::Ok);
              nameErrorFlag=1;
              break;
          }
      }
      if (temp1 != "" && temp2 != "" && foodName != "" && nameErrorFlag == 0)
      {
        int foodPrice = temp2.split(" ")[0].toInt();
        int foodStock = temp1.split(" ")[0].toInt();
        qDebug() << foodName << foodPrice << foodStock;
        if (foodPrice > -1 && foodStock > -1)
        {
          foodInfoArray[i].setAllFoodInfo(foodName, foodPrice, foodStock);
          ui->foodNameLable->setText(foodInfoArray[i].getFoodName());
          QString foodPrice1 = QString::number(foodInfoArray[i].getFoodPrice());
          ui->foodPriceLable->setText(foodPrice1);
          QString foodStock1 = QString::number(foodInfoArray[i].getFoodStock());
          ui->foodStockLable->setText(foodStock1);
          ui->foodListFoodMenu->clear();
          QIcon food = QIcon(":/new/prefix1/hot-pot.png");
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
          //ui->foodListFoodMenu->addItem(foodInfoArray[i].getFoodName());
        }

          flagName = foodName;
          saveFoodFile();
          break;
        }
        else
        {
          errorFlag = 1;
          break;
        }
      }
      else
        errorFlag = 1;
    }
  }
  if (errorFlag != 0)
  {
    QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nFillup all information\nFor Food price or stock negative value isn't acceptable"), QMessageBox::Ok);
  }
}
// owner deshboard to admin list page
void FoodiePalace::on_adminListButton_clicked()
{

  ui->UserListWidget->clear();
  ui->UserListWidget->setIconSize(QSize(40, 40));
  QIcon crownWoman = QIcon(":/new/prefix1/CrownWoman.png");
  QIcon crownMan = QIcon(":/new/prefix1/CrownMan.png");
  QIcon Woman = QIcon(":/new/prefix1/womanED.png");
  QIcon Man = QIcon(":/new/prefix1/manEd.png");

  for (int i = 0; i < ownerInfoArray.size(); i++)
  {
    if (ownerInfoArray[i].getIsOwner() == "Owner" && ownerInfoArray[i].getUserGender() == "Male")
    {
      QListWidgetItem *newItem = new QListWidgetItem;
      QFont f;

      f.setPointSize(18);
      newItem->setText(ownerInfoArray[i].getUserName());
      newItem->setIcon(QIcon(crownMan));
      newItem->setFont(f);
      ui->UserListWidget->addItem(newItem);
    }
    else if (ownerInfoArray[i].getIsOwner() == "Owner" && ownerInfoArray[i].getUserGender() == "Female")
    {
      QListWidgetItem *newItem = new QListWidgetItem;
      QFont f;

      f.setPointSize(18);
      newItem->setText(ownerInfoArray[i].getUserName());
      newItem->setIcon(QIcon(crownWoman));
      newItem->setFont(f);
      ui->UserListWidget->addItem(newItem);
    }
    else if (ownerInfoArray[i].getIsOwner() == "Partner" && ownerInfoArray[i].getUserGender() == "Male")
    {
      QListWidgetItem *newItem = new QListWidgetItem;
      QFont f;

      f.setPointSize(18);
      newItem->setText(ownerInfoArray[i].getUserName());
      newItem->setIcon(QIcon(Man));
      newItem->setFont(f);
      ui->UserListWidget->addItem(newItem);
    }
    else if (ownerInfoArray[i].getIsOwner() == "Partner" && ownerInfoArray[i].getUserGender() == "Female")
    {
      QListWidgetItem *newItem = new QListWidgetItem;
      QFont f;

      f.setPointSize(18);
      newItem->setText(ownerInfoArray[i].getUserName());
      newItem->setIcon(QIcon(Woman));
      newItem->setFont(f);
      ui->UserListWidget->addItem(newItem);
    }
  }
  ui->stackedWidget->setCurrentIndex(7);
}

// admin list page to owner deshboard
void FoodiePalace::on_userListBackButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(3);
}

QString flagAdminName;

// Admin list to particular user data;
void FoodiePalace::on_UserListWidget_clicked(const QModelIndex &index)
{

  for (int i = 0; i < ownerInfoArray.size(); i++)
  {
    if (ownerInfoArray[i].getUserName() == ui->UserListWidget->currentItem()->text())
    {
      flagAdminName = ownerInfoArray[i].getUserName();
      ui->userNameLableDetails->setText(flagAdminName);
      QString userAge = QString::number(ownerInfoArray[i].getUserAge());
      ui->userAgeLableDetails->setText(userAge);
      ui->userGenderLableDetails->setText(ownerInfoArray[i].getUserGender());
      ui->userMobileNumberLableDetails->setText(ownerInfoArray[i].getMobileNumber());
      if (ownerInfoArray[i].getIsOwner() == "Owner")
      {
        if (ownerInfoArray[i].getUserGender() == "Male")
        {
          ui->userGenderViewLable->setStyleSheet("border-image:url(:/new/prefix1/CrownMan.png);");
          ui->userPositonDetails->setText("Owner");
        }
        else if (ownerInfoArray[i].getUserGender() == "Female")
        {
          ui->userGenderViewLable->setStyleSheet("border-image:url(:/new/prefix1/CrownWoman.png);");
          ui->userPositonDetails->setText("Owner");
        }
      }
      else
      {
        if (ownerInfoArray[i].getUserGender() == "Male")
        {
          ui->userGenderViewLable->setStyleSheet("border-image:url(:/new/prefix1/manEd.png);");
          ui->userPositonDetails->setText("Employee");
        }
        else if (ownerInfoArray[i].getUserGender() == "Female")
        {
          ui->userGenderViewLable->setStyleSheet("border-image:url(:/new/prefix1/womanED.png);");
          ui->userPositonDetails->setText("Employee");
        }
      }
      ui->stackedWidget->setCurrentIndex(8);
      break;
    }
  }
}

// user details to user list
void FoodiePalace::on_userDetailsBackButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(7);
}

// Food menu to add new food page
void FoodiePalace::on_foodAddButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(9);
  ui->foodListFoodMenu->clear();
  // readFoodFile();
}

// add new food page to food menu page
void FoodiePalace::on_addNewFoodBackButton_clicked()
{
  ui->stackedWidget->setCurrentIndex(5);
  QIcon food = QIcon(":/new/prefix1/hot-pot.png");
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
  //ui->foodListFoodMenu->addItem(foodInfoArray[i].getFoodName());
}
}

// Add new food to menu

void FoodiePalace::on_addNewFoodToMenuButton_clicked()
{
    int nameErrorFlag=0;
  QString foodName = ui->newFoodName->text();
  QString temp1 = ui->newFoodPrice->text();
  QString temp2 = ui->newFoodStock->text();
  foodName = foodName.trimmed();
  for(int k=0;k<foodInfoArray.size();k++)
  {
      if(foodInfoArray[k].getFoodName()==foodName )
      {
          QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nThis name already in"), QMessageBox::Ok);
          nameErrorFlag=1;
          break;
      }
  }
  int foodPrice = temp1.split(" ")[0].toInt();
  int foodStock = temp2.split(" ")[0].toInt();
  if (foodName != "" && foodPrice > -1 && foodStock > -1 && nameErrorFlag==0)
  {
    foodObject.setAllFoodInfo(foodName, foodPrice, foodStock);
    foodInfoArray.push_back(foodObject);
    QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully added this food\nYou can add more food or exit"), QMessageBox::Ok);
    ui->newFoodName->clear();
    ui->newFoodPrice->clear();
    ui->newFoodStock->clear();
    qDebug() << foodInfoArray.size();
    saveFoodFile();
  }
  else
  {
    QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nFillup all information\nFor Food price or stock negative value isn't acceptable"), QMessageBox::Ok);
  }
}

// Delete food
void FoodiePalace::on_detailsBackButton_2_clicked()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, tr("Foodie Palace"), tr("You wanna delete this item?"),
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes)
  {
    for (int i = 0; i < foodInfoArray.size(); i++)
    {
      int pos = i;
      if (ui->foodNameLable->text() == foodInfoArray[i].getFoodName())
      {
        foodInfoArray.erase(foodInfoArray.begin() + (pos));
        break;
      }
    }
    ui->foodNameEdit->clear();
    ui->foodPriceEdit->clear();
    ui->foodStockEdit->clear();
    ui->foodNameLable->clear();
    ui->foodPriceLable->clear();
    ui->foodStockLable->clear();
    saveFoodFile();
    ui->foodListFoodMenu->clear();
    QIcon food = QIcon(":/new/prefix1/hot-pot.png");
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
    //ui->foodListFoodMenu->addItem(foodInfoArray[i].getFoodName());
  }
    QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully deleted this food\nYou can add more food or exit"), QMessageBox::Ok);
    ui->stackedWidget->setCurrentIndex(5);
    qDebug() << "Yes was clicked";
  }
  else
  {
    qDebug() << "Yes was *not* clicked";
  }
}

// Remove user from admin list
void FoodiePalace::on_removeUserButton_clicked()
{
  if (ui->userPositonDetails->text() != "Owner")
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Foodie Palace"), tr("You wanna delete this user?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      bool ok;
      QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                           tr("Password:"), QLineEdit::Password,
                                           "", &ok);
      for (int i = 0; i < ownerInfoArray.size(); i++)
      {
        if (ownerInfoArray[i].getIsOwner() == "Owner")
        {
          if (ok && !text.isEmpty() && text == ownerInfoArray[i].getPassword())
          {
            for (int j = 0; j < ownerInfoArray.size(); j++)
            {
              if (ui->userNameLableDetails->text() == ownerInfoArray[j].getUserName())
              {
                ownerInfoArray.erase(ownerInfoArray.begin() + (j));
                ui->userNameLableDetails->clear();
                ui->userAgeLableDetails->clear();
                ui->userGenderLableDetails->clear();
                ui->userMobileNumberLableDetails->clear();
                ui->userPositonDetails->clear();
                saveOwnerFile();
                ui->UserListWidget->clear();
                ui->UserListWidget->setIconSize(QSize(40, 40));
                QIcon crownWoman = QIcon(":/new/prefix1/CrownWoman.png");
                QIcon crownMan = QIcon(":/new/prefix1/CrownMan.png");
                QIcon Woman = QIcon(":/new/prefix1/womanED.png");
                QIcon Man = QIcon(":/new/prefix1/manEd.png");

                for (int i = 0; i < ownerInfoArray.size(); i++)
                {
                  if (ownerInfoArray[i].getIsOwner() == "Owner" && ownerInfoArray[i].getUserGender() == "Male")
                  {
                    QListWidgetItem *newItem = new QListWidgetItem;
                    QFont f;

                    f.setPointSize(18);
                    newItem->setText(ownerInfoArray[i].getUserName());
                    newItem->setIcon(QIcon(crownMan));
                    newItem->setFont(f);
                    ui->UserListWidget->addItem(newItem);
                  }
                  else if (ownerInfoArray[i].getIsOwner() == "Owner" && ownerInfoArray[i].getUserGender() == "Female")
                  {
                    QListWidgetItem *newItem = new QListWidgetItem;
                    QFont f;

                    f.setPointSize(18);
                    newItem->setText(ownerInfoArray[i].getUserName());
                    newItem->setIcon(QIcon(crownWoman));
                    newItem->setFont(f);
                    ui->UserListWidget->addItem(newItem);
                  }
                  else if (ownerInfoArray[i].getIsOwner() == "Partner" && ownerInfoArray[i].getUserGender() == "Male")
                  {
                    QListWidgetItem *newItem = new QListWidgetItem;
                    QFont f;

                    f.setPointSize(18);
                    newItem->setText(ownerInfoArray[i].getUserName());
                    newItem->setIcon(QIcon(Man));
                    newItem->setFont(f);
                    ui->UserListWidget->addItem(newItem);
                  }
                  else if (ownerInfoArray[i].getIsOwner() == "Partner" && ownerInfoArray[i].getUserGender() == "Female")
                  {
                    QListWidgetItem *newItem = new QListWidgetItem;
                    QFont f;

                    f.setPointSize(18);
                    newItem->setText(ownerInfoArray[i].getUserName());
                    newItem->setIcon(QIcon(Woman));
                    newItem->setFont(f);
                    ui->UserListWidget->addItem(newItem);
                  }
                }
                QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully deleted this user"), QMessageBox::Ok);
                ui->stackedWidget->setCurrentIndex(7);
                break;
              }
            }
            break;
          }
          else if (!ok)
          {
            break;
          }
          else
          {
            QMessageBox::warning(this, tr("Foodie Palace"), tr("Wrong password."), QMessageBox::Ok);
            break;
          }
        }
      }
    }
  }
  else
  {
    QMessageBox::warning(this, tr("Foodie Palace"), tr("You can't delete you information!"), QMessageBox::Ok);
  }
}

// Ownership transfer
void FoodiePalace::on_transferOwnershipButton_clicked()
{
  if (ui->userPositonDetails->text() != "Owner")
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Foodie Palace"), tr("You really wanna transfer Ownership?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      bool ok;
      QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                           tr("Password:"), QLineEdit::Password,
                                           "", &ok);
      text = text.trimmed();
      for (int i = 0; i < ownerInfoArray.size(); i++)
      {
        if (ownerInfoArray[i].getIsOwner() == "Owner")
        {
          if (ok && !text.isEmpty() && text == ownerInfoArray[i].getPassword())
          {
            for (int j = 0; j < ownerInfoArray.size(); j++)
            {
              if (ui->userNameLableDetails->text() == ownerInfoArray[j].getUserName())
              {
                ownerInfoArray[j].setIsOwner("Owner");
                ownerInfoArray[i].setIsOwner("Partner");
                ui->userPositonDetails->setText(ownerInfoArray[j].getIsOwner());
                saveOwnerFile();
                QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully transfered Ownership\nYou are an Employee now"), QMessageBox::Ok);
                fowner=0;
                ui->stackedWidget->setCurrentIndex(0);
                break;
              }
            }
            break;
          }
          else if (!ok)
          {
            break;
          }
          else
          {
            QMessageBox::warning(this, tr("Foodie Palace"), tr("Wrong password."), QMessageBox::Ok);
            break;
          }
        }
      }
    }
  }
  else
  {
    QMessageBox::warning(this, tr("Foodie Palace"), tr("You are the Owner!"), QMessageBox::Ok);
  }
}
int flagUserOwner = 0;

// owner dashboard to user information edit
void FoodiePalace::on_userInformationEditOwnerPushButton_clicked()
{
  QString userName = ui->usernameLableOwner->text();
  //readOwnerFile();
  for (int i = 0; i < ownerInfoArray.size(); i++)
  {
    if (userName == ownerInfoArray[i].getUserName())
    {
      flagUserOwner = 1;
      if (ownerInfoArray[i].getIsOwner() == "Owner")
      {
        if (ownerInfoArray[i].getUserGender() == "Male")
        {
          ui->userGenderShowLable->setStyleSheet("border-image:url(:/new/prefix1/CrownMan.png);");
        }
        else
        {
          ui->userGenderShowLable->setStyleSheet("border-image:url(:/new/prefix1/CrownWoman.png);");
        }
      }
      ui->usernameLable->setText(ownerInfoArray[i].getUserName());
      QString temp1;
      temp1 = QString::number(ownerInfoArray[i].getUserAge());
      ui->userAgeLable->setText(temp1);
      ui->userMobileNumberLable->setText(ownerInfoArray[i].getMobileNumber());
      ui->stackedWidget->setCurrentIndex(10);
      break;
    }
  }
}

// edit username
void FoodiePalace::on_usernameEditButton_clicked()
{
  int userNameFlag = 0;
  bool ok;
  QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                       tr("Enter new username: "), QLineEdit::Normal,
                                       "", &ok);
  text = text.trimmed();
  if (ok && text != "")
  {
    for (int j = 0; j < ownerInfoArray.size(); j++)
    {
      if (text == ownerInfoArray[j].getUserName() || ui->usernameLable->text() == text)
      {
        userNameFlag = 1;
        break;
      }
    }
    if (userNameFlag == 1)
    {
      QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again !\nYou can't use this name.\nUse unique name."), QMessageBox::Ok);
    }
    else if (userNameFlag == 0)
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

// edit user Age;

void FoodiePalace::on_userAgeEditButton_clicked()
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

//uedit mobile number
void FoodiePalace::on_mobileNumberEditButton_clicked()
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

//update all info
void FoodiePalace::on_userProfileUpdateButton_clicked()
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
    for (int i = 0; i < ownerInfoArray.size(); i++)
    {
      if (ui->usernameLableOwner->text() == ownerInfoArray[i].getUserName()|| ui->usernameLablePartner_2->text() == ownerInfoArray[i].getUserName())
      {
        if (ownerInfoArray[i].getPassword() == text)
        {
                ownerInfoArray[i].setUserName(userName);
                ownerInfoArray[i].setMobileNumber(mobileNumber);
                ownerInfoArray[i].setUserAge(userAge);
                ui->usernameLableOwner->setText(userName);
                ui->usernameLablePartner_2->setText(userName);
                QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully updated."), QMessageBox::Ok);
                saveOwnerFile();
                break;

        }
        else
        {
          QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!\nWrong password."), QMessageBox::Ok);
          break;
        }
      }
    }
  }
}

//profile edit to back;
void FoodiePalace::on_profileBackButton_clicked()
{
  if (fowner == 1)
  {
    ui->stackedWidget->setCurrentIndex(3);
  }
  else
  {
    ui->stackedWidget->setCurrentIndex(4);
  }
}

//partner dashboard to user information edit
void FoodiePalace::on_userInformationEditPartnerButton_clicked()
{
    QString userName = ui->usernameLablePartner_2->text();
    //readOwnerFile();
    for (int i = 0; i < ownerInfoArray.size(); i++)
    {
      if (userName == ownerInfoArray[i].getUserName())
      {
        if (ownerInfoArray[i].getIsOwner() == "Partner")
        {
          if (ownerInfoArray[i].getUserGender() == "Male")
          {
            ui->userGenderShowLable->setStyleSheet("border-image:url(:/new/prefix1/manEd.png);");
          }
          else
          {
            ui->userGenderShowLable->setStyleSheet("border-image:url(:/new/prefix1/womanED.png);");
          }
        }
        ui->usernameLable->setText(ownerInfoArray[i].getUserName());
        QString temp1;
        temp1 = QString::number(ownerInfoArray[i].getUserAge());
        ui->userAgeLable->setText(temp1);
        ui->userMobileNumberLable->setText(ownerInfoArray[i].getMobileNumber());
        ui->stackedWidget->setCurrentIndex(10);
        break;
      }
    }
}

//change password
void FoodiePalace::on_pushButton_2_clicked()
{
    QString userName1= ui->usernameLableOwner->text();
    QString userName2= ui->usernameLablePartner_2->text();
    for(int i=0;i<ownerInfoArray.size();i++)
    {
        if(userName1==ownerInfoArray[i].getUserName() || userName2==ownerInfoArray[i].getUserName())
        {
            bool ok;
            QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                                 tr("Enter your old password:"), QLineEdit::Password,
                                                 "", &ok);
            text=text.trimmed();
            if(ok && text == ownerInfoArray[i].getPassword())
            {
                bool okk;
                QString text2 = QInputDialog::getText(this, tr("Foodie Palace"),
                                                     tr("Enter your new password:"), QLineEdit::Password,
                                                     "", &okk);
                text2=text2.trimmed();
                if(okk && text2 != "")
                {
                    ownerInfoArray[i].setPassword(text2);
                    QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully updated password."), QMessageBox::Ok);
                    saveOwnerFile();
                    break;
                }
                else if(okk)
                {
                    QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!"), QMessageBox::Ok);
                    break;
                }
            }
            else if(ok)
            {
                QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!\nWrong password."), QMessageBox::Ok);
                break;
            }

        }
    }
}


//Selling history to admin dashboard
void FoodiePalace::on_profileBackButton_2_clicked()
{
    for(int i=0;i<ownerInfoArray.size();i++)
    {
        if(ui->usernameLableOwner->text()==ownerInfoArray[i].getUserName() || ui->usernameLablePartner_2->text()==ownerInfoArray[i].getUserName())
        {
            if(ownerInfoArray[i].getIsOwner()=="Owner")
            {
                ui->stackedWidget->setCurrentIndex(3);
                break;
            }
            else
            {
                ui->stackedWidget->setCurrentIndex(4);
                break;
            }
        }
    }
       ui->tableWidget->setRowCount(0);
       ui->tableWidget->setColumnCount(0);

}

//Admin dashboard to selling history
void FoodiePalace::on_sellingHistoryOwnerButton_clicked()
{

    readHistoryFile();
    QStringList coloumnName;
    ui->tableWidget->setColumnCount(5);
    coloumnName << "Food Name" << "" << "Amount" << "" << "Price";
    ui->tableWidget->setHorizontalHeaderLabels(coloumnName);
    ui->stackedWidget->setCurrentIndex(11);
    int totalEarning=0;
    for(int i=0;i<historyFoodnames.size();i++)
    {
        QString fName=historyFoodnames[i];
        int fAmount= historyData[historyFoodnames[i]].first;
        int fPrice= historyData[historyFoodnames[i]].second;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowCounter = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(rowCounter,0,new QTableWidgetItem(fName));
        ui->tableWidget->setItem(rowCounter,2,new QTableWidgetItem(QString::number(fAmount)));
        ui->tableWidget->setItem(rowCounter,4,new QTableWidgetItem(QString::number(fPrice)));
        totalEarning+=fPrice;

    }
    ui->totalEarningLable->setText(QString::number(totalEarning));
}

//Partner desh board to selling history
void FoodiePalace::on_sellingHistoryPartnerButton_clicked()
{
    readHistoryFile();
    QStringList coloumnName;
    ui->tableWidget->setColumnCount(5);
    coloumnName << "Food Name" << "" << "Amount" << "" << "Price";
    ui->tableWidget->setHorizontalHeaderLabels(coloumnName);
    ui->stackedWidget->setCurrentIndex(11);
    int totalEarning=0;
    for(int i=0;i<historyFoodnames.size();i++)
    {
        QString fName=historyFoodnames[i];
        int fAmount= historyData[historyFoodnames[i]].first;
        int fPrice= historyData[historyFoodnames[i]].second;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int rowCounter = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(rowCounter,0,new QTableWidgetItem(fName));
        ui->tableWidget->setItem(rowCounter,2,new QTableWidgetItem(QString::number(fAmount)));
        ui->tableWidget->setItem(rowCounter,4,new QTableWidgetItem(QString::number(fPrice)));
        totalEarning+=fPrice;

    }
    ui->totalEarningLable->setText(QString::number(totalEarning));
}

//Clear history
void FoodiePalace::on_clearHistory_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Foodie Palace"), tr("Clear History?"),QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      bool ok;
      QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                           tr("Password:"), QLineEdit::Password,
                                           "", &ok);
      text = text.trimmed();
      for(int i=0;i<ownerInfoArray.size();i++)
      {
          if(ownerInfoArray[i].getUserName()==ui->usernameLableOwner->text() || ownerInfoArray[i].getUserName()==ui->usernameLablePartner_2->text())
          {
              if(ownerInfoArray[i].getPassword()==text)
              {
                  ui->tableWidget->setRowCount(0);
                  ui->tableWidget->setColumnCount(0);
                  QStringList coloumnName;
                  ui->tableWidget->setColumnCount(5);
                  coloumnName << "Food Name" << "" << "Amount" << "" << "Price";
                  ui->tableWidget->setHorizontalHeaderLabels(coloumnName);
                  saveHistoryFile();
                  QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully cleard."), QMessageBox::Ok);
                  break;
              }
              else
              {
                  QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!\nWrong password."), QMessageBox::Ok);
                  break;
              }
          }
      }
    }
}

//delete all item from foodmenu
void FoodiePalace::on_foodAddButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Foodie Palace"), tr("Clear all items?"),QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      bool ok;
      QString text = QInputDialog::getText(this, tr("Foodie Palace"),
                                           tr("Password:"), QLineEdit::Password,
                                           "", &ok);
      text = text.trimmed();
      for(int i=0;i<ownerInfoArray.size();i++)
      {
          if(ownerInfoArray[i].getUserName()==ui->usernameLableOwner->text() || ownerInfoArray[i].getUserName()==ui->usernameLablePartner_2->text())
          {
              if(ownerInfoArray[i].getPassword()==text)
              {
                  foodInfoArray.clear();
                  saveFoodFile();
                  ui->foodListFoodMenu->clear();
                  QMessageBox::information(this, tr("Foodie Palace"), tr("Successfully cleard."), QMessageBox::Ok);
                  break;
              }
              else
              {
                  QMessageBox::warning(this, tr("Foodie Palace"), tr("Try again!\nWrong password."), QMessageBox::Ok);
                  break;
              }
          }
      }
    }

}

