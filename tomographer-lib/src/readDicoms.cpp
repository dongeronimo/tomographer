#include "readDicoms.h"
#include "gdcmUtils.h"
#include <algorithm>
#include <gdcmReader.h>
#include <gdcmImageReader.h>
gdcm::File CreateFile(gdcm::Directory::FilenameType& filename){
    gdcm::Reader reader;
    reader.SetFileName(filename.c_str());
    reader.Read();
    auto file = reader.GetFile();
    return file;
}
gdcm::Image CreateImage(gdcm::Directory::FilenameType& filename){
    gdcm::ImageReader imageReader;
    imageReader.SetFileName(filename.c_str());
    auto image = imageReader.GetImage();
    return image;
}
DicomFilesReader::DicomFilesReader(const char *dirpath)
    :directoryPath(dirpath)
{
    GetValidFilepaths();
}

int DicomFilesReader::GetNumberOfFiles()
{
    return filepathsList.size();
}

void DicomFilesReader::GetValidFilepaths()
{
    //Get the raw file list with everything in the directory
    gdcm::Directory::FilenamesType rawFileList = GdcmUtils::GetRawFilesList(this->directoryPath.c_str());
    //Filter the list, only dicom files with the tags that I need will remain
    std::list<gdcm::Directory::FilenameType> filesWithNeededTags = GdcmUtils::FilterListByBeingValidDicomAndHavingTags(rawFileList);
    //Fill the valid filepaths list.
    std::transform(filesWithNeededTags.begin(), filesWithNeededTags.end(),
                   std::back_inserter(this->filepathsList),
                   [](gdcm::Directory::FilenameType &current){
        return current;
    });

}

void DicomFilesReader::CreateGdcmFilesAndImagesObjects()
{
    //for each filepath, load the file and the image (these are separate operations!) and store it in
    //their respective lists.
    for(auto filepathIt=filepathsList.begin(); filepathIt!=filepathsList.end(); ++filepathIt)
    {
        auto currentFilePath = *filepathIt;
        gdcm::File currentFile = CreateFile(currentFilePath);
        this->filesList.push_back(currentFile);
        gdcm::Image currentImage = CreateImage(currentFilePath);
        this->imagesList.push_back(currentImage);
    }
    assert(filepathsList.size() == imagesList.size());
    assert(filepathsList.size() == filesList.size());
}
