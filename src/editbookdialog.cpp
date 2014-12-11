#include "editbookdialog.h"
#include "ui_editbookdialog.h"
#include <QCompleter>
#include <qdebug>
#include <string>
#include <QPixmap>
#include <QFileDialog>
#include <QAbstractButton>
#include <QSqlQueryModel>

////////////////////////////
editbookdialog::editbookdialog( QSqlRecord *rec , QWidget *parent ) :
    QDialog(parent),
    ui( new Ui::editbookdialog ) {

    ui->setupUi(this);

    activeDB = QSqlDatabase::database("libj");
    mode=1;

    initTableInfo(0);
    initTableInfo(1);
    initTableInfo(2);
    initTableInfo(3);

    ui->bookNameLineEdit->setText(rec->value("bookName").toString());
    ui->UDKCodeLineEdit->setText(rec->value("bookUDKCode").toString());
    ui->categoryLineEdit->setText(rec->value("categoryName").toString());

    query = new QSqlQuery(tr("SELECT SUBSTRING(imgSource,9) FROM bookinfotable WHERE bookUDKCode = '%1'").arg(ui->UDKCodeLineEdit->text()),activeDB);
    query->next();
    QString val(query->record().value(0).toString());
    val.truncate(val.length()-4);
    QString picturePath(tr("C:/images/%1.png").arg(val));
    QPixmap pict(picturePath);


    //ui->pictureLabel->setPixmap(pict);

    //so fun code

    query = new QSqlQuery(tr("SELECT authorName,authorSurname FROM authorTable,bookConnectTable WHERE "
                             "(bookConnectTable.bookUDKCode = '%1') and "
                             "(authorTable.authorID = bookConnectTable.authorID)")
                            .arg(rec->value("bookUDKCode").toString()),activeDB);

   this->currentAuthorBook = 0;
   while(query->next()){
        vector <QString> tmp;
        QSqlRecord rec1 = query->record();
        tmp.push_back(rec1.value("authorSurname").toString());
        tmp.push_back(rec1.value("authorName").toString());
        authorNames.push_back(tmp);
   }

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

   QSqlQueryModel *model = new QSqlQueryModel();
   model->setQuery(tr("SELECT bookID FROM bookCatalogueTable WHERE bookUDKCode = '%1' AND "
                      "bookID NOT IN (SELECT bookID FROM requestTable"
                      " WHERE (status!='Читальный зал' AND "
                      " status!='На руках'))")
                   .arg(ui->UDKCodeLineEdit->text()),activeDB);
    model->query().exec();    
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,300);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();

    for (int i=0;i<authorNames.size();i++){
        defaultAuthorSurname.push_back(authorNames[i][0]);
        defaultAuthorName.push_back(authorNames[i][1]);
    }

}

////////////////////////////
editbookdialog::editbookdialog( QWidget *parent ) :
    QDialog(parent),
    ui( new Ui::editbookdialog ) {

    ui->setupUi(this);
    activeDB = QSqlDatabase::database("libj");
    mode = 0;
    ui->deleteBtn->setVisible(false);
    ui->deleteBtn->setEnabled(false);

    initTableInfo(0);
    initTableInfo(1);

    ui->linkBack->setVisible(false);
    ui->linkBack->setEnabled(false);
    ui->linkForward->setVisible(false);
    ui->linkForward->setEnabled(false);
    ui->tableView->setVisible(false);
    ui->tableView->setEnabled(false);

    this->currentAuthorBook = 0;

    for (int i=0;i<authorNames.size();i++){
        defaultAuthorSurname.push_back(authorNames[i][0]);
        defaultAuthorName.push_back(authorNames[i][1]);
    }

}

////////////////////////////
editbookdialog::~editbookdialog() {
    delete ui;
}

/////////////////////////////
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
            query = new QSqlQuery( tr( "SELECT * FROM authorTable WHERE authorSurname = '%1'" )
                                   .arg( ui->surnameLineEdit->text() ) ,
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
            query = new QSqlQuery( tr( "SELECT bookName,bookInfoTable.bookUDKCode FROM "
                                       "bookInfoTable,authorTable,bookConnectTable WHERE "
                                       "(authorTable.authorName = '%1') and "
                                       "(authorTable.authorSurname = '%2') and "
                                       "(bookConnectTable.authorID = authorTable.authorID) and "
                                       "(bookInfoTable.bookUDKCode = bookConnectTable.bookUDKCode)" )
                                        .arg( ui->nameLineEdit->text() ,
                                         ui->surnameLineEdit->text()) ,
                                         activeDB ) ;

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
            query = new QSqlQuery(tr("SELECT authorName,authorSurname,bookInfoTable.bookUDKCode "
                                     "FROM authorTable,bookConnectTable,bookInfoTable WHERE "
                                     "(bookInfoTable.bookName = '%1') and "
                                     "(bookConnectTable.bookUDKCode = bookInfoTable.bookUDKCode) and "
                                     "(authorTable.authorID = bookConnectTable.authorID)")
                                  .arg(ui->bookNameLineEdit->text()),activeDB);
            while(query->next()){
                vector <QString> tmp;
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



////////////////////////////
void editbookdialog::on_surnameLineEdit_editingFinished(){
    if(mode!=0){
        vector <QString> tmp;
        tmp.push_back(ui->surnameLineEdit->text());
        tmp.push_back("");
        authorNames.push_back(tmp);
    }else{
        authorNames[currentAuthorBook][0]=ui->surnameLineEdit->text();
    }
    initTableInfo(2); //обновим выпадающий комплитер для имен
}

////////////////////////////
void editbookdialog::on_nameLineEdit_editingFinished(){
      if(mode!=0)
        authorNames[authorNames.size()-1][1] = ui->nameLineEdit->text();
      else
        authorNames[currentAuthorBook][1] = ui->nameLineEdit->text();
      initTableInfo(3); // обновим инфу о книге УДК,название
}

////////////////////////////
void editbookdialog::on_linkBack_linkActivated(const QString &link){
    if(currentAuthorBook==this->authorNames.size()){
        vector <QString> tmp;
        this->authorNames.push_back(tmp);
        this->authorNames[this->authorNames.size()-1].push_back(ui->nameLineEdit->text());
        this->authorNames[this->authorNames.size()-1].push_back(ui->surnameLineEdit->text());
    }

    ui->nameLineEdit->setText(this->authorNames[currentAuthorBook-1][1]);
    ui->surnameLineEdit->setText(this->authorNames[currentAuthorBook-1][0]);

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

////////////////////////////
void editbookdialog::on_linkForward_linkActivated(const QString &link){
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

////////////////////////////
void editbookdialog::on_linkAppendAuthor_linkActivated(const QString &link){

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
        vector <QString> tmp;
        currentAuthorBook = authorNames.size();
        this->authorNames.push_back(tmp);
        this->authorNames[this->authorNames.size()-1].push_back(ui->surnameLineEdit->text());
        this->authorNames[this->authorNames.size()-1].push_back(ui->nameLineEdit->text());


        ui->nameLineEdit->clear();
        ui->surnameLineEdit->clear();
        ui->linkBack->setVisible(true);
        ui->linkBack->setEnabled(true);
        ui->linkForward->setVisible(false);
        ui->linkForward->setEnabled(false);
    }

    this->currentAuthorBook++;
    ui->linkBack->setVisible(true);
    ui->linkBack->setEnabled(true);
}

////////////////////////////
void editbookdialog::on_bookNameLineEdit_editingFinished(){
    if (mode==0){
        initTableInfo(0);
        initTableInfo(1);
    }
}

////////////////////////////
void editbookdialog::on_bookNameLineEdit_textChanged(const QString &arg1){
    bookNameList.clear();
    query = new QSqlQuery(tr("SELECT bookName FROM bookInfoTable"
                             " WHERE instr(bookName,'%1')=1")
                             .arg(ui->bookNameLineEdit->text()),activeDB);

    while(query->next()){
        bookNameList<<query->value(0).toString();
    }

    completerBookName = new QCompleter(bookNameList,this);
    completerBookName->setCaseSensitivity(Qt::CaseInsensitive);
    ui->bookNameLineEdit->setCompleter(completerBookName);

}

////////////////////////////
void editbookdialog::on_editbookdialog_accepted(){

}


////////////////////////////
void editbookdialog::on_buttonBox_accepted(){

    vector <int> authorIndexes;
    int categoryID;

    if(bookCategoryList.contains(ui->categoryLineEdit->text())){
        query = new QSqlQuery(tr("SELECT categoryID FROM bookCategoryTable "
                                 "WHERE categoryName = '%1'")
                                 .arg(ui->categoryLineEdit->text()),activeDB);
        query->next();
        categoryID = query->value(0).toInt();
    }else{
        query = new QSqlQuery(tr("INSERT INTO bookCategoryTable "
                                 "(categoryName) VALUES ('%1')")
                                 .arg(ui->categoryLineEdit->text()),activeDB);
        query = new QSqlQuery(tr("SELECT categoryID FROM bookCategoryTable WHERE categoryName = '%1'")
                                 .arg(ui->categoryLineEdit->text()),activeDB);
        query->next();
        categoryID = query->value(0).toInt();
    }
    qDebug()<<"DElete that fucking authors";
    query = new QSqlQuery(tr("SELECT * FROM bookInfoTable WHERE "
                             "bookName='%1' and bookUDKCode='%2'")
                             .arg(ui->bookNameLineEdit->text(),
                                  ui->UDKCodeLineEdit->text()),
                          activeDB);

    if(query->size()==0){
        query = new QSqlQuery("SELECT * FROM bookInfoTable",activeDB);
        int size = query->size();
        this->path = "";
        query = new QSqlQuery(tr("INSERT INTO bookInfoTable "
                                 "(bookUDKCode,categoryID,"
                                 "bookName,imgSource) VALUES "
                                 "('%1',%2,'%3','%4')")
                              .arg(ui->UDKCodeLineEdit->text(),
                                   QString::number(categoryID),
                                   ui->bookNameLineEdit->text(),
                                  "C:/images/"+QString::number(size+1)+".png"),
                              activeDB);
    }else{
        /*query = new QSqlQuery(tr("UPDATE bookInfoTable SET bookUDKCode = '%1',"
                                 "bookName = '%2' WHERE bookUDKCode = '%1'")
                              .arg(ui->UDKCodeLineEdit->text(),
                                   ui->nameLineEdit->text()),
                              activeDB);

        query = new QSqlQuery(tr("UPDATE bookConnectTable SET bookUDKCode = '%1' "
                                 "WHERE bookUDKCode = '%1'")
                              .arg(ui->UDKCodeLineEdit->text()),
                              activeDB);*/

        for(int i=0;i<defaultAuthorName.size();i++){

            query = new QSqlQuery(tr("UPDATE authorTable SET authorName = '%1', "
                                     "authorSurname = '%2' WHERE "
                                     "authorName = '%3' and authorSurname = '%4'")
                                  .arg(authorNames[i][1],
                                       authorNames[i][0],
                                       defaultAuthorName[i],
                                       defaultAuthorSurname[i]),
                                 activeDB);

        }
    }

    int amount = ui->bookAmountSpinBox->value();

    for (int i=0;i<amount;i++){
        query = new QSqlQuery(tr("INSERT INTO bookCatalogueTable "
                                 "(bookUDKCode) VALUES ('%1')")
                                 .arg(ui->UDKCodeLineEdit->text()),
                              activeDB);
    }


    for (int i = 0;i<authorNames.size();i++){

        if(authorNames[i][0]!="" || authorNames[i][1]!=""){

            query = new QSqlQuery(tr("SELECT * FROM authorTable "
                                    "WHERE authorName = '%2' and "
                                    "authorSurname='%1'")
                                    .arg(authorNames[i][0],
                                        authorNames[i][1]),
                                activeDB);

            if(query->size()==0){
                query = new QSqlQuery(tr("INSERT INTO authorTable "
                                        "(authorSurname,authorName) "
                                        "VALUES ('%1','%2')")
                                    .arg(authorNames[i][0],
                                         authorNames[i][1]),
                                    activeDB);
                query = new QSqlQuery(tr("SELECT authorID FROM authorTable "
                                        "WHERE authorName = '%2' and "
                                        "authorSurname='%1'")
                                        .arg(authorNames[i][0],
                                        authorNames[i][1]),
                                        activeDB);
                query->next();
                authorIndexes.push_back(query->value(0).toInt());
                query = new QSqlQuery(tr("INSERT INTO bookConnectTable "
                                        "(authorID,bookUDKCode) VALUES "
                                        "(%1,'%2')")
                                    .arg(QString::number(authorIndexes[i]),
                                        ui->UDKCodeLineEdit->text()),
                                    activeDB);
            }else{
                query->next();
                authorIndexes.push_back(query->value(0).toInt());
            }

        }else{
            qDebug()<<"Ogoog";
            query = new QSqlQuery(tr("SELECT authorID FROM authorTable WHERE "
                                  "authorSurname = '%1' nad authorName = '%2'")
                                  .arg(defaultAuthorSurname[i],defaultAuthorName[i]),
                                  activeDB);
            query->next();
            int authorID = query->value(0).toInt();
            query = new QSqlQuery(tr("DELETE FROM bookConnectTable WHERE "
                                     "authorID = %1").arg(QString::number(authorID)),activeDB);
        }


    }//end for


    this->close();
}

////////////////////////////
void editbookdialog::on_deleteBtn_clicked(){
    int row = ui->tableView->selectionModel()->currentIndex().row();
    QModelIndex primaryKeyIndex = ui->tableView->model()->index(row,0);
    int bookID = ui->tableView->model()->data(primaryKeyIndex).toInt();

    query = new QSqlQuery(tr("DELETE FROM requestTable WHERE "
                             "bookID = %1 and "
                             "(status != 1 or status!=2)")
                          .arg(bookID),
                          activeDB);

    query = new QSqlQuery(tr("DELETE FROM bookCatalogueTable WHERE "
                             "bookID = %1")
                          .arg(bookID),
                          activeDB);
    initTableInfo(1);
    initTableInfo(2);
    initTableInfo(3);
    initTableInfo(4);
    this->close();
}
