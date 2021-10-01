#pragma once

#include <QDialog>
#include "ui_SavePath.h"

class SavePath : public QDialog
{
	Q_OBJECT

public:
	Ui::SavePath ui;
	SavePath(QWidget *parent = Q_NULLPTR);
	~SavePath();
	void ShowSaveDialog();

public slots:
	void on_yes_clicked();
	void on_no_clicked();
	

//private:
	
};
