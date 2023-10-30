#include "dataset.h"

DataSet::DataSet()
{

}

void DataSet::readMacro()
{
    reader.AssignFilePath();
    reader.WriteDatatoObject(macro);
}
