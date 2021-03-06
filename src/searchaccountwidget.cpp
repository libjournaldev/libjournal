#include "searchaccountwidget.h"
#include "ui_searchaccountwidget.h"
#include <QDebug>
#include <QTextDocument>
#include <QPrinter>
#include <QtPrintSupport/QPrinter>
#include "editaccountdialog.h"
#include "accounthistory.h"

SearchAccountWidget::SearchAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchAccountWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/accounts.png"));
    connect(ui->addAccountButton,SIGNAL(clicked()),this,SLOT(addAccount()));
    connect(ui->search,SIGNAL(textChanged(QString)),this,SLOT(search_textChanged(QString)));

    activeDB = QSqlDatabase::database("libj");
    refresh();
    ui->tableView->setModel(&model);

    ui->tableView->setColumnWidth(0,39);
    ui->tableView->setColumnWidth(1,112);
    ui->tableView->setColumnWidth(2,172);
    ui->tableView->setColumnWidth(3,70);
    ui->tableView->setColumnWidth(4,115);

    ui->radioID->setAccessibleName("readerID");
    ui->radioName->setAccessibleName("readerName");
    ui->radioSurname->setAccessibleName("readerSurname");
    connect(ui->searchRadioGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(refresh(QAbstractButton*)));
}

SearchAccountWidget::~SearchAccountWidget()
{
    delete ui;
}

void SearchAccountWidget::refresh(QAbstractButton *radio)
{
    QSqlQuery q(activeDB);
    QString searchStr = ui->search->text();
    if(radio && !searchStr.isEmpty()){
        q.prepare(tr("SELECT readerID, readerName, readerSurname, readerTelephone, readerRegDate "
                     "FROM readerTable WHERE %1 LIKE ? LIMIT 100")
                  .arg(radio->accessibleName()));
        q.addBindValue(tr("%1\%").arg(searchStr));
        q.exec();
        model.setQuery(q);
    }
    else{
        model.setQuery("SELECT readerID, readerName, readerSurname, readerTelephone, readerRegDate "
                       "FROM readerTable", activeDB);
        model.setHeaderData(0, Qt::Horizontal, tr("ID"));
        model.setHeaderData(1, Qt::Horizontal, tr("Имя"));
        model.setHeaderData(2, Qt::Horizontal, tr("Фамилия"));
        model.setHeaderData(3, Qt::Horizontal, tr("Телефон"));
        model.setHeaderData(4, Qt::Horizontal, tr("Дата регистрации"));
        model.query().exec();
    }
}

void SearchAccountWidget::search_textChanged(const QString &text)
{
    QSqlQuery q(activeDB);
    if(!text.isEmpty()){
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
    contextMenu.addAction(ui->openHistory);
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    bool ok = selectionModel->hasSelection();
    ui->editRowAction->setEnabled(ok);
    ui->openHistory->setEnabled(ok);
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
    EditAccountDialog d(this, rec);
    if(d.exec() == QDialog::Accepted){
        QString updateQueryStr = QString("UPDATE readerTable SET readerSurname = '%1',"
                                         "readerName = '%2',"
                                         "readerMiddleName = '%3',"
                                         "readerAdress='%4',"
                                         "readerTelephone = '%5',"
                                         "readerDepartmentID = %6 "
                                         "WHERE readerID = %7")
                .arg(d.readerSurname())
                .arg(d.readerName())
                .arg(d.readerMiddleName())
                .arg(d.readerAdress())
                .arg(d.readerTelephone())
                .arg(d.readerDepartment())
                .arg(readerID);
        if(!query.exec(updateQueryStr)){
            QMessageBox::warning(this,tr("Ошибка базы данных"),tr("Не удалось отредактировать "
                                                                 "карту: ") + query.lastError().text());
            return;
        }
    }
    else if(d.result() == -1){
        QString updateQueryStr = QString("DELETE FROM readertable WHERE readerID = %1").arg(readerID);
        if(!query.exec(updateQueryStr)){
            QMessageBox::warning(this,tr("Ошибка базы данных"),tr("Не удалось удалить "
                                                                 "карту: ") + query.lastError().text());
            return;
        }
        ui->search->clear();
        refresh();
    }
    model.query().exec();
}

void SearchAccountWidget::on_openHistory_triggered()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    int row = selectionModel->currentIndex().row();
    QModelIndex primaryKeyIndex = model.index(row, 0);
    int readerID = model.data(primaryKeyIndex).toInt();

    AccountHistory wind(readerID, this);
    wind.exec();
}

void SearchAccountWidget::addAccount()
{
    EditAccountDialog d(this);
    QSqlQuery query(activeDB);
    if(d.exec() != QDialog::Accepted)
       return;
    QString updateQueryStr = QString("INSERT INTO readerTable (readerSurname,"
                                     "readerName,readerMiddleName,readerAdress,"
                                     "readerTelephone,readerBirthDate,readerRegDate,"
                                     "readerDepartmentID) VALUES "
                                     "('%1','%2','%3','%4','%5','%6','%7',%8)")
            .arg(d.readerSurname())
            .arg(d.readerName())
            .arg(d.readerMiddleName())
            .arg(d.readerAdress())
            .arg(d.readerTelephone())
            .arg(d.readerBirthDate())
            .arg(d.readerRegDate())
            .arg(d.readerDepartment());
    if(!query.exec(updateQueryStr)){
        QMessageBox::warning(this,tr("Ошибка базы данных"),tr("Не удалось добавить "
                                                             "карту: ") + query.lastError().text());
    }
    else{
        ui->search->clear();
        refresh();

        QTextDocument card;
        QString initialFile = ":/card_template.html";

        if (!QFile::exists(initialFile))
            return;
        QFile file(initialFile);
        if (!file.open(QFile::ReadOnly))
            return;

        QByteArray data = file.readAll();
        QTextCodec *codec = Qt::codecForHtml(data);
        QString str = codec->toUnicode(data);

        query.exec(tr("SELECT departmentShortName "
                      "FROM departmentTable "
                      "WHERE departmentID = %1").arg(d.readerDepartment()));
        query.next();
        QString depShortName = query.record().value(0).toString();
        query.exec("SELECT MAX(readerID) FROM readerTable");
        query.next();
        int readerID = query.record().value(0).toInt();

        str.replace("%surname%",d.readerSurname());
        str.replace("%name",d.readerName());
        str.replace("%middlename%",d.readerMiddleName());
        str.replace("%department%",depShortName);
        str.replace("%readerid%",tr("Билет №%1").arg(readerID));

        if (Qt::mightBeRichText(str))
            card.setHtml(str);
        QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                        QString(), "*.pdf");
        if (!fileName.isEmpty()) {
            if (QFileInfo(fileName).suffix().isEmpty())
                fileName.append(".pdf");
            QPrinter printer(QPrinter::ScreenResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOrientation(QPrinter::Landscape);
            printer.setPaperSize(QPrinter::A7);
            printer.setOutputFileName(fileName);

            QSizeF paperSize;
            paperSize.setWidth(printer.width());
            paperSize.setHeight(printer.height());
            card.setPageSize(paperSize);

            card.print(&printer);
        }
    }
}
