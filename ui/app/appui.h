#ifndef APPUI_H
#define APPUI_H

#include <QRect>
#include <QSize>
#include <QPoint>
#include <math.h>
#include <QWidget>
#include <QPalette>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include "app/appdockbar.h"
#include "app/appsplitter.h"
#include "app/appstatusbar.h"
#include "include/appparam.h"
#include "include/buildnames.h"
#include "ui_global.h"

/**
* 主窗体，所有组件和窗体拖动，大小操作均针对该组件定义
*/

class UISHARED_EXPORT AppUi : public QWidget
{
    Q_OBJECT
public:
    explicit AppUi(QWidget *parent = 0);

private:
    static QVBoxLayout* layout;     // 主窗体布局
    static AppDockBar* dockBar;     // 主窗体导航栏
    static AppSplitter* splitter;   // 主分隔栏
    static AppStatusBar* statusBar; // 主窗体状态栏

    bool bLeftPressed;              // 左键状态
    bool bIsMoving;                 // 是否正在移动
    bool bIsResizing;               // 是否正在调整大小
    bool bIsMaxAble;                // 是否最大化
    enum_Direction eDirection;      // 调节大小的光标方向
    QRect rRestoreWindow;           // 保存非最大化时窗体尺寸
    QPoint pPressPoint;             // 鼠标按下时的位置
    QPoint pCurrentPoint;           // 鼠标当前的位置

signals:

public slots:
    void showMaxRestore();

private:
    void initComponent();
    void initWindowState();
    void setupStyleSheet(QString);

    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void setCursorStyle(enum_Direction direction);                          // 设置光标样式
    void setDrayMove(int nXGlobal, int nYGlobal, enum_Direction direction); // 调节大小
    enum_Direction resizeValid(int nXRelative, int nYRelative);             // 设置光标方向

public:
    static AppDockBar* getDockBar();
    static AppSplitter* getSplitter();
    static AppStatusBar* getStatusBar();

};

#endif // APPUI_H