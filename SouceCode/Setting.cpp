#include "Setting.h"
#include "Search_Engine_GUI.h"

extern bool includeTrain;

Setting::Setting(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.includeTrain->setChecked(true);
	this->setWindowIcon(QIcon("icon/settings"));
	this->setWindowTitle(QString::fromWCharArray(L"Thiết lập"));
}

Setting::~Setting()
{
}

void Setting::on_includeTrain_clicked(bool checked)
{
	if (checked) includeTrain = true; else includeTrain = false;
}