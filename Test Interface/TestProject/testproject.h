#ifndef TESTPROJECT_H
#define TESTPROJECT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TestProject; }
QT_END_NAMESPACE

class TestProject : public QMainWindow
{
    Q_OBJECT

public:
    TestProject(QWidget *parent = nullptr);
    ~TestProject();

private slots:
    void on_loginButton_clicked();

    void on_logoutButton_clicked();

private:
    Ui::TestProject *ui;
};
#endif // TESTPROJECT_H
