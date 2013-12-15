#ifndef SCRIPT_H
#define SCRIPT_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include "script_global.h"
#include "v8.h"

class SCRIPTSHARED_EXPORT Script
{

public:
    Script();
    QString markdownToHtml(QString markdown);
    QString htmlToMarkdown(QString html);

private:
    v8::HandleScope handleScope;
    v8::Persistent<v8::Context> markedContext;
    void initEnvironment();
    const char* ToCString(const v8::String::Utf8Value& value);
    QString filterIllegalChar(QString input);
    QString loadMarkedJs();
};

#endif // SCRIPT_H
