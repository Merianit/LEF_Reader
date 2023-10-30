﻿
#include <iostream>
#include <QtWidgets>
#include <QFileDialog>

#include "LEF.h"
#include "Macro.h"
#include "Reader.h"
#include "Port.h"
#include "Pin.h"
#include "Obs.h"


namespace LEF {
    void Reader::AssignFilePath()
    {
        //std::cout << "Reader()" << std::endl;
        QString filePath = QFileDialog::getOpenFileName(nullptr, "Выберите файл", "", "LEF Files (*.lef)");

        if (!filePath.isEmpty())
        {
            qDebug() << "Выбран файл: " << filePath;
        }
        else
        {
            qDebug() << "Файл не выбран.";
        }
        path = filePath.toStdString();
        file.open(path);
        if (!file) {
            std::cout << "file error!" << std::endl;
            exit(1);
        }
        file.close();
    }

    uint8_t Reader::WriteDatatoObject(LEF::Macro& dest_lef)
    {
        file.open(path);
        std::string lef_string;
        file >> lef_string;

        while (!lef_string.empty())
        {
            if (lef_string == "MACRO") {
                file >> lef_string;
                dest_lef.name = lef_string;
            }
            else if (lef_string == "ORIGIN") {
                double x, y;
                file >> x >> y;
                dest_lef.origin.x = x;
                dest_lef.origin.y = y;
            }

            else if (lef_string == "SIZE") {
                double width, height;
                file >> width >> lef_string >> height;
                dest_lef.width = width;
                dest_lef.height = height;
            }
            else if (lef_string == "PIN") {
                dest_lef.number_of_pins++;
                LEF::Pin temp_pin;
                file >> lef_string;
                temp_pin.name = lef_string;
                file >> lef_string;
                if (lef_string == "DIRECTION") {
                    file >> lef_string;
                    temp_pin.direction = lef_string;
                }
                file >> lef_string;
                if (lef_string == "TRISTATE")
                {
                    temp_pin.direction = "OUTPUT_TRISTATE";
                    file >> lef_string;
                }
                file >> lef_string;
                if (lef_string == "USE") {
                    file >> lef_string;
                    temp_pin.type = lef_string;
                }

                dest_lef.pin_array.push_back(temp_pin);
            }
            else if (lef_string == "PORT") {
                dest_lef.pin_array.back().number_of_ports++;
                LEF::Port temp_port;
                file >> lef_string;
                if (lef_string == "LAYER") {
                    file >> lef_string;
                    temp_port.pin_layer.name = lef_string;
                    dest_lef.mapLayers.insert(QString::fromStdString(lef_string), Qt::red);
                }
                file >> lef_string;
                file >> lef_string;
                if (lef_string == "RECT") {
                    file >> temp_port.port_rect.pt1.x >> temp_port.port_rect.pt1.y >> temp_port.port_rect.pt2.x >> temp_port.port_rect.pt2.y;
                }
                dest_lef.pin_array.back().port_array.push_back(temp_port);
            }
            else if (lef_string == "OBS") {
                Obs obs;
                while (lef_string != "END")
                {
                    file >> lef_string;
                    if (lef_string == "LAYER") {
                        file >> lef_string;
                        dest_lef.mapLayers.insert(QString::fromStdString(lef_string), Qt::blue);
                        obs.layerName = QString::fromStdString(lef_string);
                        file >> lef_string;
                    }
                    if (lef_string == "RECT") {

                        file >> obs.OBSRect.pt1.x >> obs.OBSRect.pt1.y >> obs.OBSRect.pt2.x >> obs.OBSRect.pt2.y;
                        dest_lef.obs.push_back(obs);
                    }
                }
            }
            lef_string.clear();
            file >> lef_string;
        }
        file.close();
        return 1;
    }
};
