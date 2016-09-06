#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H

#include <QWidget>

class RoundButton : public QWidget
{
    Q_OBJECT

public:
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

    void setAlignment (Qt::AlignmentFlag alignment);
    Qt::AlignmentFlag alignment () const;

signals:
    void clicked ();

protected:
    bool event(QEvent * event);
    void paintEvent (QPaintEvent *event);

private:
    QColor m_color;
    QColor m_textColor;
    QString m_text;
    Qt::AlignmentFlag m_alignment;
    qreal m_textSizeRatio;
};

#endif // ROUNDBUTTON_H
