#ifndef APPSPLITTER_H
#define APPSPLITTER_H

#include <QUrl>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QSplitter>
#include <QFileInfo>
#include <QTextStream>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWebKitWidgets/QWebView>
#include "../app/bppmarkdown.h"
#include "../model/fileinfo.h"
#include "../util/apputil.h"
#include "../include/appparam.h"
#include "../include/transnames.h"

class AppSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit AppSplitter(QWidget *parent = 0);

private:
    QWebView* browser;       // 预览窗口
    BppMarkDown* markDown;      // Markdown编辑器
    FileInfo* fileInfo;     // 文件信息

signals:
    void editContentsChangedSignal(QString);
    void editContentsSavedSignal(QString);

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

};

#endif // APPSPLITTER_H
