#include "addbookdialog.h"
#include "ui_addbookdialog.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QCompleter>


void AddBookDialog::basicInit(){//обнуление всех полей
    ui->backButton->setVisible(false);
    ui->backButton->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(0);
    ui->nextButton->setText("Далее");
    ui->spinBoxAmountBook->setValue(0);
    ui->editBookName->clear();
    ui->editBookCategory->clear();
   // ui->editBookAuthorMiddleName->clear();
    ui->editBookAuthorName->clear();
    ui->editBookAuthorSurname->clear();
    ui->editUDKCode->clear();
    ui->labelAddNewAuthorBack->setVisible(false);
    ui->labelAddNewAuthorForward->setVisible(false);
    this->currentAuthorBook = 0;
    this->authorNames.clear();
    this->bookAuthorNamesList.clear();
    this->bookAuthorNames = new QCompleter(this->bookAuthorNamesList,this);
    ui->editBookAuthorName->setCompleter(this->bookAuthorNames);
}

void AddBookDialog::closeEvent(QCloseEvent *event){
    this->basicInit();

}

AddBookDialog::AddBookDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
    this->basicInit();
    activequery = QSqlQuery(QSqlDatabase::database("libj"));
    this->currentAuthorBook = 0;
    activequery.exec("SELECT * FROM bookCategoryTable");

    while(activequery.next()){
        this->bookCategoryList<<activequery.value(1).toString();
    }

    activequery.exec("SELECT authorSurname FROM authorTable");
    while(activequery.next()){
        this->bookAuthorSurnameList<<activequery.value(0).toString();
    }
    bookAuthorSurnameList.removeDuplicates();
    this->bookAuthorSurnames = new QCompleter(this->bookAuthorSurnameList,this);
    this->bookAuthorSurnames->setCaseSensitivity(Qt::CaseInsensitive);
    ui->editBookAuthorSurname->setCompleter(this->bookAuthorSurnames);

}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}


void AddBookDialog::on_nextButton_clicked()
{
    if((ui->stackedWidget->currentIndex()<ui->stackedWidget->count()-1)){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
        ui->backButton->setEnabled(true);
        ui->backButton->setVisible(true);
        if(ui->stackedWidget->currentIndex()==ui->stackedWidget->count()-1){
            ui->nextButton->setText("Завершить");
        }
    }
    else if(ui->stackedWidget->currentIndex()==ui->stackedWidget->count()-1){
        //тут код занесения в базу данных




        this->close();
        this->basicInit();
    }
}

void AddBookDialog::on_cancelButton_clicked()
{
    if(QMessageBox::warning(this,
                            "Подтверждение",
                            "Вы уверены, что хотите отменить?",
                            QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok){
        this->close();
        this->basicInit();
    }

}



void AddBookDialog::on_backButton_clicked()
{
    if(ui->stackedWidget->currentIndex()>0){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
        ui->nextButton->setText("Далее");
        if(ui->stackedWidget->currentIndex()==0){
            ui->backButton->setEnabled(false);
            ui->backButton->setVisible(false);
        }
    }
    else{
    }
}



void AddBookDialog::on_labelAddNewAuthor_linkActivated(const QString &link)
{
    if(this->authorNames.size() == currentAuthorBook){
        vector <QString> tmp;
        this->authorNames.push_back(tmp);
        this->authorNames[this->authorNames.size()-1].push_back(ui->editBookAuthorName->text());
        this->authorNames[this->authorNames.size()-1].push_back(ui->editBookAuthorSurname->text());
        //this->authorNames[this->authorNames.size()-1].push_back(ui->editBookAuthorMiddleName->text());
        ui->editBookAuthorName->clear();
        ui->editBookAuthorSurname->clear();
        //ui->editBookAuthorMiddleName->clear();
        ui->labelAddNewAuthorForward->setVisible(false);
        ui->labelAddNewAuthorForward->setEnabled(false);
    }else{
        currentAuthorBook = authorNames.size();
        ui->editBookAuthorName->clear();
        ui->editBookAuthorSurname->clear();
        //ui->editBookAuthorMiddleName->clear();
        ui->labelAddNewAuthorBack->setVisible(true);
        ui->labelAddNewAuthorBack->setEnabled(true);
        ui->labelAddNewAuthorForward->setVisible(false);
        ui->labelAddNewAuthorForward->setEnabled(false);
        return;
    }

    this->currentAuthorBook++;
    ui->labelAddNewAuthorBack->setVisible(true);
    ui->labelAddNewAuthorBack->setEnabled(true);
}

void AddBookDialog::on_labelAddNewAuthorBack_linkActivated(const QString &link)
{

    if(currentAuthorBook==this->authorNames.size()){
        vector <QString> tmp;
        this->authorNames.push_back(tmp);
        this->authorNames[this->authorNames.size()-1].push_back(ui->editBookAuthorName->text());
        this->authorNames[this->authorNames.size()-1].push_back(ui->editBookAuthorSurname->text());
        //this->authorNames[this->authorNames.size()-1].push_back(ui->editBookAuthorMiddleName->text());
    }

    ui->editBookAuthorName->setText(this->authorNames[currentAuthorBook-1][0]);
    ui->editBookAuthorSurname->setText(this->authorNames[currentAuthorBook-1][1]);
    //ui->editBookAuthorMiddleName->setText(this->authorNames[currentAuthorBook-1][2]);

    this->currentAuthorBook--;
    if(currentAuthorBook==0){
        ui->labelAddNewAuthorBack->setVisible(false);
        ui->labelAddNewAuthorBack->setEnabled(false);
    }

    if(currentAuthorBook<authorNames.size() && authorNames.size()!=0){
        ui->labelAddNewAuthorForward->setVisible(true);
        ui->labelAddNewAuthorForward->setEnabled(true);
    }


}

void AddBookDialog::on_labelAddNewAuthorForward_linkActivated(const QString &link)
{

    this->currentAuthorBook++;
    ui->labelAddNewAuthorBack->setVisible(true);
    ui->labelAddNewAuthorBack->setEnabled(true);

    ui->editBookAuthorName->setText(this->authorNames[currentAuthorBook][0]);
    ui->editBookAuthorSurname->setText(this->authorNames[currentAuthorBook][1]);
    //ui->editBookAuthorMiddleName->setText(this->authorNames[currentAuthorBook][2]);


    qDebug()<<"Author.size() "<<QString::number(authorNames.size());
    qDebug()<<"currentAuthorBook "<<QString::number(currentAuthorBook);
    if(currentAuthorBook==this->authorNames.size()-1){
        ui->labelAddNewAuthorForward->setVisible(false);
        ui->labelAddNewAuthorForward->setEnabled(false);
    }
}

void AddBookDialog::on_btnChoosePhoto_clicked()
{
    QString path = QFileDialog::getOpenFileName(0,QObject::tr("Укажите файл фотографии"),QDir::homePath(), QObject::tr("Файл картинки (*.png);;Файл картинки (*.jpg)"));
    ui->labelFilePath->setText(path);
    qDebug()<<path;
}

void AddBookDialog::on_editBookAuthorSurname_editingFinished()
{
    activequery.prepare("SELECT authorName from authorTable WHERE authorSurname=?");
    activequery.addBindValue(ui->editBookAuthorSurname->text());
    activequery.exec();
    while(activequery.next()){
        this->bookAuthorNamesList<<activequery.value(0).toString();
    }

    this->bookAuthorNamesList.removeDuplicates();
    this->bookAuthorNames = new QCompleter(this->bookAuthorNamesList,this);
    this->bookAuthorNames->setCaseSensitivity(Qt::CaseInsensitive);
    ui->editBookAuthorName->setCompleter(this->bookAuthorNames);
}

