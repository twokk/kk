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

    //this->setStyleSheet(APP_WINDOW_BACKGROUND_TRANSPARENT);
}

/**
* 初始化窗口组件
*/
void AppSplitter::initComponet()
{
    markDown = new BppMarkDown();
    webView = new QWebView();
    fileInfo = new BaseFileInfo();

    webView->setHtml("<h3>你好,欢迎使用markplus.</h3><hr/>感觉很不错的样子");

    this->addWidget(markDown);
    this->addWidget(webView);
    this->setHandleWidth(1);

    fileInfo->setFileStatus(false);
    fileInfo->setFileName("undefine");
    fileInfo->setFilePath("");
    fileInfo->setHtmlText("");
    fileInfo->setMarkdown("");

    // 平分窗口
    QList<int> splitterSizes;
    splitterSizes.append(this->width() / 2);
    splitterSizes.append(this->width() / 2);
    this->setSizes(splitterSizes);

    // 建立信号槽连接
    connect(markDown, &BppMarkDown::textChanged, this, &AppSplitter::editContentsChangedSlots);
}

/*******************************************响应设置菜单槽函数***********************************************/
/**
* 打开文件
*/
void AppSplitter::openFileSlots()
{
    QMessageBox::information(NULL, "Open File", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 保存成HTML
*/
void AppSplitter::saveHtmlSlots()
{
    QMessageBox::information(NULL, "Save To Html", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 保存成markdown
*/
void AppSplitter::saveMarkdownSlots()
{
    QMessageBox::information(NULL, "Save To MarkDown", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 预览模式
*/
void AppSplitter::previewSlots()
{
    QMessageBox::information(NULL, "Preview View", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 编辑模式
*/
void AppSplitter::editViewSlots()
{
    QMessageBox::information(NULL, "Edit View", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 双栏模式
*/
void AppSplitter::doubleViewSlots()
{
    QMessageBox::information(NULL, "Double View", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 帮助
*/
void AppSplitter::helpSlots()
{
    QMessageBox::information(NULL, "Help", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 关于对话框
*/
void AppSplitter::aboutSlots()
{
    QMessageBox::information(NULL, "About", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/**
* 反馈
*/
void AppSplitter::feedBackSlots()
{
    QMessageBox::information(NULL, "Feed Back", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
/*******************************************响应设置菜单槽函数***********************************************/

/**
* 编辑器内容发生变化
*/
void AppSplitter::editContentsChangedSlots()
{
    this->fileInfo->setMarkdown(markDown->toPlainText());
    this->fileInfo->setHtmlText(markDown->toPlainText());

    this->webView->setHtml(fileInfo->getHtmlText());

    this->fileInfo->setFileStatus(1);

    // 激发编辑器内容发生变化信号
    emit editContentsChangedSignal();
}

/**
* 编辑器内容保存
*/
void AppSplitter::editContentsSavedSlots()
{
    // 文件状态
    this->fileInfo->setFileStatus(2);

    // 激发编辑器内容发生变化信号
    emit editContentsSavedSignal();
}
