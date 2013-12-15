#ifndef BASEFILEINFO_H
#define BASEFILEINFO_H

#include <QObject>

/**
* 记录文件信息
*/
class BaseFileInfo : public QObject
{
    Q_OBJECT
public:
    explicit BaseFileInfo(QObject *parent = 0);
    QString getFileName();
    QString getFilePath();
    QString getMarkdown();
    QString getHtmlText();
    int getFileStatus();
    void setFileName(QString);
    void setFilePath(QString);
    void setMarkdown(QString);
    void setHtmlText(QString);
    void setFileStatus(int);

signals:

public slots:

private:
    QString fileName;
    QString filePath;
    QString markdown;
    QString htmlText;
    int fileStatus;
};

#endif // BASEFILEINFO_H
