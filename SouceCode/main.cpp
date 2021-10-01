#include "Search_Engine_GUI.h"
#include <QtWidgets/QApplication>

wstring discards[1942];
int nStopwords = 1942;
int convert[1 << 16];
wstring stupidChar = L"`~!@#$%^&*()–-_=+[]{}\\|;:'\",<.>/?“”•";
const float eps = 0.01;

SLL curList;
bool includeTrain = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Search_Engine_GUI w;
    w.setWindowTitle("Index Magical Searching");
    w.setWindowIcon(QIcon("icon/icon.png"));
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    w.loadIndex();

    FILE *file = fopen("Crawl\\index.txt", "a");
    fclose(file);

    InitList(curList);
    loadFileMeta(curList);
    prepare();

    w.DestroyWaiting();

    int ret = a.exec();

    SavePath dialogSave;
    dialogSave.ShowSaveDialog();

    eraseList(curList);

    return ret;
}
