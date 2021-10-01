#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileSystemModel>
#include <QTextStream>
#include <QFile>
#include <QTreeView>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QThread>
#include "ui_Search_Engine_GUI.h"
#include "Setting.h"
#include "WarningDialog.h"
#include "WaitingDialog.h"
#include "SavePath.h"
#include "lib.h"
#include "PreprocessFIle.h"
#include "SLL.h"
#include "Query.h"
#include "TextNormalizationOperators.h"

class Search_Engine_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Search_Engine_GUI(QWidget *parent = Q_NULLPTR);
    void DestroyWaiting();
    void Searching(QString searchText);
    void ShowResult(double time, bool includeTrain);
    void loadIndex();

private slots:
    void on_treeView_doubleClicked(const QModelIndex& index);
    void on_LoadDir_clicked();
    void on_listView_doubleClicked(const QModelIndex& index);
    void on_listView_2_doubleClicked(const QModelIndex& index);
    void on_tableWidget_cellDoubleClicked(int r, int c);
    void on_LoadFile_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_DelFile_clicked();
    void on_AddFile_clicked();
    void displayFiles(const QString& mPath);
    void addResult(QString name, QString score, int cnt);
    void on_searchBox_returnPressed();
    void on_searchButton_clicked();
    void on_setting_clicked();
    void ShowWarning();
    void ShowWaiting(QString info, QString label, QIcon icon);

private:
    Ui::Search_Engine_GUIClass ui;

    Setting setting;
    WaitingDialog *waiting;
    QFileSystemModel* dirModel;
    QStringListModel* listFileQueryModel, * listFileModel;
    QStringList listFileQuery;
    QString pathCur;
    int tabChose = 0;
    int numFileQuery = 0;
};

class CustomTableWidgetItem : public QTableWidgetItem
{
public:
    CustomTableWidgetItem(const QString txt = QString('0'))
        :QTableWidgetItem(txt)
    {
    }

    bool operator <(const QTableWidgetItem& other) const
    {
        return text().toFloat() < other.text().toFloat();
    }
};