#include "lef_graphic.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <math.h>

LEF_Graphic::LEF_Graphic(QWidget *parent) : QWidget(parent)
{
    setFixedSize(3000, 3000);
    setStyleSheet("background-color: transparent");

}

void LEF_Graphic::fill(LEF::Macro * pLefObject)
{
    isActiveLayers.clear();
    lef_object = pLefObject;
}

void LEF_Graphic::autoScaling()
{
    //Auto-scaling
    if(lef_object){
    gScale = std::min((width()-gOffset)/lef_object->width, (height()-gOffset) / lef_object->height);
    }
}

void LEF_Graphic::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    if(lef_object){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawPins(painter);
    drawContour(painter);
    drawObs(painter);

    }
}

void LEF_Graphic::drawObs(QPainter & painter){
    for (int i = 0; i < lef_object->obs.size(); i++)
    {
        if (isActiveLayers[lef_object->obs[i].layerName]){
            QColor penColor = lef_object->mapLayers[lef_object->obs[i].layerName];
            Qt::PenStyle penStyle = Qt::SolidLine;
            int lineWidth = 1;
            QPen pen(penColor, lineWidth, penStyle);
            painter.setPen(pen);

            QColor brushColor(Qt::transparent);
            painter.setBrush(brushColor);
            drawRectangle(lef_object->obs[i].OBSRect, painter);

            drawHatchRect(lef_object->obs[i].OBSRect, 10, 120, painter);
        }
    }
}

void LEF_Graphic::drawRectangle(Rect & rect, QPainter & painter){


    QPoint startPoint(rect.pt1.x * gScale + gOffset, rect.pt1.y * gScale + gOffset);
    QPoint endPoint(rect.pt2.x * gScale + gOffset,rect.pt2.y * gScale + gOffset);
    int width = qAbs(endPoint.x() - startPoint.x());
    int height = qAbs(endPoint.y() - startPoint.y());

    painter.drawRect(QRect(startPoint, QSize(width, height)));


}

void LEF_Graphic::drawContour(QPainter & painter){
    // Set the pen properties (color and line density)
    QColor penColor(Qt::green);
    Qt::PenStyle penStyle = Qt::SolidLine;
    int lineWidth = 1;
    QPen pen(penColor, lineWidth, penStyle);
    painter.setPen(pen);

    // Set the brush color for the rectangle
    QColor brushColor(Qt::transparent);
    painter.setBrush(brushColor);

    //qDebug() << gScale;
    QPoint startPoint(lef_object->origin.x * gScale + gOffset,lef_object->origin.y * gScale + gOffset);
    int width = lef_object->width * gScale;
    int height = lef_object->height * gScale;

    painter.drawRect(QRect(startPoint, QSize(width, height)));

}

void LEF_Graphic::drawPins(QPainter & painter)
{
    for(int i = 0; i < lef_object->pin_array.size(); i++)
        for (int j = 0; j < lef_object->pin_array[i].port_array.size(); j++) {
            QString layer(QString::fromStdString(lef_object->pin_array[i].port_array[j].pin_layer.name));
            if(isActiveLayers[layer])
            {
                QColor layer_color = lef_object->mapLayers[layer];
                //qDebug() << layer_color;

                QColor penColor(layer_color);
                Qt::PenStyle penStyle = Qt::SolidLine;
                int lineWidth = 1;
                QPen pen(penColor, lineWidth, penStyle);
                painter.setPen(pen);

                // Set the brush color for the rectangle
                QColor brushColor(layer_color);
                painter.setBrush(brushColor);

                QPoint startPoint(lef_object->pin_array[i].port_array[j].port_rect.pt1.x * gScale + gOffset,lef_object->pin_array[i].port_array[j].port_rect.pt1.y * gScale + gOffset);
                QPoint endPoint(lef_object->pin_array[i].port_array[j].port_rect.pt2.x * gScale + gOffset,lef_object->pin_array[i].port_array[j].port_rect.pt2.y * gScale + gOffset);
                int width = qAbs(endPoint.x() - startPoint.x());
                int height = qAbs(endPoint.y() - startPoint.y());

                painter.drawRect(QRect(startPoint, QSize(width, height)));
            }

        }
}

void LEF_Graphic::simpleLineClipping(Rect& rect, Vector2f* vect1, Vector2f* vect2)
{
    float xmin = std::min(gScale * (float)rect.pt1.x + gOffset, gScale * (float)rect.pt2.x + gOffset);
    float ymin = std::min(gScale * (float)rect.pt1.y + gOffset, gScale * (float)rect.pt2.y + gOffset);
    float xmax = std::max(gScale * (float)rect.pt1.x + gOffset, gScale * (float)rect.pt2.x + gOffset);
    float ymax = std::max(gScale * (float)rect.pt1.y + gOffset, gScale * (float)rect.pt2.y + gOffset);
    float x1 = vect1->x;
    float y1 = vect1->y;
    float x2 = vect2->x;
    float y2 = vect2->y;
    float x[2] = {0};
    float y[2] = {0};

    if (!((x1 < xmin) && (x2 < xmin)) && !((x1 > xmax) && (x2 > xmax)))
    {
        if (!((y1 < ymin) && (y2 < ymin)) && !((y1 > ymax) && (y2 > ymax)))
        {
            x[0] = x1;
            y[0] = y1;
            x[1] = x2;
            y[1] = y2;
            int j = 0;
            do {
                if (x[j] < xmin) {
                    x[j] = xmin;
                    y[j] = ((y2 - y1) / (x2 - x1)) * (xmin - x1) + y1;
                }
                else if (x[j] > xmax) {
                    x[j] = xmax;
                    y[j] = ((y2 - y1) / (x2 - x1)) * (xmax - x1) + y1;
                }
                if (y[j] < ymin) {
                    y[j] = ymin;
                    x[j] = ((x2 - x1) / (y2 - y1)) * (ymin - y1) + x1;
                }
                else if (y[j] > ymax) {
                    y[j] = ymax;
                    x[j] = ((x2 - x1) / (y2 - y1)) * (ymax - y1) + x1;
                }
                j++;

            } while (j < 2);
        }
    }
    vect1->x = x[0];
    vect1->y = y[0];
    vect2->x = x[1];
    vect2->y = y[1];
}

void LEF_Graphic::drawHatchRect(Rect& rect, uint8_t step, uint8_t angle, QPainter & painter)
{
    Vector2f startPoint( gScale * (float)rect.pt1.x + gOffset, gScale * (float)rect.pt1.y + gOffset );
    Vector2f endPoint(   gScale * (float)rect.pt2.x + gOffset, gScale * (float)rect.pt2.y + gOffset );
    Vector2f rectSize(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
    Vector2f center = { startPoint.x + rectSize.x / 2,  startPoint.y + rectSize.y / 2 };
    float diag = sqrtf(rectSize.x * rectSize.x + rectSize.y * rectSize.y);

    //TODO: How to calculate this number?
    const uint8_t magic_number_lines = 10;
    int j = -magic_number_lines;
    for (int i = 0; i < ((rectSize.y / step) + 2*magic_number_lines); i++)
    {
        Vector2f lineStartPoint( center.x - diag / 2 , startPoint.y + (step * j++));
        Vector2f lineEndPoint( center.x + diag / 2,  lineStartPoint.y );
        rotateCoordinates(lineStartPoint.x, lineStartPoint.y, center.x, center.y, angle);
        rotateCoordinates(lineEndPoint.x, lineEndPoint.y, center.x, center.y , angle);
        simpleLineClipping(rect, &lineStartPoint, &lineEndPoint);

        QPoint startPoint(lineStartPoint.x, lineStartPoint.y);
        QPoint endPoint(lineEndPoint.x, lineEndPoint.y);

        painter.drawLine(startPoint, endPoint);
    }
}


void LEF_Graphic::onCheckBoxStateChanged(int state)
{
    QCheckBox* checkBox = qobject_cast<QCheckBox*>(QWidget::sender());
    QString idValue = checkBox->property("id").toString();
    if (state == Qt::Checked) {
        qDebug() << "Check box ID:" << idValue << "state : on";
        isActiveLayers[idValue] = true;
        repaint();
    } else if (state == Qt::Unchecked) {
        qDebug() << "Check box ID:" << idValue << "state : off";
        isActiveLayers[idValue] = false;
        repaint();
    }
}

void LEF_Graphic::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    QPoint pos = mouseEvent->pos();
    //qDebug() << QString::number(pos.x()) << QString::number(pos.y());
    QString message;
    message += "Coordinates: ";
    message += QString::number((pos.x() - gOffset) / gScale - lef_object->origin.x);
    message += " ";
    message += QString::number((pos.y() - gOffset) / gScale - lef_object->origin.y);
    emit statusBarSignaltoMainWgt(message);

//    QWidget* grand =parentWidget() -> parentWidget();
//    QString mes = "Parent";
//    (qobject_cast<MainWindow*>(grand) ) -> statusBarMessage(mes);
}

void LEF_Graphic::wheelEvent(QWheelEvent *event){
    // Обработка движения колесика мышки
    if (event->angleDelta().y() > 0) {
        // Увеличение масштаба при движении вверх
        gScale += 0.1f;
    }
    else if (event->angleDelta().y() < 0) {
        // Уменьшение масштаба при движении вниз
        gScale -= 0.1f;
    }

    // Защита от отрицательного масштаба
    if (gScale < 0.1f) {
        gScale = 0.1f;
    }
    // Перерисовываем содержимое
    repaint();
    event->accept();
}

void LEF_Graphic::rotateCoordinates(float& x, float& y, float cx, float cy, float angle) {
    // Переводим координаты в систему относительно точки (cx, cy)
    float relX = x - cx;
    float relY = y - cy;

    // Выполняем поворот координат
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    float newX = relX * cosAngle - relY * sinAngle;
    float newY = relX * sinAngle + relY * cosAngle;

    // Возвращаем координаты в исходную систему
    x = newX + cx;
    y = newY + cy;
}


