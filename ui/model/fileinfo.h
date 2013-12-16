#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>

class FileInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileInfo(QObject *parent = 0);
    QString getFileTitle();
    QString getMarkdownFileName();
    QString getHtmlFileName();
    QString getMarkdownFilePath();
    QString getHtmlFilePath();
    QString getMarkdown();
    QString getHtmlText();
    bool isSaved();
    bool isTitled();
    void setFileTitle(QString);
    void setMarkdownFileName(QString);
    void setHtmlFileName(QString);
    void setMarkdownFilePath(QString);
    void setHtmlFilePath(QString);
    void setMarkdown(QString);
    void setHtmlText(QString);
    void setFileStatus(int);
    void setSaved(bool);
    void setTitled(bool);

signals:

public slots:

private:
    QString fileTitle;
    QString markdownFileName;
    QString htmlFileName;
    QString markdownFilePath;
    QString htmlFilePath;
    QString markdown;
    QString htmlText;
    bool bSaved;
    bool bTitled;

};

#endif // FILEINFO_H
