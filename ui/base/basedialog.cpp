#include "basedialog.h"

BaseDialog::BaseDialog(QWidget *parent) :
    QDialog(parent)
{
}

/**
* 重载对话框构造函数，根据参数创建基本对话框
* @titleText
* @icon
* @infoText
* @mode
* @okButton
* @noButton
* @cancelButton
*/
BaseDialog::BaseDialog(QString titleText, QString icon, QString infoText, bool mode, bool okButton, bool noButton, bool cancelButton)
{
    mainLayout = new QVBoxLayout();
    titleLayout = new QHBoxLayout();
    infoLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();

    titleLab = new QLabel(titleText);
    closeBtn = new QToolButton();
}
