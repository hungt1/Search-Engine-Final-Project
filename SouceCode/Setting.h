#pragma once

#include <QDialog>
#include "ui_Setting.h"

class Setting : public QDialog
{
	Q_OBJECT

public:
	Setting(QWidget *parent = Q_NULLPTR);
	~Setting();
	Ui::Setting ui;

public slots:
	void on_includeTrain_clicked(bool checked);
};
