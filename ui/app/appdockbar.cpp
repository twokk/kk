#include "appdockbar.h"
#include "QDebug"

AppDockBar::AppDockBar(QWidget *parent) :
    QWidget(parent)
{
    initWindowComponent();
    initWindowStatus();
}

AppDockBar::~AppDockBar()
{

}

/**
* 初始化窗口状态参数
*/
void AppDockBar::initWindowStatus()
{
    // 设置导航栏的固定高度
    this->setFixedHeight(APP_DOCK_FIX_HEIGHT);

    // 设置鼠标跟踪
    this->setMouseTracking(true);

    // 设置不继承父窗口北京
    this->setAutoFillBackground(true);

    // 设置背景透明
    this->setStyleSheet(APP_WINDOW_BACKGROUND_TRANSPARENT);
}

/**
* 初始化窗口组件
*/
void AppDockBar::initWindowComponent()
{
    this->setObjectName(APP_DOCK_BAR_NAME_SELF_NAME);

    vLayout = new QVBoxLayout();
    titleLayout = new QHBoxLayout();
    toolsLayout = new QHBoxLayout();

    vLayout->setMargin(0);
    titleLayout->setMargin(0);
    toolsLayout->setMargin(0);

    vLayout->setSpacing(0);
    titleLayout->setSpacing(0);
    toolsLayout->setSpacing(0);

    vLayout->setObjectName(APP_DOCK_BAR_NAME_V_LAYOUT);
    titleLayout->setObjectName(APP_DOCK_BAR_NAME_TITLE_LAYOUT);
    toolsLayout->setObjectName(APP_DOCK_BAR_NAME_TOOLS_LAYOUT);

    closeButton = new QToolButton();
    closeButton->setObjectName(APP_DOCK_BAR_NAME_CLOSE_BUTTON);
    closeButton->setText(APP_DOCK_BAR_TRANS_NAMES_CLOSE_BUTTON);

    maximButton = new QToolButton();
    closeButton->setObjectName(APP_DOCK_BAR_NAME_MAXIM_BUTTON);
    maximButton->setText(APP_DOCK_BAR_TRANS_NAMES_MAXIM_BUTTON);

    minimButton = new QToolButton();
    minimButton->setObjectName(APP_DOCK_BAR_NAME_MINIM_BUTTON);
    minimButton->setText(APP_DOCK_BAR_TRANS_NAMES_MINIM_BUTTON);

    setupButton = new QToolButton();
    setupButton->setObjectName(APP_DOCK_BAR_NAME_SETUP_MENU);
    setupButton->setPopupMode(QToolButton::InstantPopup);
    setupButton->setText(APP_DOCK_BAR_TRANS_NAMES_SETTING_BUTTON);

    logoLable = new QLabel();
    logoLable->setObjectName(APP_DOCK_BAR_NAME_LOGO_LABEL);
    logoLable->setText(APP_DOCK_BAR_TRANS_NAMES_LOGO_LABEL);

    textLabel = new QLabel();
    textLabel->setObjectName(APP_DOCK_BAR_NAME_TEXT_LABEL);
    textLabel->setText(APP_DOCK_BAR_TRANS_NAMES_TEXT_LABEL);

    titleLabel = new QLabel();
    titleLabel->setObjectName(APP_DOCK_BAR_NAME_TITLE_LABEL);
    titleLabel->setText(APP_DOCK_BAR_TRANS_NAMES_TITLE_LABEL);

    setupMenu = new AppSetupMenu();
    setupMenu->setObjectName(APP_DOCK_BAR_NAME_SETUP_MENU);
    setupButton->setMenu(setupMenu);

    titleLayout->addWidget(this->logoLable);
    titleLayout->addWidget(this->titleLabel);
    titleLayout->addWidget(this->textLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(this->minimButton);
    titleLayout->addWidget(this->maximButton);
    titleLayout->addWidget(this->closeButton);

    toolsLayout->addStretch();
    toolsLayout->addWidget(this->setupButton);

    vLayout->addLayout(titleLayout);
    vLayout->addLayout(toolsLayout);
    setLayout(vLayout);

    // 设置连接
    connect(setupMenu, &AppSetupMenu::setupMenuShowSignal, this, &AppDockBar::setSetupMenuPos);
}

/**
* 设置文本内容
*/
void AppDockBar::setTextContent(QString content)
{
    this->textLabel->setText(content);
}

/**
* 获取关闭按钮
*/
QToolButton* AppDockBar::getCloseButton()
{
    return this->closeButton;
}

/**
* 获取最大化按钮
*/
QToolButton* AppDockBar::getMaximButton()
{
    return this->maximButton;
}

/**
* 获取最小化按钮
*/
QToolButton* AppDockBar::getMinimButton()
{
    return this->minimButton;
}

/**
* 设置设置菜单的位置
*/
void AppDockBar::setSetupMenuPos()
{
    qDebug() << "hello";
    QPoint pos = mapToGlobal(setupButton->pos());
    pos.setX(pos.x() + setupButton->width() - setupMenu->width());
    pos.setY(pos.y() + setupButton->height());
    setupMenu->popup(pos);
}
