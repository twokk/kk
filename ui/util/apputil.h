#ifndef APPUTIL_H
#define APPUTIL_H

#include <QObject>

class AppUtil : public QObject
{
    Q_OBJECT
public:
    explicit AppUtil(QObject *parent = 0);

signals:

public slots:

public:
    static QString markDownToHtml(QString);

};

#endif // APPUTIL_H
