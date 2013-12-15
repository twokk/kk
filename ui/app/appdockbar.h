#ifndef APPDOCKBAR_H
#define APPDOCKBAR_H

#include <QLabel>
#include <QWidget>
#include <QString>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "app/appsetupmenu.h"
#include "include/appparam.h"
#include "include/transnames.h"
#include "include/buildnames.h"

/**
* 系统导航栏，在窗口最顶部
*/

class AppDockBar : public QWidget
{
    Q_OBJECT
public:
    explicit AppDockBar(QWidget *parent = 0);
    virtual ~AppDockBar();

    QToolButton* getCloseButton();
    QToolButton* getMaximButton();
    QToolButton* getMinimButton();

private:
    void initWindowComponent();
    void initWindowStatus();

private:
    QVBoxLayout* vLayout;
    QHBoxLayout* titleLayout;
    QHBoxLayout* toolsLayout;
    QToolButton* closeButton;
    QToolButton* maximButton;
    QToolButton* minimButton;
    QToolButton* setupButton;
    QLabel* logoLable;
    QLabel* textLabel;
    QLabel* titleLabel;
    AppSetupMenu* setupMenu;

signals:

public slots:
    void setTextContent(QString content);
    void setSetupMenuPos();

};

#endif // APPDOCKBAR_H
