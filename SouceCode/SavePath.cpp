#include "SavePath.h"
#include "Query.h"

extern SLL curList;

SavePath::SavePath(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SavePath::~SavePath()
{
}

void SavePath::ShowSaveDialog()
{
	this->setModal(true);
    this->setWindowIcon(QIcon("icon/save"));
	this->exec();
}

void SavePath::on_yes_clicked()
{
	this->reject();
	updateMetadata(curList);
}

void SavePath::on_no_clicked()
{
	this->reject();

	remove("Crawl\\index.txt");
    FILE* meta = fopen("Crawl\\metadata.txt", "w");
    Node* cur = curList.head;
    while (cur != NULL) {
        string prefix = "";
        for (int i = 0; i < min(6,cur->path.size()); i++) prefix += cur->path[i];
        if (prefix != "train\\") {
            cur = cur->nxt;
            continue;
        }
        fprintf(meta, "%d\n%s\n", cur->nWords, cur->path.c_str());
        for (int i = 0; i < cur->nWords; i++) {
            fprintf(meta, "%f %s\n", cur->listWord[i].weight, cur->listWord[i].word.c_str());
        }
        cur = cur->nxt;
    }
    fprintf(meta, "-1");
    fclose(meta);
}