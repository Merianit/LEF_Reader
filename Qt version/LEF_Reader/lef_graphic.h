#ifndef LEF_GRAPHIC_H
#define LEF_GRAPHIC_H

#include <QWidget>
#include <QtWidgets>
#include "LEF.h"
#include "Macro.h"
#include "Reader.h"
#include "vector2f.h"

class LEF_Graphic : public QWidget
{
    Q_OBJECT
public:
    explicit LEF_Graphic(QWidget *parent = nullptr);
    LEF::Macro* lef_object = nullptr;
    void fill(LEF::Macro * pLefObject);
    void autoScaling();
private:
    float gScale = 3;
    uint8_t gOffset = 50;
    QMap <QString, bool> isActiveLayers;

    void rotateCoordinates(float& x, float& y, float cx, float cy, float angle);

    void wheelEvent(QWheelEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void drawObs(QPainter & painter);

    void drawRectangle(Rect & rect, QPainter & painter);

    void drawContour(QPainter & painter);

    void drawPins(QPainter & painter);

    void simpleLineClipping(Rect& rect, Vector2f* vect1, Vector2f* vect2);

    void drawHatchRect(Rect& rect, uint8_t step, uint8_t angle, QPainter & painter);

public slots:
    void onCheckBoxStateChanged(int state);

signals:
    void statusBarSignaltoMainWgt(QString message);

};

#endif // LEF_GRAPHIC_H
