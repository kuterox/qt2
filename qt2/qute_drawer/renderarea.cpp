#include <QtGui>

#include "renderarea.h"
#include <QSizePolicy>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    shape = Rect;
    antialiased = false;
    transformed = false;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::setShape(Shape shape)
{
    this->shape = shape;
}

void RenderArea::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}

void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

void RenderArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

void RenderArea::setTransformed(bool transformed)
{
    this->transformed = transformed;
    update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QRect rect(start,end);

    int startAngle = 30 * 16;
    int arcLength = 120 * 16;

    if (!painter.isActive())
        painter.begin(this);
    
    painter.setPen(pen);
    painter.setBrush(brush);
    if (antialiased) {
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.translate(+0.5, +0.5);
    }
    
    switch (shape) {
    case Line:
        painter.drawLine(start, end);
        break;
    case Rect:
        painter.drawRect(rect);
        break;
    case RoundRect:
        painter.drawRoundRect(rect);
        break;
    case Ellipse:
        painter.drawEllipse(rect);
        break;
    case Arc:
        painter.drawArc(rect, startAngle, arcLength);
        break;
    case Chord:
        painter.drawChord(rect, startAngle, arcLength);
        break;
    case Pie:
        painter.drawPie(rect, startAngle, arcLength);
        break;
    }

    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::mousePressEvent ( QMouseEvent * e )
{
    start = e->pos();    
}

void RenderArea::mouseReleaseEvent ( QMouseEvent * e )
{    
    end = e->pos();
    update();
}