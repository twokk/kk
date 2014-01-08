#include "appproxy.h"
#include <QDebug>

AppProxy::AppProxy(QObject *parent) :
    QObject(parent)
{
    qDebug() << "bbbbbbb";
}

/**
* 重载的构造函数，用于从AppUi获取各个组件的指针
* @dockBar
* @splitter
* @statusBar
*/
AppProxy::AppProxy(AppDockBar* dockBar, AppSplitter* splitter, AppStatusBar* statusBar)
{
    this->dockBar = dockBar;
    this->splitter = splitter;
    this->statusBar = statusBar;
    memFileInfo = new FileInfo();
    splitter->setMarkdown("Hello,world");
}

/**
* 预览模式
*/
void AppProxy::previewSlots()
{
    splitter->setPrevewMode();
}

/**
* 编辑模式
*/
void AppProxy::editViewSlots()
{
    splitter->setEditMode();
}

/**
* 双栏模式
*/
void AppProxy::doubleViewSlots()
{

    splitter->setDoubleMode();
}

/**
* 帮助
*/
void AppProxy::helpSlots()
{
    QMessageBox::information(NULL, APP_SETUP_MENU_HELP, "<H2>Help</h2><h3>QQ Group:348234568        </h3><br>", QMessageBox::Ok);
}

/**
* 关于对话框
*/
void AppProxy::aboutSlots()
{
    QMessageBox::information(NULL, APP_SETUP_MENU_ABOUT, "<h2>Version : Markplus 0.5.2</h2><h4>QQ Group:348234568</h4><br/>", QMessageBox::Ok);
}

/**
* 反馈
*/
void AppProxy::feedBackSlots()
{
    QMessageBox::information(NULL, APP_SETUP_MENU_FEED_BACK, "<h2>Feed Back</h2><h3>QQ Group:348234568        </h3><br/>", QMessageBox::Ok);
}

/*******************************************槽函数*****************************************************/
/**
 * 打开文件
 */
void AppProxy::openFileSlots()
{
    // 如果文件全路径名不为空，则先保存
    if(!memFileInfo->getMarkdownFileFullName().isEmpty())
    {
        writeFile(memFileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN);
    }

    // 文件名为空，则弹出打开对话框
    QString fileFullName = QFileDialog::getOpenFileName(NULL, FILE_OPERATE_OPEN_FILE_TITLE, "D:\\", FILE_OPERATE_OPEN_FILE_EXTEND, 0, QFileDialog::DontUseNativeDialog);
    if(!fileFullName.isEmpty() && readFile(fileFullName))
    {
        // 更新编辑器
        splitter->setMarkdown(memFileInfo->getMarkdown());

        // 更新预览
        splitter->setBrowserHtml(memFileInfo->getMarkdown());

        // 激发编辑器内容保存信号
        // emit textChangeSlots(memFileInfo->getFileTitle());

        // 补充，更新文件状态为保存
        memFileInfo->setSaved(true);
    }

}

/**
* 导出成HTML
*/
void AppProxy::saveHtmlSlots()
{
    // 弹出保存对话框
    QString fileFullName = QFileDialog::getSaveFileName(NULL, FILE_OPERATE_SAVE_TO_HTML_TITLE, ".", FILE_OPERATE_SAVE_TO_HTML_EXTEND, 0, QFileDialog::DontUseNativeDialog) + FILE_STATUS_MARKDOWN_EXTENSION_HTML;

    // 保存HTML文件
    writeFile(fileFullName, FILE_STATUS_TYPE_HTML);
}

/**
* 另存为
*/
void AppProxy::saveAsSlots()
{
    QString fileFullName = QFileDialog::getSaveFileName(NULL, FILE_OPERATE_SAVE_AS, ".", FILE_OPERATE_SAVE_AS_EXTEND, 0, QFileDialog::DontUseNativeDialog);
    if(!fileFullName.isEmpty() && writeFile(fileFullName, FILE_STATUS_TYPE_OTHER))
    {
        // 激发编辑器内容保存信号
        //emit textSavedSignal(memFileInfo->getFileTitle());
    }
}

/**
* 保存成markdown格式槽
*/
void AppProxy::saveMarkdownSlots()
{
    if(memFileInfo->getMarkdownFileFullName().isEmpty())
    {
        QString fileFullName = QFileDialog::getSaveFileName(NULL, FILE_OPERATE_SAVE_TO_MARKDOAN_TITLE, ".", FILE_OPERATE_SAVE_TO_MARKDOWN_EXTEND, 0, QFileDialog::DontUseNativeDialog);
        // 保存markdown文件
        if(!fileFullName.isEmpty() && writeFile(fileFullName, FILE_STATUS_TYPE_MARKDOWN))
        {
            // 更新标题栏为保存状态
            dockBar->updateTitleText(memFileInfo->getFileTitle(), true);
        }
    }
    else if(writeFile(memFileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN))
    {
        // 更新标题栏为保存状态
        dockBar->updateTitleText(memFileInfo->getFileTitle(), true);
    }
}

/**
* 编辑器内容发生变化槽
*/
void AppProxy::textChangeSlots()
{
    // 更新文件markdown内容
    memFileInfo->setMarkdown(splitter->getMarkdown());

    // 更新文件保存状态
    memFileInfo->setSaved(false);

    // 更新浏览器预览内容
    splitter->setBrowserHtml(memFileInfo->getHtml());

    // 更新标题栏内容为未保存状态
    dockBar->updateTitleText(memFileInfo->getFileTitle(), false);
}

/**
* 退出程序
*/
void AppProxy::exitSlots()
{
    // 文件名不为空&&未保存，提醒是否保存，可直接保存
    if(!memFileInfo->getMarkdownFileFullName().isEmpty() && !memFileInfo->isSaved())
    {
        // 询问用户是否保存文件
        QMessageBox::StandardButton sb = QMessageBox::information(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_NOTE_SAVE_FILE, QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);

        // 用户要求保存文件
        if(sb == QMessageBox::Yes)
        {
            writeFile(memFileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN);

            // 关闭窗口
            emit exitSignals(true);
        }
        else if(sb == QMessageBox::No)
        {
            // 关闭窗口
            emit exitSignals(true);
        }
        else if(sb == QMessageBox::Cancel)
        {
            // 取消关闭
            emit exitSignals(false);
        }

        return;
    }
    else if(!memFileInfo->getMarkdownFileFullName().isEmpty() && memFileInfo->isSaved())
    {
        emit exitSignals(true);

        return;
    }


    // 文件为空&&文件名为空，不需要保存
    if(memFileInfo->getMarkdown().isEmpty() && memFileInfo->getMarkdownFileFullName().isEmpty())
    {
        // 关闭窗口
        emit exitSignals(true);

        return;
    }

    // 文件不为空&&文件名为空，需要新建保存文件
    if(!memFileInfo->getMarkdown().isEmpty() && memFileInfo->getMarkdownFileFullName().isEmpty())
    {
        // 询问用户是否保存文件
        QMessageBox::StandardButton sb = QMessageBox::information(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_NOTE_SAVE_FILE, QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);

        // 保存文件
        if(sb == QMessageBox::Yes)
        {
            // 弹出保存对话
            QString fileFullName = QFileDialog::getSaveFileName(NULL, FILE_OPERATE_SAVE_TO_MARKDOAN_TITLE, ".", FILE_OPERATE_SAVE_TO_MARKDOWN_EXTEND, 0, QFileDialog::DontUseNativeDialog);
            qDebug() << fileFullName;
            if(!fileFullName.isEmpty() && writeFile(fileFullName + FILE_STATUS_MARKDOWN_EXTENSION_MD, FILE_STATUS_TYPE_MARKDOWN))
            {
                // 关闭窗口
                emit exitSignals(true);
            }
            else
            {
                // 用户取消了保存文件，取消关闭窗口
                emit exitSignals(false);
            }
        }
        else if(sb == QMessageBox::No)
        {
            // 不保存文件，关闭窗口
            emit exitSignals(true);
        }
        else if(sb == QMessageBox::Cancel)
        {
            // 取消关闭
            emit exitSignals(false);
        }

        return;
    }
}

/**
* 放下markdown文件
* @fileFullName 放下的文件全路径
*/
void AppProxy::dropMarkdownSlots(QString fileFullName)
{
    // 如果文件名为空，直接返回
    if(NULL == fileFullName || fileFullName.isEmpty())
    {
        return;
    }

    // 询问是否保存文件
    if(memFileInfo->getMarkdownFileFullName().isEmpty()
            && QMessageBox::question(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_NOTE_SAVE_FILE, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        return;
    }

    // 保存已经存在的文件
    if(!memFileInfo->getMarkdownFileFullName().isEmpty())
    {
        writeFile(memFileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN);
    }

    // 读取文件内容
    if(readFile(fileFullName))
    {
        // 设置markdown编辑器内容
        splitter->setMarkdown(memFileInfo->getMarkdown());
    }
}

/*******************************************槽函数*****************************************************/

/**
* 读取文件
* @fileFullName 文件的全路径名称
*/
bool AppProxy::readFile(QString fileFullName)
{
    if(!fileFullName.isEmpty())
    {
        // 读取文件
        QFile file(fileFullName);

        // 打开文件失败
        if (!file.open(QIODevice::ReadOnly|QIODevice::WriteOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_CAN_NOT_CREATE_FILE);
            return false;
        }

        // 读文件
        QTextStream in(&file);
        QFileInfo info(fileFullName);
        QString text(in.readAll());

        // 更新文件信息
        memFileInfo->setFileTitle(info.filePath());
        memFileInfo->setMarkdown(text);
        memFileInfo->setHtmlText(script.markdownToHtml(text));
        memFileInfo->setMarkdownFileName(info.baseName());
        memFileInfo->setHtmlFileName("");
        memFileInfo->setMarkdownFileFullName(info.filePath());
        memFileInfo->setHtmlFileFullName("");
        memFileInfo->setSaved(true);
        memFileInfo->setTitled(true);

        file.close();

        return true;
    }

    return false;
}

/**
* 写文件
* @fileFullName 文件全路径名称
* @type 写文件类型，1:markdown,2:html
*/
bool AppProxy::writeFile(QString fileFullName, int type)
{
    if(!fileFullName.isEmpty()) {
        QFile file(fileFullName);

        // 打开文件失败
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QMessageBox::critical(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_CAN_NOT_CREATE_FILE);
            return false;
        }

        // 写文件
        QTextStream out(&file);
        // 保存markdown
        if(type == FILE_STATUS_TYPE_MARKDOWN || type == FILE_STATUS_TYPE_OTHER)
        {
            // 如果文件不是以.md|.markdown，则追加结尾
            if(type == FILE_STATUS_TYPE_MARKDOWN && !fileFullName.endsWith(FILE_STATUS_MARKDOWN_EXTENSION_MD) && !fileFullName.endsWith(FILE_STATUS_MARKDOWN_EXTENSION_MARKDOWN))
            {
                fileFullName = fileFullName + FILE_STATUS_MARKDOWN_EXTENSION_MD;
            }

            QFileInfo info(fileFullName);
            // 更新文件标题
            memFileInfo->setFileTitle(info.filePath());
            // 更新文件名称
            memFileInfo->setMarkdownFileName(info.fileName());
            // 更新文件路径
            memFileInfo->setMarkdownFileFullName(info.filePath());
            // 更新文件状态
            memFileInfo->setSaved(true);
            // 更新文件标题状态
            memFileInfo->setTitled(true);

            // 写文件内容到输出流
            out << memFileInfo->getMarkdown();
        }
        // 保存html
        else if(type == FILE_STATUS_TYPE_HTML)
        {
            // 写文件内容到输出流
            out << memFileInfo->getHtml();
        }

        out.flush();
        file.close();

        return true;
    }

    return false;
}
