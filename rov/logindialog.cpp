#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
LogInDialog::LogInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog)
{
    ui->setupUi(this);
    this->setFixedSize(795, 564);

    ui->edit_name->setText("hit_rover");
    ui->edit_pw->setText("123");

    QPixmap pixmap = QPixmap(":/pictures/7CAA45F18C7A68430A750C0F6147A263.jpg").scaled(this->size());
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    setPalette(palette);
}

LogInDialog::~LogInDialog()
{
    delete ui;
}

void LogInDialog::on_btn_log_clicked()
{
    if((ui->edit_name->text() == "hit_rover") && (ui->edit_pw->text() == "123")){
        this->hide();
        emit showmain();
    }

    else if((ui->edit_name->text() == "") || (ui->edit_name->text() == "")){
        QMessageBox::warning(this, tr("提示"), tr("用户名或密码不能为空"), QMessageBox::Yes);
        ui->edit_name->clear();
        ui->edit_name->setFocus();
    }

    else if(ui->edit_name->text() != "hit_rover"){
        QMessageBox::warning(this, tr("提示"), tr("用户名不存在，请重新输入"), QMessageBox::Yes);
        ui->edit_name->clear();
        ui->edit_name->setFocus();
    }

    else if((ui->edit_name->text() == "hit_rover") && (ui->edit_pw->text()!= "888888")){
        QMessageBox::warning(this, tr("提示"), tr("用户名密码不匹配，请重新输入"), QMessageBox::Yes);
        ui->edit_name->setFocus();
    }
}

void LogInDialog::on_btn_clear_clicked(bool checked)
{
    this->close();
}

