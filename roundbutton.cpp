#include "roundbutton.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>

RoundButton::RoundButton(QWidget *parent)
    : QWidget(parent)
{
    QPalette palette = this->palette ();
    m_color = palette.color (QPalette::Background);
    m_textColor = palette.color (QPalette::Foreground);
    m_alignment = AlignCenter;

#ifdef ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE
    m_textSizeRatio = 1.0;
#endif

}

RoundButton::~RoundButton()
{

}

void RoundButton::setColor(const QColor &color)
{
    m_color = color;
    update ();
}

QColor RoundButton::color() const
{
    return m_color;
}

void RoundButton::setTextColor(const QColor &color)
{
    m_textColor = color;
    update ();
}

QColor RoundButton::textColor() const
{
    return m_textColor;
}

void RoundButton::setText(const QString &text)
{
    m_text = text;
    update ();
}

QString RoundButton::text() const
{
    return m_text;
}

#ifdef ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE
void RoundButton::setTextSizeRatio(const qreal ratio)
{
    m_textSizeRatio = ratio;
    update ();
}

qreal RoundButton::textSizeRatio() const
{
    return m_textSizeRatio;
}
#endif // ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE

void RoundButton::setAlignment(AlignMode alignment)
{
    m_alignment = alignment;
    update ();
}

RoundButton::AlignMode RoundButton::alignment() const
{
    return m_alignment;
}

bool RoundButton::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::MouseButtonRelease:
        {
            const QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *> (event);
            bool inside = rect ().contains (mouseEvent->pos ());
            if ((mouseEvent->button () == Qt::LeftButton) && inside)
            {
                emit clicked ();
            }
        }
        break;
    default:
        break;
    }
    return QWidget::event (event);
}

void RoundButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);

    QPainter painter (this);
    painter.setRenderHints (QPainter::Antialiasing | QPainter::TextAntialiasing);

    qreal height = this->height ();
    qreal width = this->width ();
    QPointF center (width / 2, height / 2);

    qreal radius = (height > width) ? width : height;
    radius /= 2;

    QRectF rect = this->rect ();
    rect.setTop (center.y () - radius);
    rect.setBottom (center.y () + radius);

    painter.setPen (Qt::NoPen);
    painter.setBrush (QBrush (m_color));
    painter.drawRoundedRect (rect, radius, radius);

    if (m_alignment & AlignLeft)
    {
        QRectF leftRect (rect);
        leftRect.setRight (center.x ());
        painter.drawRect (leftRect);
    }

    if (m_alignment & AlignRight)
    {
        QRectF rightRect (rect);
        rightRect.setLeft (center.x ());
        painter.drawRect (rightRect);
    }

#ifdef ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE
    // dynamic font size derived from:
    // For Qt 4.6.x, how to auto-size text to fit in a specified width?
    // http://stackoverflow.com/a/2204501
    // which was in turn derived from:
    // For Qt 4.6.x, how to auto-size text to fit in a specified width?
    // http://www.qtcentre.org/threads/27839-For-Qt-4-6-x-how-to-auto-size-text-to-fit-in-a-specified-width

    QFont font = painter.font ();
    qreal yFactor = width / qreal (painter.fontMetrics ().width (m_text));
    qreal xFactor = height / qreal (painter.fontMetrics ().height ());
    qreal factor = (yFactor > xFactor) ? xFactor : yFactor;
    factor *= m_textSizeRatio;
    font.setPointSizeF (font.pointSizeF () * factor);
    painter.setFont (font);
#endif // ROUNDBUTTON_USE_DYNAMIC_FONT_SIZE

    painter.setPen (QPen (m_textColor));

    // test
    // painter.drawText (rect, Qt::AlignVCenter | m_alignment , m_text);
    painter.drawText (rect, Qt::AlignCenter, m_text);
}
