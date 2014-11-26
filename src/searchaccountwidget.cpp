#include "searchaccountwidget.h"
#include "ui_searchaccountwidget.h"
#include <QDebug>
#include "infobuttondelegate.h"
#include "editaccountdialog.h"

SearchAccountWidget::SearchAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchAccountWidget)
{
    ui->setupUi(this);

    QTimer::singleShot(0, ui->search, SLOT(setFocus()));

    connect(ui->search,SIGNAL(textChanged(QString)),this,SLOT(search_textChanged(QString)));

    activeDB = QSqlDatabase::database("libj");
    model.setQuery("SELECT readerID, readerName, readerSurname, readerTelephone, readerRegDate "
                   "FROM readerTable", activeDB);
    model.setHeaderData(0, Qt::Horizontal, tr("ID"));
    model.setHeaderData(1, Qt::Horizontal, tr("Имя"));
    model.setHeaderData(2, Qt::Horizontal, tr("Фамилия"));
    model.setHeaderData(3, Qt::Horizontal, tr("Телефон"));
    model.setHeaderData(4, Qt::Horizontal, tr("Дата регистрации"));
    ui->tableView->setModel(&model);

    ui->tableView->setColumnWidth(0,39);
    ui->tableView->setColumnWidth(1,112);
    ui->tableView->setColumnWidth(2,172);
    ui->tableView->setColumnWidth(3,70);
    ui->tableView->setColumnWidth(4,115);

  //InfoButtonDelegate *delegate = new InfoButtonDelegate(ui->tableView);
  //ui->tableView->setItemDelegate(delegate);
    ui->radioID->setAccessibleName("readerID");
    ui->radioName->setAccessibleName("readerName");
    ui->radioSurname->setAccessibleName("readerSurname");

}

SearchAccountWidget::~SearchAccountWidget()
{
    delete ui;
}


void SearchAccountWidget::search_textChanged(const QString &text)
{
    QSqlQuery q(activeDB);
    if(!ui->search->text().isEmpty()){
        q.prepare(tr("SELECT readerID, readerName, readerSurname, readerTelephone, readerRegDate "
                     "FROM readerTable WHERE %1 LIKE ? LIMIT 100")
                  .arg(ui->searchRadioGroup->checkedButton()->accessibleName()));
        q.addBindValue(tr("%1\%").arg(text));
        q.exec();
    }
    else q.exec("SELECT readerID, readerName, readerSurname, readerTelephone, readerRegDate "
                "FROM readerTable");
    model.setQuery(q);
}

void SearchAccountWidget::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(this);
    contextMenu.addAction(ui->editRowAction);
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    bool ok = selectionModel->hasSelection();
    ui->editRowAction->setEnabled(ok);
    contextMenu.exec(QCursor::pos());
}

void SearchAccountWidget::on_editRowAction_triggered()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    int row = selectionModel->currentIndex().row();
    QModelIndex primaryKeyIndex = model.index(row, 0);
    int readerID = model.data(primaryKeyIndex).toInt();

    QSqlQuery query(tr("SELECT * FROM readerTable WHERE readerID = %1").arg(readerID), activeDB);
    query.next();
    QSqlRecord rec = query.record();
    EditAccountDialog editDialog(this, rec);
    editDialog.exec();
}

void SearchAccountWidget::on_pushButton_clicked()
{

}
