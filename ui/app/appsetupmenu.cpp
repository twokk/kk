#include "appsetupmenu.h"
#include "QDebug"

AppSetupMenu::AppSetupMenu(QWidget *parent) :
    QMenu(parent)
{
    initSetMenu();
    initActions();
}

void AppSetupMenu::initSetMenu()
{
    setMinimumWidth(400);
    setMaximumWidth(400);
}

void AppSetupMenu::initActions()
{
    editPost = new QAction(QObject::tr("Editor View"), this);
    editPost->setShortcut(QObject::tr("Ctrl+E"));
    prePost = new QAction(QObject::tr("Preview View(P)"), this);
    prePost->setShortcut(QObject::tr("Ctrl+P"));
    doubleView = new QAction(QObject::tr("Double View(D)"), this);
    doubleView->setShortcut(QObject::tr("Ctrl+D"));
    pubPost = new QAction(QObject::tr("Publish Post(T)"), this);
    pubPost->setShortcut(QObject::tr("Ctrl+T"));
    find = new QAction(QObject::tr("Find(F)"), this);
    find->setShortcut(QObject::tr("Ctrl+F"));
    print = new QAction(QObject::tr("Print(P)"), this);
    print->setShortcut(QObject::tr("Ctrl+Alt+P"));
    open = new QAction(QObject::tr("Open(O)"), this);
    open->setShortcut(QObject::tr("Ctrl+O"));
    save = new QAction(QObject::tr("Save(S)"), this);
    save->setShortcut(QObject::tr("Ctrl+S"));
    saveToHtml = new QAction(QObject::tr("Save To Html(H)"), this);
    saveToHtml->setShortcut(QObject::tr("Ctrl+H"));
    syncPost = new QAction(QObject::tr("Sync To Clound"), this);
    setAccount = new QAction(QObject::tr("Set Your Account"), this);
    setAction = new QAction(QObject::tr("Setting"), this);
    about = new QAction(QObject::tr("About"), this);
    feedBack = new QAction(QObject::tr("Feed Back"), this);
    help = new QAction(QObject::tr("Help"), this);
    exit = new QAction(QObject::tr("Exit(X)"), this);
    exit->setShortcut(QObject::tr("Ctrl+X"));

    addAction(doubleView);
    addAction(editPost);
    addAction(prePost);
    //addAction(pubPost);
    addSeparator();
    //addAction(find);
    //addAction(print);
    addAction(open);
    addAction(save);
    addAction(saveToHtml);
    //addSeparator();
    //addAction(syncPost);
    //addAction(setAccount);
    addSeparator();
    addAction(about);
    addAction(feedBack);
    addAction(help);
    addSeparator();
    addAction(exit);

    // 构建信号槽连接
    connect(prePost, &QAction::triggered, this, &AppSetupMenu::previewSlots);
    connect(editPost, &QAction::triggered, this, &AppSetupMenu::editViewSlots);
    connect(doubleView, &QAction::triggered, this, &AppSetupMenu::doubleViewSlots);
    connect(open, &QAction::triggered, this, &AppSetupMenu::openFileSlots);
    connect(save, &QAction::triggered, this, &AppSetupMenu::saveMarkdownSlots);
    connect(saveToHtml, &QAction::triggered, this, &AppSetupMenu::saveHtmlSlots);
    connect(about, &QAction::triggered, this, &AppSetupMenu::aboutSlots);
    connect(feedBack, &QAction::triggered, this, &AppSetupMenu::feedBackSlots);
    connect(help, &QAction::triggered, this, &AppSetupMenu::helpSlots);
    connect(exit, &QAction::triggered, this, &AppSetupMenu::exitSlots);
}

void AppSetupMenu::showEvent(QShowEvent *)
{
    emit setupMenuShowSignal();
}

/**
* 打开文件
*/
void AppSetupMenu::openFileSlots()
{
    emit openFileSignal();
}

/**
* 保存成html格式
*/
void AppSetupMenu::saveHtmlSlots()
{
    emit saveHtmlSignal();
}

/**
* 保存成markdown格式
*/
void AppSetupMenu::saveMarkdownSlots()
{
    emit saveMarkdownSignal();
}

/**
* 预览模式
*/
void AppSetupMenu::previewSlots()
{
    emit previewSignal();
}

/**
* 编辑模式
*/
void AppSetupMenu::editViewSlots()
{
    emit editViewSignal();
}

/**
* 双栏视图
*/
void AppSetupMenu::doubleViewSlots()
{
    emit doubleViewSignal();
}

/**
* 关于程序
*/
void AppSetupMenu::aboutSlots()
{
    emit aboutSignal();
}


/**
* 帮助
*/
void AppSetupMenu::helpSlots()
{
    emit helpSignal();
}

/**
* 反馈
*/
void AppSetupMenu::feedBackSlots()
{
    emit feedBackSignal();
}

/**
* 退出程序
*/
void AppSetupMenu::exitSlots()
{
    emit exitSignal();
}

