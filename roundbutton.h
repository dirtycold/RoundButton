#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H

#include <QWidget>

class RoundButton : public QWidget
{
    Q_OBJECT

public:
    enum AlignMode
    {
        AlignCenter = 0x0,
        AlignLeft   = 0x1,
        AlignRight  = 0x2,
        AlignBoth   = AlignLeft | AlignRight,
    };

    RoundButton(QWidget *parent = 0);
    ~RoundButton();

    void setColor (const QColor &color);
    QColor color () const;

    void setTextColor (const QColor &color);
    QColor textColor () const;

    void setText (const QString &text);
    QString text () const;

    void setTextSizeRatio (const qreal ratio);
    qreal textSizeRatio () const;

    void setAlignment (AlignMode alignment);
    AlignMode alignment () const;

signals:
    void clicked ();

protected:
    bool event(QEvent * event);
    void paintEvent (QPaintEvent *event);

private:
    QColor m_color;
    QColor m_textColor;
    QString m_text;
    AlignMode m_alignment;
    qreal m_textSizeRatio;
};

#endif // ROUNDBUTTON_H
