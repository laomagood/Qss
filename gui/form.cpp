#include "form.h"
#include "ui_form.h"
#include "util/QssHelper.h"
#include <QDebug>


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    this->setProperty("form", true);

    ui->widget->setProperty("CustomColor", 1);
    ui->label->setProperty("CustomColor", 1);

    QStringList strListSkin = QssHelper::instance()->getAllQssName();
    ui->comboBoxSkin->addItems(strListSkin);

    connect(ui->comboBoxSkin, &QComboBox::currentTextChanged, [](QString t_name) {
        qDebug() << t_name;
        QssHelper::instance()->setSkinStyle(t_name);
    });
}

Form::~Form()
{
    delete ui;
}
