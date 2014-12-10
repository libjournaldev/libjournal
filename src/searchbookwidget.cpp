#include "searchbookwidget.h"
#include "ui_searchbookwidget.h"
#include "editbookdialog.h"
#include <QString>

SearchBookWidget::SearchBookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchBookWidget)
{
    ui->setupUi(this);
    QTimer::singleShot(0, ui->search, SLOT(setFocus()));
    connect(ui->search,SIGNAL(textChanged(QString)),this,SLOT(search_textChanged(QString)));
    activeDB = QSqlDatabase::database("libj");
    query = new QSqlQuery("DELETE FROM bookInfoTable WHERE bookUDKCode NOT IN "
                          "(SELECT bookUDKCode FROM bookCatalogueTable GROUP BY bookUDKCode)",
                          activeDB);

    model.setQuery("SELECT bookConnectTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),"
                   "categoryName "
                   "FROM bookConnectTable,bookInfoTable,bookCategoryTable,authorTable "
                   "WHERE (authorTable.authorID = bookConnectTable.authorId) and "
                   "(bookInfoTable.bookUDKCode = bookConnectTable.bookUDKCode) and "
                   "(bookCategoryTable.categoryID = bookInfoTable.categoryID) "
                   "GROUP BY bookConnectTable.bookUDKCode "
                   "ORDER BY bookName LIMIT 200 "
                   ,activeDB);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    model.setHeaderData(0, Qt::Horizontal, tr("УДК Код"));
    model.setHeaderData(1, Qt::Horizontal, tr("Название книги"));
    model.setHeaderData(2, Qt::Horizontal, tr("Автор(ы)"));
    model.setHeaderData(3, Qt::Horizontal, tr("Категория"));
    model.query().exec();
    ui->tableView->setModel(&model);
    ui->tableView->setColumnWidth(0,120);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,230);

    ui->radioBookId->setAccessibleName("bookId");
    ui->radioAuthorSurname->setAccessibleName("authorSurname");
    ui->radioUDKCode->setAccessibleName("bookUDKCode");
    ui->radioBookName->setAccessibleName("bookName");

    refreshStatistic();

}

SearchBookWidget::~SearchBookWidget()
{
    delete ui;
}

void SearchBookWidget::search_textChanged(const QString &text)
{
    QSqlQuery q(activeDB);
    if(!ui->search->text().isEmpty()){
        if(ui->groupBox->checkedButton()->accessibleName()=="bookUDKCode"){
            query = new QSqlQuery("DELETE FROM bookInfoTable WHERE bookUDKCode NOT IN "
                                  "(SELECT bookUDKCode FROM bookCatalogueTable GROUP BY bookUDKCode)",
                                  activeDB);
            q.prepare(tr("SELECT bookConnectTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),"
                     "categoryName FROM bookConnectTable,bookInfoTable,bookCategoryTable,authorTable "
                     "WHERE (authorTable.authorID = bookConnectTable.authorId) and "
                     "(bookInfoTable.bookUDKCode = bookConnectTable.bookUDKCode) and "
                     "(bookCategoryTable.categoryID = bookInfoTable.categoryID) and "
                     "bookInfoTable.bookUDKCode like ? "
                     "GROUP BY bookConnectTable.bookUDKCode "));
            q.addBindValue(tr("%1\%").arg(text));
            q.exec();
        }

        if(ui->groupBox->checkedButton()->accessibleName()=="bookId"){
           query = new QSqlQuery("DELETE FROM bookInfoTable WHERE bookUDKCode NOT IN "
                                  "(SELECT bookUDKCode FROM bookCatalogueTable GROUP BY bookUDKCode)",
                                  activeDB);
           q.prepare(tr("SELECT bookCatalogueTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),categoryName "
                         "FROM bookInfoTable,authorTable,bookCategoryTable,bookConnectTable,bookCatalogueTable "
                         "WHERE (bookCatalogueTable.bookID = :id) and "
                         "(bookInfoTable.bookUDKCode = bookCatalogueTable.bookUDKCode) and "
                         "(authorTable.authorID = bookConnectTable.authorId) and "
                         "(bookInfoTable.bookUDKCode = bookConnectTable.bookUDKCode) and "
                         "(bookCategoryTable.categoryID = bookInfoTable.categoryID) "
                         "GROUP BY bookConnectTable.bookUDKCode"));
            q.bindValue(":id",ui->search->text().toInt());
            q.exec();
         }

        if(ui->groupBox->checkedButton()->accessibleName()=="authorSurname"){
           query = new QSqlQuery("DELETE FROM bookInfoTable WHERE bookUDKCode NOT IN "
                                  "(SELECT bookUDKCode FROM bookCatalogueTable GROUP BY bookUDKCode)",
                                  activeDB);
           q.prepare(tr("SELECT bookConnectTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),categoryName "
                         "FROM bookInfoTable,authorTable,bookCategoryTable,bookConnectTable "
                         "WHERE (INSTR(authorTable.authorSurname,:id)=1) and "
                         "(bookInfoTable.bookUDKCode = bookConnectTable.bookUDKCode) and "
                         "(bookConnectTable.authorID = authorTable.authorId) and "
                         "(bookCategoryTable.categoryID = bookInfoTable.categoryID) "
                         "GROUP BY bookConnectTable.bookUDKCode"));
            q.bindValue(":id",ui->search->text());
            q.exec();
         }

        if(ui->groupBox->checkedButton()->accessibleName()=="bookName"){
            query = new QSqlQuery("DELETE FROM bookInfoTable WHERE bookUDKCode NOT IN "
                                  "(SELECT bookUDKCode FROM bookCatalogueTable GROUP BY bookUDKCode)",
                                  activeDB);
            q.prepare(tr("SELECT bookInfoTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),"
                     "categoryName FROM bookInfoTable,bookConnectTable,authorTable,bookCategoryTable "
                     "WHERE (instr(bookInfoTable.bookName,:id)=1) and "
                     "(bookConnectTable.bookUDKCode = bookInfoTable.bookUDKCode) and "
                     "(authorTable.authorID = bookConnectTable.authorID) and "
                     "(bookCategoryTable.categoryID = bookInfoTable.categoryID) "
                     "GROUP BY bookConnectTable.bookUDKCode "));
            q.bindValue(":id",ui->search->text());
            q.exec();
         }

        model.setQuery(q);
    }
    else{
        query = new QSqlQuery("DELETE FROM bookInfoTable WHERE bookUDKCode NOT IN "
                              "(SELECT bookUDKCode FROM bookCatalogueTable GROUP BY bookUDKCode)",
                              activeDB);
        q.prepare("SELECT bookConnectTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),"
                  "categoryName FROM bookConnectTable,bookInfoTable,bookCategoryTable,authorTable "
                  "WHERE (authorTable.authorID = bookConnectTable.authorId) and "
                  "(bookInfoTable.bookUDKCode = bookConnectTable.bookUDKCode) and "
                  "(bookCategoryTable.categoryID = bookInfoTable.categoryID) "
                  "GROUP BY bookConnectTable.bookUDKCode LIMIT 200");
        q.exec();
        model.setQuery(q);
    }
}

void SearchBookWidget::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(this);
    contextMenu.addAction(ui->editRowAction);
    contextMenu.addAction(ui->actionOrderRowAction);
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    bool ok = selectionModel->hasSelection();
    ui->editRowAction->setEnabled(ok);
    ui->actionOrderRowAction->setEnabled(ok);
    contextMenu.exec(QCursor::pos());
}

void SearchBookWidget::on_editRowAction_triggered()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    int row = selectionModel->currentIndex().row();
    QModelIndex primaryKeyIndex = model.index(row, 0);
    QString bookUDKCode = model.data(primaryKeyIndex).toString();

    qDebug()<<bookUDKCode;
    QSqlQuery query(tr("SELECT bookConnectTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),"
                          "categoryName FROM bookConnectTable,bookInfoTable,bookCategoryTable,authorTable "
                          "WHERE (bookInfoTable.bookUDKCode = '%1') and "
                          "(authorTable.authorID = bookConnectTable.authorId) and "
                          "(bookConnectTable.bookUDKCode = bookInfoTable.bookUDKCode) and "
                          "(bookCategoryTable.categoryID = bookInfoTable.categoryID) "
                          "GROUP BY bookConnectTable.bookUDKCode ").arg(bookUDKCode), activeDB);

    qDebug()<<query.size();
    query.next();

    QSqlRecord rec = query.record();
    qDebug()<<rec.value("bookUDKCode").toString();

    editbookdialog editDialog(&rec,this);

    editDialog.exec();
    refreshStatistic();
    model.query().exec();
}

void SearchBookWidget::on_addNewBookButton_clicked()
{
    editbookdialog addDialog(this);
    addDialog.exec();
    refreshStatistic();
    query = new QSqlQuery("DELETE FROM bookInfoTable WHERE bookUDKCode NOT IN "
                          "(SELECT bookUDKCode FROM bookCatalogueTable GROUP BY bookUDKCode)",
                          activeDB);
    model.query().exec();
}

void SearchBookWidget::on_actionOrderRowAction_triggered()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    int row = selectionModel->currentIndex().row();
    QModelIndex primaryKeyIndex = model.index(row, 0);
    QString bookUDKCode = model.data(primaryKeyIndex).toString();

    QSqlQuery query(tr("SELECT bookConnectTable.bookUDKCode,bookName,GROUP_CONCAT(authorSurname),"
                          "categoryName FROM bookConnectTable,bookInfoTable,bookCategoryTable,authorTable "
                          "WHERE (bookInfoTable.bookUDKCode = '%1') and "
                          "(authorTable.authorID = bookConnectTable.authorId) and "
                          "(bookConnectTable.bookUDKCode = bookInfoTable.bookUDKCode) and "
                          "(bookCategoryTable.categoryID = bookInfoTable.categoryID) "
                          "GROUP BY bookConnectTable.bookUDKCode ").arg(bookUDKCode), activeDB);

    query.next();

    QSqlRecord rec = query.record();

    orderBookDialog orderDialog(&rec,this);

    orderDialog.exec();
    model.query().exec();
    refreshStatistic();
}


void SearchBookWidget::refreshStatistic(){
    query = new QSqlQuery("SELECT COUNT(bookID) FROM bookCatalogueTable",activeDB);
    query->next();
    ui->labelBookAmount->setText(query->record().value(0).toString());
    query = new QSqlQuery("SELECT COUNT(bookID) FROM requestTable WHERE status='на руках'",activeDB);
    query->next();
    ui->labelOnHandBook->setText(query->record().value(0).toString());
    double i = ui->labelOnHandBook->text().toDouble();
    double j = ui->labelBookAmount->text().toDouble();
    i/=j;
    i*=100;
    ui->labelPercentage->setText(QString::number(i) + "%");

}

void SearchBookWidget::on_SearchBookWidget_destroyed()
{
    model.query().exec();
    refreshStatistic();
}
