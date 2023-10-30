// Reader.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include <iostream>
#include "LEF.h"
#include "Macro.h"
#include "Reader.h"

#define GUI 1
//#define CLI 1

#ifdef GUI

#define OFFSET 50

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <cmath>


float gScale;

sf::RenderWindow window(sf::VideoMode({ 1000,1000 }), "LEF Reader");
sf::Font font;

void graphicRenderTask(LEF::Macro& lef_object);
void drawRectangle(Rect& rect, sf::Color outline, sf::Color fill);
void drawMacroContour(LEF::Macro& lef_object);
void drawMyText(std::string& string, uint32_t size, Point& position);
void drawHatchRect(Rect& rect, uint8_t step, uint8_t angle, sf::Color color);

void mouseWhellEvent_Handler(sf::Event& event);

int main()
{
    window.clear(sf::Color::White);

    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
    window.setView(view);

    if (!font.loadFromFile("OpenSans-Bold.ttf")) {
        // ��������� ������ �������� ������
        exit(0);
    }

    LEF::Reader test;
    LEF::Macro lut_s44;
    test.WriteDatatoObject(lut_s44);
    gScale = 1;
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                mouseWhellEvent_Handler(event);
            }
            graphicRenderTask(lut_s44);
        }

    }
    return 0;
}



void graphicRenderTask(LEF::Macro & lef_object)
{
    window.clear(sf::Color::White);
    Point position = { window.getSize().x / 2, 0};
    drawMyText(lef_object.name, 32, position);
    drawMacroContour(lef_object);

    for(int i = 0; i < lef_object.pin_array.size(); i++)
        for (int j = 0; j < lef_object.pin_array[i].port_array.size(); j++) {
            drawRectangle(lef_object.pin_array[i].port_array[j].port_rect, sf::Color::Red, sf::Color::Red);
        }

    for (int i = 0; i < lef_object.obs.obs_rects.size(); i++)
    {
        drawRectangle(lef_object.obs.obs_rects[i], sf::Color::Blue, sf::Color::Transparent);
        drawHatchRect(lef_object.obs.obs_rects[i], 10, 120, sf::Color::Blue);
       
    }

    window.display();
}

void rotateCoordinates(float& x, float& y, float cx, float cy, float angle) {
    // ��������� ���������� � ������� ������������ ����� (cx, cy)
    float relX = x - cx;
    float relY = y - cy;

    // ��������� ������� ���������
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    float newX = relX * cosAngle - relY * sinAngle;
    float newY = relX * sinAngle + relY * cosAngle;

    // ���������� ���������� � �������� �������
    x = newX + cx;
    y = newY + cy;
}

void simpleLineClipping(Rect& rect, sf::Vector2f* vect1, sf::Vector2f* vect2)
{
    float xmin = std::min(gScale * (float)rect.pt1.x + OFFSET, gScale * (float)rect.pt2.x + OFFSET);
    float ymin = std::min(gScale * (float)rect.pt1.y + OFFSET, gScale * (float)rect.pt2.y + OFFSET);
    float xmax = std::max(gScale * (float)rect.pt1.x + OFFSET, gScale * (float)rect.pt2.x + OFFSET);
    float ymax = std::max(gScale * (float)rect.pt1.y + OFFSET, gScale * (float)rect.pt2.y + OFFSET);
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



void drawHatchRect(Rect& rect, uint8_t step, uint8_t angle, sf::Color color)
{
    sf::Vector2f startPoint{ gScale * (float)rect.pt1.x + OFFSET, gScale * (float)rect.pt1.y + OFFSET };
    sf::Vector2f endPoint{   gScale * (float)rect.pt2.x + OFFSET, gScale * (float)rect.pt2.y + OFFSET };
    sf::Vector2f rectSize = endPoint - startPoint;
    sf::Vector2f center = { startPoint.x + rectSize.x / 2,  startPoint.y + rectSize.y / 2 };
    float diag = sqrtf(rectSize.x * rectSize.x + rectSize.y * rectSize.y);

    //TODO: How to calculate this number?
    const uint8_t magic_number_lines = 10;
    int j = -magic_number_lines;
    for (int i = 0; i < ((rectSize.y / step) + 2*magic_number_lines); i++)
    {
        sf::Vector2f lineStartPoint = { center.x - diag / 2 , startPoint.y + (step * j++)};
        sf::Vector2f lineEndPoint =   { center.x + diag / 2,  lineStartPoint.y };
        sf::Vertex line[2];
        rotateCoordinates(lineStartPoint.x, lineStartPoint.y, center.x, center.y, angle);
        rotateCoordinates(lineEndPoint.x, lineEndPoint.y, center.x, center.y , angle);
        simpleLineClipping(rect, &lineStartPoint, &lineEndPoint);
        line[0] = sf::Vertex(lineStartPoint, color);
        line[1] = sf::Vertex(lineEndPoint, color);
        window.draw(line, 2, sf::Lines);
    }


}

void drawMyText(std::string& string, uint32_t size, Point& position)
{
    sf::Text text;
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x, position.y);
    window.draw(text);
}

void drawMacroContour(LEF::Macro& lef_object)
{
    sf::Vector2f startPoint{ gScale * (float)lef_object.origin.x + OFFSET, gScale * (float)lef_object.origin.y + OFFSET };
    sf::Vector2f endPoint{ gScale * (float)lef_object.width + OFFSET, gScale * (float)lef_object.height + OFFSET };
    sf::Vector2f rectSize = endPoint - startPoint;
    sf::RectangleShape rectangle(rectSize);
    rectangle.setPosition(startPoint);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color::Green);
    rectangle.setFillColor(sf::Color::Transparent);
    window.draw(rectangle);
}

void drawRectangle(Rect& rect, sf::Color outline, sf::Color fill)
{
    sf::Vector2f startPoint{ gScale * (float)rect.pt1.x + OFFSET, gScale * (float)rect.pt1.y + OFFSET };
    sf::Vector2f endPoint{ gScale * (float)rect.pt2.x + OFFSET, gScale * (float)rect.pt2.y + OFFSET };
    sf::Vector2f rectSize = endPoint - startPoint;
    sf::RectangleShape port_rectangle(rectSize);
    port_rectangle.setPosition(startPoint);
    port_rectangle.setOutlineThickness(2);
    port_rectangle.setOutlineColor(outline);
    port_rectangle.setFillColor(fill);
    window.draw(port_rectangle);
}

void mouseWhellEvent_Handler(sf::Event & event)
{
    // ��������� �������� �������� �����
    if (event.mouseWheelScroll.delta > 0) {
        // ���������� �������� ��� �������� �����
        gScale += 0.1f;
    }
    else if (event.mouseWheelScroll.delta < 0) {
        // ���������� �������� ��� �������� ����
        gScale -= 0.1f;
    }

    // ������ �� �������������� ��������
    if (gScale < 0.1f) {
        gScale = 0.1f;
    }
    sf::Text text;
    text.setFont(font);
    std::string str = "Scale: ";
    str += std::to_string((int)(gScale * 100));
    str += '%';
    text.setString(str);
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::Black);
    text.setPosition(800.f, 0.f);
    window.draw(text);
    window.display();
    sf::sleep(sf::seconds(0.1));
}






#endif

#ifdef CLI 
int main()
{
    LEF::Reader test;
    LEF::Macro lut_s44;
    test.WriteDatatoObject(lut_s44);
    lut_s44.show_data();
}
#endif

// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
