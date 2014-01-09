#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>

/**
* 自定义Dialog基类，提供无边框，自定义样式的组件。
*/

class BaseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BaseDialog(QWidget *parent = 0);
    explicit BaseDialog(QString titleText, QString icon, QString infoText, bool mode, bool okButton, bool noButton, bool cancelButton);

signals:

public slots:

private:
    QLabel* titleLab;
    QLabel* icon;
    QLabel* infoText;
    QPushButton* okBtn;
    QPushButton* noBtn;
    QToolButton* closeBtn;
    QPushButton* cancelBtn;
    QVBoxLayout* mainLayout;
    QHBoxLayout* titleLayout;
    QHBoxLayout* infoLayout;
    QHBoxLayout* buttonLayout;

};

#endif // BASEDIALOG_H
