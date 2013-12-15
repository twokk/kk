#include "basefileinfo.h"

BaseFileInfo::BaseFileInfo(QObject *parent) :
    QObject(parent)
{
}

/**
* 获取文件名称(含路径)
*/
QString BaseFileInfo::getFileName()
{
    return this->fileName;
}

/**
* 设置文件名称
*/
void BaseFileInfo::setFileName(QString fileName)
{
    this->fileName = fileName;
}

/**
* 获取文件路径
*/
QString BaseFileInfo::getFilePath()
{
    return this->filePath;
}

/**
* 设置文件路径
*/
void BaseFileInfo::setFilePath(QString filePath)
{
    this->filePath = filePath;
}

/**
* 获取Html文本
*/
QString BaseFileInfo::getHtmlText()
{
    return this->htmlText;
}

/**
* 设置Html文本
*/
void BaseFileInfo::setHtmlText(QString htmlText)
{
    this->htmlText = htmlText;
}

/**
* 获取markdown文本
*/
QString BaseFileInfo::getMarkdown()
{
    return this->markdown;
}

/**
* 设置markdown文本
*/
void BaseFileInfo::setMarkdown(QString markdown)
{
    this->markdown = markdown;
}

/**
* 获取文件状态
*/
int BaseFileInfo::getFileStatus()
{
    return this->fileStatus;
}

/**
* 设置文件状态
*/
void BaseFileInfo::setFileStatus(int status)
{
    this->fileStatus = status;
}
