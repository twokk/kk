#ifndef APPSPLITTER_H
#define APPSPLITTER_H

#include <QUrl>
#include <QWebView>
#include <QSplitter>
#include "app/bppmarkdown.h"
#include "include/appparam.h"

class AppSplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit AppSplitter(QWidget *parent = 0);

private:
    QWebView* webView;          // 预览窗口
    BppMarkDown* markDown;   // Markdown编辑器

signals:

public slots:

private:
    void initWindowStatus();
    void initComponet();

};

#endif // APPSPLITTER_H
