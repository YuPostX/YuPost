#ifndef YPOPUSHBUTTON_H
#define YPOPUSHBUTTON_H
#include <QPushButton>
#include <QStyleOptionButton>
#include <QIcon>

class YuPostPushButton : public QPushButton
{
public:
    explicit YuPostPushButton(QWidget * parent = Q_NULLPTR);
    explicit YuPostPushButton(const QString &text, QWidget *parent = Q_NULLPTR);

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    void updateIcon(QStyleOptionButton &pushbutton);

private:
    bool m_iconCached;
    QIcon m_downIcon;
};

#endif // YPOPUSHBUTTON_H
