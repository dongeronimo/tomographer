#ifndef __read_dicoms
#define __read_dicoms
#include <string>
#include <vector>
#include <gdcmDirectory.h>
#include <gdcmFile.h>
#include <gdcmImage.h>
class DicomFilesReader
{
private:
    std::string directoryPath;

    std::vector<gdcm::Directory::FilenameType> filepathsList;
    std::vector<gdcm::File> filesList;
    std::vector<gdcm::Image> imagesList;

    void GetValidFilepaths();
    void CreateGdcmFilesAndImagesObjects();
public:
    DicomFilesReader(const char* dirpath);
    int GetNumberOfFiles();
};

#endif
