#include "datasetUtils.h"
#include <gdcmAttribute.h>

namespace GdcmUtils {
std::string GetPatientFromDataset(const gdcm::DataSet &ds)
{
    gdcm::Attribute<0x0010,0x0010> patientNameAttr;
    patientNameAttr.Set(ds);
    std::string name = patientNameAttr.GetValue();
    return name;
}
std::string GetStudyFromDataset(const gdcm::DataSet &dataset)
{
    gdcm::Attribute<0x0020,0x000d> studyAttr;
    studyAttr.Set(dataset);
    std::string study = studyAttr.GetValue();
    return study;
}
std::string GetSeriesFromDataset(const gdcm::DataSet &dataset)
{
    gdcm::Attribute<0x0020,0x000e> seriesAttr;
    seriesAttr.Set(dataset);
    std::string series = seriesAttr.GetValue();
    return series;
}
std::array<float, 6> GetDirectionCosinesFromDataset(const gdcm::DataSet &dataset)
{
    gdcm::Attribute<0x0020,0x0037> dcAttr;
    dcAttr.Set(dataset);
    std::array<float, 6> arr;
    arr[0] = dcAttr[0];
    arr[1] = dcAttr[1];
    arr[2] = dcAttr[2];
    arr[3] = dcAttr[3];
    arr[4] = dcAttr[4];
    arr[5] = dcAttr[5];
    return arr;
}
std::array<float, 3> GetImagePositionFromDataset(const gdcm::DataSet &dataset)
{
    gdcm::Attribute<0x0020,0x0032> ipAttr;
    ipAttr.Set(dataset);
    std::array<float, 3> arr;
    arr[0] = ipAttr[0];
    arr[1] = ipAttr[1];
    arr[2] = ipAttr[2];
    return arr;
}
}
