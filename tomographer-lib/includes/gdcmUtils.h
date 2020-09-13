#ifndef __gdcm_utils
#define __gdcm_utils
#include <gdcmDirectory.h>
#include <gdcmDataSet.h>
#include <list>

namespace GdcmUtils {
const gdcm::Directory GetDirectory(const std::string directoryPath);
gdcm::Directory::FilenamesType GetRawFilesList(const char* _path);
bool FileHasTags(const gdcm::DataSet& ds);
std::list<gdcm::Directory::FilenameType> FilterListByBeingValidDicomAndHavingTags(gdcm::Directory::FilenamesType rawFileList);
}
#endif
