#include "testproject.h"
#include "./ui_testproject.h"

TestProject::TestProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestProject)
{
    ui->setupUi(this);
}

TestProject::~TestProject()
{
    delete ui;
}


void TestProject::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if (username == "Victor" && password == "1234") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        QPushButton* target = qobject_cast<QPushButton*>(sender());
        target->setStyleSheet(QString("#%1 { background-color: Red; }").arg(target->objectName()));
    }
}


void TestProject::on_logoutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

