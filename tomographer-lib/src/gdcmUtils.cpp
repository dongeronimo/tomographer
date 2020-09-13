#include "gdcmUtils.h"
#include "dicomTags.h"
#include <algorithm>
#include <gdcmReader.h>

const gdcm::Directory GdcmUtils::GetDirectory(const std::string directoryPath)
{
    gdcm::Directory d;
    d.Load(directoryPath.c_str(), true);
    return d;
}

gdcm::Directory::FilenamesType GdcmUtils::GetRawFilesList(const char *_path)
{
    std::string path(_path);
    gdcm::Directory directory = GetDirectory(path);
    gdcm::Directory::FilenamesType rawFileList = directory.GetFilenames();
    return rawFileList;
}

bool GdcmUtils::FileHasTags(const gdcm::DataSet &ds)
{
    bool hasNeededTags = ds.FindDataElement(PatientName) && ds.FindDataElement(StudyInstanceUID)
            && ds.FindDataElement(SeriesInstanceUID) && ds.FindDataElement(ImagePosition)
            && ds.FindDataElement(DirectionCosines);
    return hasNeededTags;
}

std::list<gdcm::Directory::FilenameType> GdcmUtils::FilterListByBeingValidDicomAndHavingTags(gdcm::Directory::FilenamesType rawFileList)
{
    std::list<gdcm::Directory::FilenameType> filesWithNeededTags;
    std::copy_if(rawFileList.begin(), rawFileList.end(),
                 std::back_inserter(filesWithNeededTags),
                 [](const gdcm::Directory::FilenameType& current){
        gdcm::Reader reader;
        reader.SetFileName(current.c_str());
        bool canReadCurrent = reader.Read();
        if(canReadCurrent){
            //If we got here we only know that it is a valid dicom file. It is not guaranteed to be an image
            gdcm::File& file = reader.GetFile();
            gdcm::DataSet& ds = file.GetDataSet();
            return FileHasTags(ds);
        }else{
            return false;
        }
    });
    return filesWithNeededTags;
}
