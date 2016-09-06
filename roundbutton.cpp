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
    m_alignment = Qt::AlignHCenter;
    m_textSizeRatio = 1.0;
}

RoundButton::~RoundButton()
{

}

void RoundButton::setColor(const QColor &color)
{
    m_color = color;
}

QColor RoundButton::color() const
{
    return m_color;
}

void RoundButton::setTextColor(const QColor &color)
{
    m_textColor = color;
}

QColor RoundButton::textColor() const
{
    return m_textColor;
}

void RoundButton::setText(const QString &text)
{
    m_text = text;
}

QString RoundButton::text() const
{
    return m_text;
}

void RoundButton::setTextSizeRatio(const qreal ratio)
{
    m_textSizeRatio = ratio;
}

qreal RoundButton::textSizeRatio() const
{
    return m_textSizeRatio;
}

void RoundButton::setAlignment(Qt::AlignmentFlag alignment)
{
    int horizontalAlignment = Qt::AlignLeft | Qt::AlignRight | Qt::AlignHCenter;
    if (! (horizontalAlignment & alignment))
    {
        alignment = Qt::AlignHCenter;
    }
    m_alignment = alignment;
}

Qt::AlignmentFlag RoundButton::alignment() const
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
    painter.setRenderHint (QPainter::Antialiasing);

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

    QRectF coverRect (rect);
    switch (m_alignment)
    {
    case Qt::AlignLeft:
        {
            coverRect.setRight (center.x ());
            painter.drawRect (coverRect);
        }
        break;
    case Qt::AlignRight:
        {
            coverRect.setLeft (center.x ());
            painter.drawRect (coverRect);
        }
        break;
    default:
        break;
    }

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
    painter.setPen (QPen (m_textColor));

    // test
    // painter.drawText (rect, Qt::AlignVCenter | m_alignment , m_text);
    painter.drawText (rect, Qt::AlignCenter , m_text);
}
