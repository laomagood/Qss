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

    // 使用自定义颜色
    ui->widget->setProperty("CustomColor", 1);
    ui->label->setProperty("CustomColor", 1);
    ui->pushButton->setProperty("CustomColor", 2);

    // 获取所有样式
    QMap<QString, QString> mapSkin = QssHelper::instance()->getAllQssName();
    QStringList strListSkin = mapSkin.keys();
    ui->comboBoxSkin->addItems(strListSkin);

    connect(ui->comboBoxSkin, &QComboBox::currentTextChanged, [](QString t_name) {
        qDebug() << t_name;
        QssHelper::instance()->setSkinStyle(t_name);
    });

    QssHelper::instance()->setSkinStyle(ui->comboBoxSkin->currentText());
}

Form::~Form()
{
    delete ui;
}
