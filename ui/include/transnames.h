#ifndef TRANSNAMES_H
#define TRANSNAMES_H

/**
* dockBar组件显示名称定义
*/
#define APP_DOCK_BAR_TRANS_NAMES_LOGO_LABEL ":/images/logo-m-t"
#define APP_DOCK_BAR_TRANS_NAMES_TITLE_LABEL " - Markplus"
#define APP_DOCK_BAR_TRANS_NAMES_BLANK " "
#define APP_DOCK_BAR_TRANS_NAMES_TEXT_LABEL QObject::tr("undefine")
#define APP_DOCK_BAR_TRANS_NAMES_MINIM_BUTTON ":/tittleButton/mini"
#define APP_DOCK_BAR_TRANS_NAMES_MAXIM_BUTTON ":/tittleButton/max"
#define APP_DOCK_BAR_TRANS_NAMES_NORMAL_BUTTON ":/tittleButton/normal"
#define APP_DOCK_BAR_TRANS_NAMES_CLOSE_BUTTON ":/tittleButton/close"
#define APP_DOCK_BAR_TRANS_NAMES_SETUP_BUTTON ":/tittleButton/setup"

/**
* 设置菜单显示名称定义
*/
#define APP_SETUP_MENU_EDIT_POST QObject::tr("Editor View")
#define APP_SETUP_MENU_PRE_POST QObject::tr("Preview View")
#define APP_SETUP_MENU_DOUBLE_VIEW QObject::tr("Double View")
#define APP_SETUP_MENU_PUB_POST QObject::tr("Publish Post")
#define APP_SETUP_MENU_FIND QObject::tr("Find")
#define APP_SETUP_MENU_PRINT QObject::tr("Print")
#define APP_SETUP_MENU_OPEN QObject::tr("Open")
#define APP_SETUP_MENU_SAVE QObject::tr("Save")
#define APP_SETUP_MENU_SAVE_AS QObject::tr("Save As")
#define APP_SETUP_MENU_TO_HTML QObject::tr("Save To Html")
#define APP_SETUP_MENU_SYNC_POST QObject::tr("Sync To Cloud")
#define APP_SETUP_MENU_SET_ACCOUNT QObject::tr("Set Your Account")
#define APP_SETUP_MENU_SET_ACTION QObject::tr("Setting")
#define APP_SETUP_MENU_ABOUT QObject::tr("About")
#define APP_SETUP_MENU_FEED_BACK QObject::tr("Feed Back")
#define APP_SETUP_MENU_HELP QObject::tr("Help")
#define APP_SETUP_MENU_EXIT QObject::tr("Exit")

/**
* 快捷键定义
*/
#define APP_SHOT_CUT_EDIT_POST QObject::tr("Ctrl+Alt+E")
#define APP_SHOT_CUT_PREVIEW_VIEW QObject::tr("Ctrl+Alt+P")
#define APP_SHOT_CUT_DOUBLE_VIEW QObject::tr("Ctrl+Alt+D")
#define APP_SHOT_CUT_PUBLISH_POST QObject::tr("Ctrl+Alt+T")
#define APP_SHOT_CUT_FIND QObject::tr("Ctrl+F")
#define APP_SHOT_CUT_PRINT QObject::tr("Ctrl+P")
#define APP_SHOT_CUT_OPEN QObject::tr("Ctrl+O")
#define APP_SHOT_CUT_SAVE QObject::tr("Ctrl+S")
#define APP_SHOT_CUT_SAVE_TO_HTML QObject::tr("Ctrl+H")
#define APP_SHOT_CUT_EXIT QObject::tr("Ctrl+Alt+X")

/**
* 对话框显示名称定义
*/
#define FILE_OPERATE_SHOW_NOTE QObject::tr("Note")
#define FILE_OPERATE_CAN_NOT_OPEN_FILE QObject::tr("Can not open file")
#define FILE_OPERATE_CAN_NOT_CREATE_FILE QObject::tr("Can not create file")
#define FILE_OPERATE_SAVE_TO_MARKDOAN_TITLE QObject::tr("Save as markdown file")
#define FILE_OPERATE_SAVE_TO_HTML_TITLE QObject::tr("Save as html file")
#define FILE_OPERATE_SAVE_AS QObject::tr("Save as")
#define FILE_OPERATE_SAVE_TO_MARKDOWN_EXTEND QObject::tr("Markdown file(*.md *.markdown)")
#define FILE_OPERATE_SAVE_TO_HTML_EXTEND QObject::tr("Html file(*.htm *.html)")
#define FILE_OPERATE_SAVE_AS_EXTEND QObject::tr("All file(*.*)")
#define FILE_OPERATE_OPEN_FILE_TITLE QObject::tr("Open")
#define FILE_OPERATE_OPEN_FILE_EXTEND QObject::tr("Markdown file(*.md *.markdown)")
#define FILE_OPERATE_NOTE_SAVE_FILE QObject::tr("Do you want to save the current file ?")

/**
* 文件信息KEY值定义
*/
#define FILE_INFO_KEY_TEXT "Text"   // 文件内容
#define FILE_INFO_KEY_TITLE "Title" // 文件标题
#define FILE_INFO_KEY_FILE_NAME "FileName" // 文件名称
#define FILE_INFO_KEY_MARKDOWN_FILE_FULL_NAME "MarkdownFileFullName" // markdown文件全路径名称

#endif // TRANSNAMES_H
