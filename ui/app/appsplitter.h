#ifndef APPSPLITTER_H
#define APPSPLITTER_H

#include <QUrl>
#include <QList>
#include <QFileInfo>
#include <QMimeData>
#include <QTextStream>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWebKitWidgets/QWebView>
#include "../app/bppmarkdown.h"
#include "../model/fileinfo.h"
#include "../include/appparam.h"
#include "../include/transnames.h"
#include "../script/appscript.h"

class AppSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit AppSplitter(QWidget *parent = 0);

private:
    QWebView* browser;       // 预览窗口
    BppMarkDown* markDown;   // Markdown编辑器
    FileInfo* fileInfo;      // 文件信息
    AppScript script;        // 解析markdown

signals:
    void editContentsChangedSignal(QString);    // 编辑器内容发生变化，参数为文件title
    void editContentsSavedSignal(QString);      // 编辑器内容保存信号，参数为文件title

public slots:
    void openFileSlots();
    void saveHtmlSlots();
    void saveAsSlots();
    void saveMarkdownSlots();
    void previewSlots();
    void editViewSlots();
    void doubleViewSlots();
    void helpSlots();
    void aboutSlots();
    void feedBackSlots();
    void editContentsChangedSlots();

private:
    void initWindowStatus();
    void initComponet();
    void initFileStatus();
    bool readFile(QString);
    bool writeFile(QString, int);

protected:
    void dragEnterEvent(QDragEnterEvent*);
    void dropEvent(QDropEvent*);

};

#endif // APPSPLITTER_H
