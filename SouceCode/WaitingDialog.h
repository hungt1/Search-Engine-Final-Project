#pragma once

#include <QDialog>
#include "ui_WaitingDialog.h"

class WaitingDialog : public QDialog
{
	Q_OBJECT

public:
	WaitingDialog(QWidget *parent = Q_NULLPTR);
	~WaitingDialog();
	Ui::WaitingDialog ui;
};
