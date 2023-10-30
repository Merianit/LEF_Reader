#ifndef DATASET_H
#define DATASET_H

#include "LEF.h"
#include "Macro.h"
#include "Reader.h"

class DataSet
{
public:
    DataSet();
    LEF::Reader reader;
    LEF::Macro macro;
    void readMacro();

};

#endif // DATASET_H
