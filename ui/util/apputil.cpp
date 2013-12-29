#include "apputil.h"

AppUtil::AppUtil(QObject *parent) :
    QObject(parent)
{
}

QString AppUtil::markDownToHtml(QString markdown)
{
    return markdown;
}
