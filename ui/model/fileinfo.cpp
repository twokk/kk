#include "fileinfo.h"

FileInfo::FileInfo(QObject *parent) :
    QObject(parent)
{
}

/**
* 获取文件标题
*/
QString FileInfo::getFileTitle()
{
    return this->fileTitle;
}

/**
* 设置文件标题
*/
void FileInfo::setFileTitle(QString fileTitle)
{
    this->fileTitle = fileTitle;
}

/**
* 获取markdown文件名称
*/
QString FileInfo::getMarkdownFileName()
{
    return this->markdownFileName;
}

/**
* 设置markdown文件名称
*/
void FileInfo::setMarkdownFileName(QString fileName)
{
    this->markdownFileName = fileName;
}

/**
* 获取html文件名称
*/
QString FileInfo::getHtmlFileName()
{
    return this->htmlFileName;
}

/**
* 设置html文件名称
*/
void FileInfo::setHtmlFileName(QString fileName)
{
    this->htmlFileName = fileName;
}

/**
* 获取markdown文件路径
*/
QString FileInfo::getMarkdownFilePath()
{
    return this->markdownFilePath;
}

/**
* 设置markdown文件名称
*/
void FileInfo::setMarkdownFilePath(QString filePath)
{
    this->markdownFilePath = filePath;
}

/**
* 获取html文件路径
*/
QString FileInfo::getHtmlFilePath()
{
    return this->htmlFilePath;
}

/**
* 设置html文件路径
*/
void FileInfo::setHtmlFilePath(QString filePath)
{
    this->htmlFilePath = filePath;
}

/**
* 获取markdown文本
*/
QString FileInfo::getMarkdown()
{
    return this->markdown;
}

/**
* 设置markdown文本
*/
void FileInfo::setMarkdown(QString markdown)
{
    this->markdown = markdown;
}

/**
* 获取htmlText文本
*/
QString FileInfo::getHtmlText()
{
    return this->htmlText;
}

/**
* 设置htmlText文本
*/
void FileInfo::setHtmlText(QString text)
{
    // 转换markdown文本为html
    this->htmlText = AppUtil::markDownToHtml(text);
}

/**
* 获取保存状态
*/
bool FileInfo::isSaved()
{
    return this->bSaved;
}

/**
* 设置保存状态
*/
void FileInfo::setSaved(bool bSaved)
{
    this->bSaved = bSaved;
}

/**
* 获取设置标题状态
*/
bool FileInfo::isTitled()
{
    return this->bTitled;
}

/**
* 设置标题状体
*/
void FileInfo::setTitled(bool bTitle)
{
    this->bTitled = bTitle;
}
