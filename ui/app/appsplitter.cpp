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
    browser = new QWebView();

    browser->setHtml("<h3>你好,欢迎使用markplus.</h3><hr/>感觉很不错的样子");

    this->addWidget(markDown);
    this->addWidget(browser);
    this->setHandleWidth(1);

    // 平分窗口
    QList<int> splitterSizes;
    splitterSizes.append(this->width() / 2);
    splitterSizes.append(this->width() / 2);
    this->setSizes(splitterSizes);

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
    fileInfo->setMarkdownFilePath("");
    fileInfo->setHtmlFilePath("");
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
    QString filePath = QFileDialog::getOpenFileName(this, tr(FILE_OPERATE_OPEN_FILE_TITLE), ".", FILE_OPERATE_OPEN_FILE_EXTEND);
    if(!filePath.isEmpty()) {
        //方式：Append为追加，WriteOnly，ReadOnly
        QFile file(filePath);

        // 打开文件失败
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
            return;
        }

        QFileInfo info(filePath);
        // 更新文件状态
        fileInfo->setSaved(true);
        // 更新文件标题状态
        fileInfo->setTitled(true);
        // 更新文件标题
        fileInfo->setFileTitle(info.baseName());
        // 更新文件名称
        fileInfo->setHtmlFileName(info.fileName());
        // 更新文件路径
        fileInfo->setHtmlFilePath(info.absoluteFilePath());

        // 读文件
        QTextStream in(&file);;
        QString text(in.readAll());
        fileInfo->setMarkdown(text);
        fileInfo->setHtmlText(text);
        file.close();

        qDebug() << "bbb" << fileInfo->getMarkdown();

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
    // 如果文件为空，则新保存文件，否则，直接保存文件内容
    if(fileInfo->getHtmlFilePath().isEmpty())
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr(FILE_OPERATE_SAVE_TO_HTML_TITLE), ".", FILE_OPERATE_SAVE_TO_HTML_EXTEND);
        if(!filePath.isEmpty()) {
            // 追加文件后缀
            if(!filePath.endsWith(FILE_STATUS_MARKDOWN_EXTENSION_HTM) && !filePath.endsWith(FILE_STATUS_MARKDOWN_EXTENSION_HTML))
            {
                filePath.append(".").append(FILE_STATUS_MARKDOWN_EXTENSION_HTML);
            }

            //方式：Append为追加，WriteOnly，ReadOnly
            QFile file(filePath);

            // 打开文件失败
            if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
                QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
                return;
            }

            QFileInfo info(filePath);
            // 更新文件状态
            fileInfo->setSaved(true);
            // 更新文件标题状态
            fileInfo->setTitled(true);
            // 更新文件标题
            fileInfo->setFileTitle(info.baseName());
            // 更新文件名称
            fileInfo->setHtmlFileName(info.fileName());
            // 更新文件路径
            fileInfo->setHtmlFilePath(info.absoluteFilePath());

            // 写文件
            QTextStream out(&file);;
            out << fileInfo->getHtmlText();
            out.flush();
            file.close();

            // 激发编辑器内容保存信号
            emit editContentsSavedSignal(fileInfo->getFileTitle());
        }
    }
    else
    {
        // 获取文件
        QFile file(fileInfo->getHtmlFilePath());

        // 打开文件失败
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
            return;
        }
        // 写文件
        QTextStream out(&file);;
        out << fileInfo->getHtmlText();
        out.flush();
        file.close();

        // 激发编辑器内容保存信号
        emit editContentsSavedSignal(fileInfo->getFileTitle());
    }
}

/**
* 保存成markdown
*/
void AppSplitter::saveMarkdownSlots()
{
    if(fileInfo->getMarkdownFilePath().isEmpty())
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr(FILE_OPERATE_SAVE_TO_MARKDOAN_TITLE), ".", FILE_OPERATE_SAVE_AS_EXTEND);
        if(!filePath.isEmpty()) {
            // 追加文件后缀
            if(!filePath.endsWith(FILE_STATUS_MARKDOWN_EXTENSION_MD) && !filePath.endsWith(FILE_STATUS_MARKDOWN_EXTENSION_MARKDOWN))
            {
                filePath.append(".").append(FILE_STATUS_MARKDOWN_EXTENSION_MD);
            }

            //方式：Append为追加，WriteOnly，ReadOnly
            QFile file(filePath);

            // 打开文件失败
            if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
                QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
                return;
            }

            QFileInfo info(filePath);
            // 更新文件状态
            fileInfo->setSaved(true);
            // 更新文件标题状态
            fileInfo->setTitled(true);
            // 更新文件标题
            fileInfo->setFileTitle(info.baseName());
            // 更新文件名称
            fileInfo->setMarkdownFileName(info.fileName());
            // 更新文件路径
            fileInfo->setMarkdownFilePath(info.absoluteFilePath());

            // 写文件
            QTextStream out(&file);;
            out << fileInfo->getMarkdown();
            out.flush();
            file.close();

            // 激发编辑器内容保存信号
            emit editContentsSavedSignal(fileInfo->getFileTitle());
        }
    }
    else
    {
        // 获取文件
        QFile file(fileInfo->getMarkdownFilePath());
        qDebug() << fileInfo->getMarkdownFilePath();
        qDebug() << fileInfo->getMarkdownFileName();
        qDebug() << fileInfo->getFileTitle();

        // 打开文件失败
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
            return;
        }

        // 写文件
        QTextStream out(&file);;
        out << fileInfo->getHtmlText();
        out.flush();
        file.close();

        // 激发编辑器内容保存信号
        emit editContentsSavedSignal(fileInfo->getFileTitle());
    }
}

/**
* 另存为
*/
void AppSplitter::saveAsSlots()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr(FILE_OPERATE_SAVE_AS), ".", FILE_OPERATE_SAVE_AS_EXTEND);
    if(!filePath.isEmpty()) {

        //方式：Append为追加，WriteOnly，ReadOnly
        QFile file(filePath);

        // 打开文件失败
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, tr(FILE_OPERATE_SHOW_NOTE), tr(FILE_OPERATE_CAN_NOT_CREATE_FILE));
            return;
        }

        QFileInfo info(filePath);
        // 更新文件状态
        fileInfo->setSaved(true);
        // 更新文件标题状态
        fileInfo->setTitled(true);
        // 更新文件标题
        fileInfo->setFileTitle(info.baseName());
        // 更新文件名称
        fileInfo->setMarkdownFileName(info.fileName());
        // 更新文件路径
        fileInfo->setMarkdownFilePath(info.absoluteFilePath());

        // 写文件
        QTextStream out(&file);;
        out << fileInfo->getMarkdown();
        out.flush();
        file.close();

        // 激发编辑器内容保存信号
        emit editContentsSavedSignal(fileInfo->getFileTitle());
    }
}

/**
* 预览模式
*/
void AppSplitter::previewSlots()
{
    if(!markDown->isHidden())
    {
        markDown->hide();
    }

    if(browser->isHidden())
    {
        browser->show();
    }
}

/**
* 编辑模式
*/
void AppSplitter::editViewSlots()
{
    if(markDown->isHidden())
    {
        markDown->show();
    }

    if(!browser->isHidden())
    {
        browser->hide();
    }
}

/**
* 双栏模式
*/
void AppSplitter::doubleViewSlots()
{
    if(markDown->isHidden())
    {
        markDown->show();
    }
    if(browser->isHidden())
    {
        browser->hide();
    }

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
    this->fileInfo->setHtmlText(markDown->toPlainText());

    // 更新文件保存状态
    this->fileInfo->setSaved(false);

    // 更新browser内容
    this->browser->setHtml(fileInfo->getHtmlText());

    // 激发编辑器内容发生变化信号
    emit editContentsChangedSignal(fileInfo->getFileTitle());
}
