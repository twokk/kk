#ifndef APPPARAM_H
#define APPPARAM_H

// 主窗体缩放枚举定义
enum enum_Direction
{
   eNone,
   eTop = 1,
   eRight =2 ,
   eBottom =4,
   eLeft = 8,
   eTopRight = eTop + eRight,
   eRightBottom = eRight + eBottom,
   eBottomLeft = eBottom + eLeft,
   eLeftTop = eLeft + eTop
};

// 主窗体移动,拖动区域定义
#define APP_WINDOW_DRAG_TOP_HEIGHT 100
#define APP_WINDOW_ZOOM_PADDING 1
#define APP_WINDOW_ZOOM_CLICK 45
#define APP_WINDOW_INIT_TOP_LEFT_X 50
#define APP_WINDOW_INIT_TOP_LEFT_Y 50
#define APP_WINDOW_INIT_WIDTH 800
#define APP_WINDOW_INIT_HEIGHT 600
#define APP_WINDOW_RESIZE_NONE 0
#define APP_WINDOW_RESIZE_TOP 2
#define APP_WINDOW_RESIZE_RIGHT 3
#define APP_WINDOW_RESIZE_BOTTOM 6
#define APP_WINDOW_RESIZE_LEFT 7
#define APP_WINDOW_DEFAULT_STYLE_SHEET ":/skin/default"
#define APP_WINDOW_BACKGROUND_TRANSPARENT "background-color:transparent"

// 主窗体导航栏参数
#define APP_DOCK_FIX_HEIGHT 55
#define APP_DOCK_BAR_TITLE_BUTTON_SIZE 24

// 主窗体状态栏参数
#define APP_STATUS_BAR_FIX_HEIGHT 10

// 文件状态
#define FILE_STATUS_DEFAULT_FILE_TITLE "undefine"
#define FILE_STATUS_MARKDOWN_EXTENSION_MD "md"
#define FILE_STATUS_MARKDOWN_EXTENSION_MARKDOWN "markdown"
#define FILE_STATUS_MARKDOWN_EXTENSION_HTM "htm"
#define FILE_STATUS_MARKDOWN_EXTENSION_HTML "HTML"
#define FILE_STATUS_TYPE_MARKDOWN 1
#define FILE_STATUS_TYPE_HTML 2
#define FILE_STATUS_TYPE_OTHER 3

#endif // APPPARAM_H
