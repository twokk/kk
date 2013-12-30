#include "appsplitter.h"
#include "QDebug"

AppSplitter::AppSplitter(QWidget *parent) :
    QSplitter(parent)
{
    initFileStatus();
    initWindowStatus();
    initComponet();
}

/**
* 初始化窗口状态
*/
void AppSplitter::initWindowStatus()
{
    // 设置鼠标跟踪
    this->setMouseTracking(true);

    // 设置继承父类背景
    this->setAutoFillBackground(true);

    // 设置允许拖拽
    this->setAcceptDrops(true);
}

/**
* 初始化窗口组件
*/
void AppSplitter::initComponet()
{
    markDown = new BppMarkDown();
    browser = new QWebView();

    this->addWidget(markDown);
    this->addWidget(browser);
    this->setHandleWidth(1);

    // 平分窗口
    QList<int> splitterSizes;
    splitterSizes.append(this->width() / 2);
    splitterSizes.append(this->width() / 2);
    this->setSizes(splitterSizes);

    // 禁止拖拽分隔条
    this->handle(1)->setDisabled(true);

    // 禁止编辑器拖拽
    markDown->setAcceptDrops(false);

    // 禁止浏览器拖拽
    browser->setAcceptDrops(false);

    // 初始化编辑器内容
    markDown->setPlainText("##Welcome!");

    // 初始化浏览器内容
    browser->setHtml(script.markdownToHtml(markDown->toPlainText()));

    // 建立信号槽连接
    connect(markDown, &BppMarkDown::textChanged, this, &AppSplitter::editContentsChangedSlots);
}

/**
* 初始化文件状态
*/
void AppSplitter::initFileStatus()
{
    fileInfo = new FileInfo();

    // 设置文件状态
    fileInfo->setSaved(false);
    fileInfo->setTitled(false);
    fileInfo->setFileTitle(FILE_STATUS_DEFAULT_FILE_TITLE);
    fileInfo->setMarkdownFileName("");
    fileInfo->setMarkdownFileFullName("");
    fileInfo->setHtmlFileFullName("");
    fileInfo->setHtmlFileName("");
    fileInfo->setHtmlText("");
    fileInfo->setMarkdown("");
}

/*******************************************响应设置菜单槽函数***********************************************/
/**
* 打开文件
*/
void AppSplitter::openFileSlots()
{
    QString fileFullName = QFileDialog::getOpenFileName(this, tr(FILE_OPERATE_OPEN_FILE_TITLE), "D:\\", FILE_OPERATE_OPEN_FILE_EXTEND, 0, QFileDialog::DontUseNativeDialog);
    if(!fileFullName.isEmpty() && readFile(fileFullName)) {
        // 更新编辑器
        markDown->setPlainText(fileInfo->getMarkdown());

        // 更新预览
        browser->setHtml(fileInfo->getHtmlText());

        // 激发编辑器内容保存信号
        emit editContentsSavedSignal(fileInfo->getFileTitle());
    }
}

/**
* 保存成HTML
*/
void AppSplitter::saveHtmlSlots()
{
    if(fileInfo->getHtmlFileFullName().isEmpty())
    {
        QString fileFullName = QFileDialog::getSaveFileName(this, tr(FILE_OPERATE_SAVE_TO_HTML_TITLE), ".", FILE_OPERATE_SAVE_TO_HTML_EXTEND, 0, QFileDialog::DontUseNativeDialog);
        // 保存html文件
        writeFile(fileFullName, FILE_STATUS_TYPE_HTML);
    }
    else
    {
        // 保存html文件
        writeFile(fileInfo->getHtmlFileFullName(), FILE_STATUS_TYPE_HTML);
    }
}

/**
* 保存成markdown
*/
void AppSplitter::saveMarkdownSlots()
{
    if(fileInfo->getMarkdownFileFullName().isEmpty())
    {
        QString fileFullName = QFileDialog::getSaveFileName(this, tr(FILE_OPERATE_SAVE_TO_MARKDOAN_TITLE), ".", FILE_OPERATE_SAVE_TO_MARKDOWN_EXTEND, 0, QFileDialog::DontUseNativeDialog);
        // 保存markdown文件
        if(!fileFullName.isEmpty() && writeFile(fileFullName, FILE_STATUS_TYPE_MARKDOWN)) {
            // 激发编辑器内容保存信号
            emit editContentsSavedSignal(fileInfo->getFileTitle());
        }
    }
    else if(writeFile(fileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN))
    {
        // 激发编辑器内容保存信号
        emit editContentsSavedSignal(fileInfo->getFileTitle());
    }
}

/**
* 另存为
*/
void AppSplitter::saveAsSlots()
{
    QString fileFullName = QFileDialog::getSaveFileName(this, tr(FILE_OPERATE_SAVE_AS), ".", FILE_OPERATE_SAVE_AS_EXTEND, 0, QFileDialog::DontUseNativeDialog);
    if(!fileFullName.isEmpty() && writeFile(fileFullName, FILE_STATUS_TYPE_OTHER))
    {
        // 激发编辑器内容保存信号
        emit editContentsSavedSignal(fileInfo->getFileTitle());
    }
}

/**
* 预览模式
*/
void AppSplitter::previewSlots()
{
    markDown->hide();
    browser->show();
}

/**
* 编辑模式
*/
void AppSplitter::editViewSlots()
{
    markDown->show();
    browser->hide();
}

/**
* 双栏模式
*/
void AppSplitter::doubleViewSlots()
{

    markDown->show();
    browser->show();

    // 平分窗口
    QList<int> splitterSizes;
    splitterSizes.append(this->width() / 2);
    splitterSizes.append(this->width() / 2);
    setSizes(splitterSizes);
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
    // 更新文件markdown内容
    this->fileInfo->setMarkdown(markDown->toPlainText());

    // 更新文件htmlText内容
    this->fileInfo->setHtmlText(script.markdownToHtml(markDown->toPlainText()));

    // 更新文件保存状态
    this->fileInfo->setSaved(false);

    // 更新browser内容
    this->browser->setHtml(fileInfo->getHtmlText());

    // 激发编辑器内容发生变化信号
    emit editContentsChangedSignal(fileInfo->getFileTitle());
}

/*******************************************拖拽实现***********************************************/
/**
* 拖动文件事件
*/
void AppSplitter::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
}

/**
* 放下文件事件
*/
void AppSplitter::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();

    if(urls.isEmpty())
    {
        return;
    }

    // 获取拖动文件中的第一个
    QString fileFullName = urls.first().toLocalFile();

    // 读取文件内容
    if(readFile(fileFullName))
    {
        // 设置markdown编辑器内容
        markDown->setPlainText(fileInfo->getMarkdown());
    }
}

/*******************************************拖拽实现***********************************************/

/**
* 读取文件
*/
bool AppSplitter::readFile(QString fileFullName)
{
    if(!fileFullName.isEmpty())
    {
        // 读取文件
        QFile file(fileFullName);

        // 打开文件失败
        if (!file.open(QIODevice::ReadOnly|QIODevice::WriteOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
            return false;
        }

        // 读文件
        QTextStream in(&file);
        QFileInfo info(fileFullName);
        QString text(in.readAll());

        // 更新文件信息
        fileInfo->setFileTitle(info.filePath());
        fileInfo->setMarkdown(text);
        fileInfo->setHtmlText(script.markdownToHtml(text));
        fileInfo->setMarkdownFileName(info.baseName());
        fileInfo->setHtmlFileName("");
        fileInfo->setMarkdownFileFullName(info.filePath());
        fileInfo->setHtmlFileFullName("");
        fileInfo->setSaved(true);
        fileInfo->setTitled(true);

        file.close();

        return true;
    }

    return false;
}

/**
* 写文件
* @fileFullName
* @type 1:markdown,2:html
*/
bool AppSplitter::writeFile(QString fileFullName, int type)
{
    if(!fileFullName.isEmpty()) {
        QFile file(fileFullName);

        // 打开文件失败
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
            return false;
        }

        // 写文件
        QTextStream out(&file);
        // 保存markdown
        if(type == FILE_STATUS_TYPE_MARKDOWN || type == FILE_STATUS_TYPE_OTHER)
        {
            QFileInfo info(fileFullName);
            // 更新文件标题
            fileInfo->setFileTitle(info.filePath());
            // 更新文件名称
            fileInfo->setMarkdownFileName(info.fileName());
            // 更新文件路径
            fileInfo->setMarkdownFileFullName(info.filePath());
            // 更新文件状态
            fileInfo->setSaved(true);
            // 更新文件标题状态
            fileInfo->setTitled(true);

            // 写文件内容到输出流
            out << fileInfo->getMarkdown();

            // 激发编辑器内容保存信号
            emit editContentsSavedSignal(fileInfo->getFileTitle());
        }
        // 保存html
        else if(type == FILE_STATUS_TYPE_HTML)
        {
            // 写文件内容到输出流
            out << fileInfo->getHtmlText();
        }

        out.flush();
        file.close();

        return true;
    }

    return false;
}
