#ifndef APPSPLITTER_H
#define APPSPLITTER_H

#include <QUrl>
#include <QTextEdit>
#include <QWebView>
#include <QSplitter>
#include <QMessageBox>
#include "app/bppmarkdown.h"
#include "base/basefileinfo.h"
#include "include/appparam.h"

class AppSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit AppSplitter(QWidget *parent = 0);

private:
    QWebView* webView;          // 预览窗口
    BppMarkDown* markDown;      // Markdown编辑器
    BaseFileInfo* fileInfo;     // 文件信息

signals:
    void editContentsChangedSignal();
    void editContentsSavedSignal();

public slots:
    void openFileSlots();
    void saveHtmlSlots();
    void saveMarkdownSlots();
    void previewSlots();
    void editViewSlots();
    void doubleViewSlots();
    void helpSlots();
    void aboutSlots();
    void feedBackSlots();
    void editContentsChangedSlots();
    void editContentsSavedSlots();

private:
    void initWindowStatus();
    void initComponet();

};

#endif // APPSPLITTER_H
