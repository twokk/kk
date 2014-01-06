#include "appsplitter.h"
#include "QDebug"

AppSplitter::AppSplitter(QWidget *parent) :
    QSplitter(parent)
{
    initFileStatus();
    initWindowStatus();
    initComponet();
    initHtmlTemplate();
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
    fileInfo->setFileTitle(APP_DOCK_BAR_TRANS_NAMES_TEXT_LABEL);
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
    // 如果文件全路径名不为空，则先保存。
    if(!fileInfo->getMarkdown().isEmpty() && !fileInfo->getMarkdownFileFullName().isEmpty())
    {
        writeFile(fileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN);
    }

    // 文件名为空，则弹出打开对话框
    QString fileFullName = QFileDialog::getOpenFileName(this, FILE_OPERATE_OPEN_FILE_TITLE, "D:\\", FILE_OPERATE_OPEN_FILE_EXTEND, 0, QFileDialog::DontUseNativeDialog);
    if(!fileFullName.isEmpty() && readFile(fileFullName)) {

        // 更新编辑器
        markDown->setPlainText(fileInfo->getMarkdown());

        // 更新预览
        setBrowserHtml();

        // 激发编辑器内容保存信号
        emit editContentsSavedSignal(fileInfo->getFileTitle());

        // 更新文件状态为保存
        fileInfo->setSaved(true);
    }
}

/**
* 保存成HTML
*/
void AppSplitter::saveHtmlSlots()
{
    if(fileInfo->getHtmlFileFullName().isEmpty())
    {
        QString fileFullName = QFileDialog::getSaveFileName(this, FILE_OPERATE_SAVE_TO_HTML_TITLE, ".", FILE_OPERATE_SAVE_TO_HTML_EXTEND, 0, QFileDialog::DontUseNativeDialog) + FILE_STATUS_MARKDOWN_EXTENSION_HTML;
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
        QString fileFullName = QFileDialog::getSaveFileName(this, FILE_OPERATE_SAVE_TO_MARKDOAN_TITLE, ".", FILE_OPERATE_SAVE_TO_MARKDOWN_EXTEND, 0, QFileDialog::DontUseNativeDialog);
        // 保存markdown文件
        if(!fileFullName.isEmpty() && writeFile(fileFullName, FILE_STATUS_TYPE_MARKDOWN))
        {
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
    QString fileFullName = QFileDialog::getSaveFileName(this, FILE_OPERATE_SAVE_AS, ".", FILE_OPERATE_SAVE_AS_EXTEND, 0, QFileDialog::DontUseNativeDialog);
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
    QMessageBox::information(NULL, APP_SETUP_MENU_HELP, "<H2>Help</h2><h3>QQ Group:348234568        </h3><br>", QMessageBox::Ok);
}

/**
* 关于对话框
*/
void AppSplitter::aboutSlots()
{
    QMessageBox::information(NULL, APP_SETUP_MENU_ABOUT, "<h2>Version : Markplus 0.5.2</h2><h4>QQ Group:348234568</h4><br/>", QMessageBox::Ok);
}

/**
* 反馈
*/
void AppSplitter::feedBackSlots()
{
    QMessageBox::information(NULL, APP_SETUP_MENU_FEED_BACK, "<h2>Feed Back</h2><h3>QQ Group:348234568        </h3><br/>", QMessageBox::Ok);
}
/*******************************************响应设置菜单槽函数***********************************************/

/**
* 编辑器内容发生变化
*/
void AppSplitter::editContentsChangedSlots()
{
    // 更新文件markdown内容
    this->fileInfo->setMarkdown(markDown->toPlainText());

    // 更新文件保存状态
    this->fileInfo->setSaved(false);

    // 更新预览内容
    setBrowserHtml();

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
* @event 事件
*/
void AppSplitter::dropEvent(QDropEvent *event)
{
    // 询问是否保存文件
    if(fileInfo->getMarkdownFileFullName().isEmpty()
            && QMessageBox::question(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_NOTE_SAVE_FILE, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        return;
    }

    // 保存已经存在的文件
    if(!fileInfo->getMarkdownFileFullName().isEmpty())
    {
        writeFile(fileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN);
    }

    // 加载拖拽文件
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
* @fileFullName 文件的全路径名称
*/
bool AppSplitter::readFile(QString fileFullName)
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
* @fileFullName 文件全路径名称
* @type 写文件类型，1:markdown,2:html
*/
bool AppSplitter::writeFile(QString fileFullName, int type)
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
            out << fileInfo->getHtml();
        }

        out.flush();
        file.close();

        return true;
    }

    return false;
}

/**
* 加载html模板
*/
void AppSplitter::initHtmlTemplate()
{
    QFile htmlTemp(HTML_TEMPLATE_DEFAULT);

    // 打开文件失败
    if (!htmlTemp.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_CAN_NOT_OPEN_FILE);
        return;
    }

    QTextStream in(&htmlTemp);

    htmlTemplate = in.readAll();

    htmlTemp.close();;
}

/**
* 为浏览器设置HTML
*/
void AppSplitter::setBrowserHtml()
{
    QString htmlTmp = genBrowserHtml();

    // 更新fileInfo
    fileInfo->setHtmlText(htmlTmp);

    // 将填充好的模板写入到browser
    browser->setHtml(htmlTmp);
}

/**
* 将 markdown编译后的html作为参数写入HTML模板
*/
QString AppSplitter::genBrowserHtml()
{
    return htmlTemplate.arg(genHtml());
}

/**
* 生成html，不附带css
*/
QString AppSplitter::genHtml()
{
    QString html = script.markdownToHtml(markDown->toPlainText());
    // 更新fileInfo
    fileInfo->setHtml(html);

    return html;
}

/**
* 程序退出
*/
void AppSplitter::exitSlots()
{
    qDebug() << "aaaaaaaaaaa" << fileInfo->getMarkdownFileFullName() << "  " << fileInfo->getMarkdown() << "   " << fileInfo->isSaved();

    // 文件名不为空&&未保存，提醒是否保存，可直接保存
    if(!fileInfo->getMarkdownFileFullName().isEmpty() && !fileInfo->isSaved())
    {
        // 询问用户是否保存文件
        QMessageBox::StandardButton sb = QMessageBox::information(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_NOTE_SAVE_FILE, QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);

        // 用户要求保存文件
        if(sb == QMessageBox::Yes)
        {
            writeFile(fileInfo->getMarkdownFileFullName(), FILE_STATUS_TYPE_MARKDOWN);

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
    else if(!fileInfo->getMarkdownFileFullName().isEmpty() && fileInfo->isSaved())
    {
        emit exitSignals(true);

        return;
    }


    // 文件为空&&文件名为空，不需要保存
    if(fileInfo->getMarkdown().isEmpty() && fileInfo->getMarkdownFileFullName().isEmpty())
    {
        // 关闭窗口
        emit exitSignals(true);

        return;
    }

    // 文件不为空&&文件名为空，需要新建保存文件
    if(!fileInfo->getMarkdown().isEmpty() && fileInfo->getMarkdownFileFullName().isEmpty())
    {
        // 询问用户是否保存文件
        QMessageBox::StandardButton sb = QMessageBox::information(NULL, FILE_OPERATE_SHOW_NOTE, FILE_OPERATE_NOTE_SAVE_FILE, QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);

        // 保存文件
        if(sb == QMessageBox::Yes)
        {
            // 弹出保存对话
            QString fileFullName = QFileDialog::getSaveFileName(this, FILE_OPERATE_SAVE_TO_MARKDOAN_TITLE, ".", FILE_OPERATE_SAVE_TO_MARKDOWN_EXTEND, 0, QFileDialog::DontUseNativeDialog);
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
