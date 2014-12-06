#include "editbookdialog.h"
#include "ui_editbookdialog.h"
#include <QCompleter>
#include <qdebug>
#include <string>
#include <QPixmap>
editbookdialog::editbookdialog(QSqlRecord *rec , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editbookdialog)
{
    ui->setupUi(this);

    activeDB = QSqlDatabase::database("libj");

    initTableInfo(0);
    initTableInfo(1);
    initTableInfo(2);
    initTableInfo(3);

    ui->bookNameLineEdit->setText(rec->value("bookName").toString());
    ui->UDKCodeLineEdit->setText(rec->value("bookUDKCode").toString());
    ui->categoryLineEdit->setText(rec->value("categoryName").toString());

    query = new QSqlQuery(tr("SELECT SUBSTRING(imgSource,9) FROM bookinfotable WHERE bookUDKCode = '%1'").arg(ui->UDKCodeLineEdit->text()),activeDB);
    query->next();
    /*О я ебу почему это не работает отсюда*/
    QString val(query->record().value(0).toString());
    QString picturePath(tr("C:\\images\\%1").arg(val));
    QPixmap pict(picturePath);
    qDebug()<<pict;
    qDebug()<<picturePath;
    //qDebug()<<picturePath.length();
    ui->pictureLabel->setPixmap(pict);
    //До этого момента
    //so fun code

            query = new QSqlQuery(tr("SELECT authorName,authorSurname FROM authorTable,bookConnectTable WHERE "
                                  "(bookConnectTable.bookUDKCode = '%1') and "
                                  "(authorTable.authorID = bookConnectTable.authorID)").arg(rec->value("bookUDKCode").toString()),activeDB);
            this->currentAuthorBook = 0;
            while(query->next()){
                vector <QString> tmp;
                QSqlRecord rec1 = query->record();
                //qDebug()<<query->record().value("authorSurname").toString();
                tmp.push_back(rec1.value("authorSurname").toString());
                tmp.push_back(rec1.value("authorName").toString());
                authorNames.push_back(tmp);
            };

            ui->surnameLineEdit->setText(authorNames[0][0]);
            ui->nameLineEdit->setText(authorNames[0][1]);

            ui->linkBack->setVisible(false);
            ui->linkBack->setEnabled(false);
            if(query->size()-1!=0){
                ui->linkForward->setVisible(true);
                ui->linkForward->setEnabled(true);
            }else{
                ui->linkForward->setVisible(false);
                ui->linkForward->setEnabled(false);
            }


    //end of so fun code
}

editbookdialog::editbookdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editbookdialog)
{
    ui->setupUi(this);

}


editbookdialog::~editbookdialog()
{
    delete ui;
}


void editbookdialog::initTableInfo( int fieldInit ) {

    switch( fieldInit ) {

        case 0 :
            bookCategoryList.clear();
            query = new QSqlQuery( "SELECT * FROM bookCategoryTable" , activeDB ) ;
            while( query->next() ) {
                bookCategoryList << query->value( "categoryName" ).toString() ;
            }
            bookCategory = new QCompleter(bookCategoryList,this);
            bookCategory->setCaseSensitivity(Qt::CaseInsensitive);
            ui->categoryLineEdit->setCompleter(bookCategory);
            break ;

        case 1 :
            authorSurnameList.clear();
            query = new QSqlQuery( "SELECT * FROM authorTable GROUP BY authorSurname" , activeDB );
            while( query->next() ) {
                authorSurnameList << query->value( "authorSurname" ).toString() ;
            }
            completerAuthorSurname = new QCompleter(authorSurnameList,this);
            completerAuthorSurname->setCaseSensitivity(Qt::CaseInsensitive);
            ui->surnameLineEdit->setCompleter(completerAuthorSurname);
            break ;

        case 2 :
            authorNameList.clear();
            query = new QSqlQuery( tr( "SELECT * FROM authorTable WHERE authorSurname = '%1'" ).arg( ui->surnameLineEdit->text() ) ,
                        activeDB ) ;
            while( query->next() ) {
                authorNameList << query->value( "authorName" ).toString() ;
            }
            completerAuthorName = new QCompleter(authorNameList,this);
            completerAuthorName->setCaseSensitivity(Qt::CaseInsensitive);
            ui->nameLineEdit->setCompleter(completerAuthorName);
            break ;

        case 3 :
            bookNameList.clear();
            bookUDKCodeList.clear();
            query = new QSqlQuery( tr( "SELECT bookName,bookInfoTable.bookUDKCode FROM bookInfoTable,authorTable,bookConnectTable WHERE (authorTable.authorName = '%1') and "
                     "(authorTable.authorSurname = '%2') and (bookConnectTable.authorID = authorTable.authorID) and "
                    "(bookInfoTable.bookUDKCode = bookConnectTable.bookUDKCode)" ).arg( ui->nameLineEdit->text() ,
                                                                                   ui->surnameLineEdit->text()) , activeDB ) ;
            while( query->next() ) {
                bookNameList << query->value( "bookName" ).toString() ;
                bookUDKCodeList << query->value( "bookUDKCode" ).toString() ;
            }

            completerBookName = new QCompleter(bookNameList,this);
            completerBookName->setCaseSensitivity(Qt::CaseInsensitive);
            ui->bookNameLineEdit->setCompleter(completerBookName);

            bookUDKCode = new QCompleter(bookUDKCodeList,this);
            bookUDKCode->setCaseSensitivity(Qt::CaseInsensitive);
            ui->UDKCodeLineEdit->setCompleter(bookUDKCode);

            break ;

       case 4:
            authorNameList.clear();
            authorSurnameList.clear();
            bookUDKCodeList.clear();
            authorNames.clear();
            query = new QSqlQuery(tr("SELECT authorName,authorSurname,bookInfoTable.bookUDKCode FROM authorTable,bookConnectTable,bookInfoTable WHERE "
                                     "(bookInfoTable.bookName = '%1') and (bookConnectTable.bookUDKCode = bookInfoTable.bookUDKCode) and "
                                     "(authorTable.authorID = bookConnectTable.authorID)").arg(ui->bookNameLineEdit->text()),activeDB);
            while(query->next()){
                vector <QString> tmp;
                qDebug()<<"hello";
                tmp.push_back(query->value("authorSurname").toString());
                tmp.push_back(query->value("authorName").toString());
                authorSurnameList<<query->value("authorSurname").toString();
                authorNameList<<query->value("authorName").toString();
                authorNames.push_back(tmp);
                bookUDKCodeList<<query->value(2).toString();
            }


            this->currentAuthorBook=0;
            ui->surnameLineEdit->setText(authorNames[0][0]);
            ui->nameLineEdit->setText(authorNames[0][1]);
            ui->linkBack->setVisible(false);
            ui->linkBack->setEnabled(false);
            if(query->size()-1!=0){
                ui->linkForward->setVisible(true);
                ui->linkForward->setEnabled(true);
            }else{
                ui->linkForward->setVisible(false);
                ui->linkForward->setEnabled(false);
            }

            completerAuthorName = new QCompleter(authorNameList,this);
            completerAuthorSurname = new QCompleter(authorSurnameList,this);
            bookUDKCode = new QCompleter(bookUDKCodeList,this);

            completerAuthorName->setCaseSensitivity(Qt::CaseInsensitive);
            completerAuthorSurname->setCaseSensitivity(Qt::CaseInsensitive);
            bookUDKCode->setCaseSensitivity(Qt::CaseInsensitive);

            ui->nameLineEdit->setCompleter(completerAuthorName);
            ui->surnameLineEdit->setCompleter(completerAuthorSurname);
            ui->UDKCodeLineEdit->setCompleter(bookUDKCode);


            break;
    }
}



void editbookdialog::on_surnameLineEdit_editingFinished()
{
    initTableInfo(2); //обновим выадающий комплитер для имен
}

void editbookdialog::on_nameLineEdit_editingFinished()
{
    initTableInfo(3); // обновим инфу о книге УДК,название
}





void editbookdialog::on_linkBack_linkActivated(const QString &link)
{
    if(currentAuthorBook==this->authorNames.size()){
        vector <QString> tmp;
        this->authorNames.push_back(tmp);
        this->authorNames[this->authorNames.size()-1].push_back(ui->surnameLineEdit->text());
        this->authorNames[this->authorNames.size()-1].push_back(ui->nameLineEdit->text());
    }

    ui->surnameLineEdit->setText(this->authorNames[currentAuthorBook-1][0]);
    ui->nameLineEdit->setText(this->authorNames[currentAuthorBook-1][1]);

    this->currentAuthorBook--;
    if(currentAuthorBook==0){
        ui->linkBack->setVisible(false);
        ui->linkBack->setEnabled(false);
    }

    if(currentAuthorBook<authorNames.size() && authorNames.size()!=0){
        ui->linkForward->setVisible(true);
        ui->linkForward->setEnabled(true);
    }
}

void editbookdialog::on_linkForward_linkActivated(const QString &link)
{
    this->currentAuthorBook++;
    ui->linkBack->setVisible(true);
    ui->linkBack->setEnabled(true);

    ui->surnameLineEdit->setText(this->authorNames[currentAuthorBook][0]);
    ui->nameLineEdit->setText(this->authorNames[currentAuthorBook][1]);

    if(currentAuthorBook==this->authorNames.size()-1){
        ui->linkForward->setVisible(false);
        ui->linkForward->setEnabled(false);
    }
}

void editbookdialog::on_linkAppendAuthor_linkActivated(const QString &link)
{
    if(this->authorNames.size() == currentAuthorBook){
        vector <QString> tmp;
        this->authorNames.push_back(tmp);
        this->authorNames[this->authorNames.size()-1].push_back(ui->surnameLineEdit->text());
        this->authorNames[this->authorNames.size()-1].push_back(ui->nameLineEdit->text());
        ui->nameLineEdit->clear();
        ui->surnameLineEdit->clear();
        ui->linkForward->setVisible(false);
        ui->linkForward->setEnabled(false);
    }else{
        currentAuthorBook = authorNames.size();
        ui->nameLineEdit->clear();
        ui->surnameLineEdit->clear();
        ui->linkBack->setVisible(true);
        ui->linkBack->setEnabled(true);
        ui->linkForward->setVisible(false);
        ui->linkForward->setEnabled(false);
        return;
    }

    this->currentAuthorBook++;
    ui->linkBack->setVisible(true);
    ui->linkBack->setEnabled(true);
}

void editbookdialog::on_bookNameLineEdit_editingFinished()
{
    initTableInfo(4);
}

void editbookdialog::on_bookNameLineEdit_textChanged(const QString &arg1)
{
    bookNameList.clear();
    query = new QSqlQuery(tr("SELECT bookName FROM bookInfoTable WHERE instr(bookName,'%1')=1").arg(ui->bookNameLineEdit->text()),activeDB);
    while(query->next()){
        bookNameList<<query->value(0).toString();
    }
    completerBookName = new QCompleter(bookNameList,this);
    completerBookName->setCaseSensitivity(Qt::CaseInsensitive);
    ui->bookNameLineEdit->setCompleter(completerBookName);

}
