#include "appsplitter.h"

AppSplitter::AppSplitter(QWidget *parent) :
    QSplitter(parent)
{
    initWindowStatus();
    initComponet();
}

/**
* 初始化窗口状态
*/
void AppSplitter::initWindowStatus()
{
    this->setMouseTracking(true);

    this->setAutoFillBackground(true);

    this->setAutoFillBackground(true);

    this->setStyleSheet(APP_WINDOW_BACKGROUND_TRANSPARENT);
}

/**
* 初始化窗口组件
*/
void AppSplitter::initComponet()
{
    markDown = new BppMarkDown();
    webView = new QWebView();

    webView->load(QUrl("http://www.qq.com"));

    this->addWidget(markDown);
    this->addWidget(webView);

    // 平分窗口
    QList<int> splitterSizes;
    splitterSizes.append(this->width() / 2);
    splitterSizes.append(this->width() / 2);
    this->setSizes(splitterSizes);
}
