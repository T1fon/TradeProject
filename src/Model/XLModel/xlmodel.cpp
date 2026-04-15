#include "xlmodel.h"

XLModel::XLModel() {}


void XLModel::__extractData(const QString& way)
{

}
void XLModel::__saveData(const QString& way)
{

}

bool XLModel::getData(const QString& way)
{
    __extractData(way);
}
bool XLModel::saveData(const QString& way)
{
    __saveData(way);
}
