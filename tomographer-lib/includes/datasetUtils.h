#ifndef __dataset_utils
#define __dataset_utils
#include <string>
#include <gdcmDataSet.h>
#include <array>
namespace GdcmUtils {
std::string GetPatientFromDataset(const gdcm::DataSet &ds);
std::string GetStudyFromDataset(const gdcm::DataSet &dataset);
std::string GetSeriesFromDataset(const gdcm::DataSet &dataset);
std::array<float, 6> GetDirectionCosinesFromDataset(const gdcm::DataSet &dataset);
std::array<float, 3> GetImagePositionFromDataset(const gdcm::DataSet &dataset);
}
#endif
