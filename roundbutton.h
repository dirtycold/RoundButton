#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H

#include <QWidget>

#define ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE
#undef ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE

class RoundButton : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(AlignMode alignment READ alignment WRITE setAlignment)

#ifdef ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE
    Q_PROPERTY(qreal textSizeRatio READ textSizeRatio WRITE setTextSizeRatio)
#endif

public:
    enum AlignMode
    {
        AlignCenter = 0x0,
        AlignLeft   = 0x1,
        AlignRight  = 0x2,
        AlignBoth   = AlignLeft | AlignRight,
    };
    Q_DECLARE_FLAGS(AlignModes, AlignMode)

    RoundButton(QWidget *parent = 0);
    ~RoundButton();

    void setColor (const QColor &color);
    QColor color () const;

    void setTextColor (const QColor &color);
    QColor textColor () const;

    void setText (const QString &text);
    QString text () const;

    void setAlignment (AlignMode alignment);
    AlignMode alignment () const;

#ifdef ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE
    void setTextSizeRatio (const qreal ratio);
    qreal textSizeRatio () const;
#endif

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

#ifdef ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE
    qreal m_textSizeRatio;
#endif
};

#endif // ROUNDBUTTON_H
