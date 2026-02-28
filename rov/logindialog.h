#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(QWidget *parent = nullptr);
    ~LogInDialog();

signals:
    void showmain();

private slots:
    void on_btn_log_clicked();

    void on_btn_clear_clicked(bool checked);

private:
    Ui::LogInDialog *ui;
};

#endif // LOGINDIALOG_H
