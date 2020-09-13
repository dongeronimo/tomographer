#include <array>
#include <string>
#include <list>
#include <algorithm>
#include <gdcmReader.h>
#include <gdcmWriter.h>
#include <gdcmAttribute.h>
#include <gdcmSorter.h>
#include <gdcmIPPSorter.h>
#include <gdcmScanner.h>
#include <gdcmDataSet.h>
#include <gdcmAttribute.h>
#include <gdcmImageReader.h>
#include "findAllDicomsInPath.h"
#include "dicomTags.h"
#include "stringUtils.h"
#include "gdcmUtils.h"
#include "datasetUtils.h"

void tomographer::FindAllDicomsInPath(const char* _path, DicomFileVOList* list)
{
    gdcm::Directory::FilenamesType rawFileList = GdcmUtils::GetRawFilesList(_path);
    std::list<gdcm::Directory::FilenameType> filesWithNeededTags = GdcmUtils::FilterListByBeingValidDicomAndHavingTags(rawFileList);

    DicomFileVO* lst = new DicomFileVO[filesWithNeededTags.size()];
    int counter = 0;
    for(auto i=filesWithNeededTags.begin(); i!=filesWithNeededTags.end(); ++i)
    {
        gdcm::Directory::FilenameType currentFilename = *i;
        gdcm::Reader tagsReader;
        tagsReader.SetFileName(currentFilename.c_str());
        tagsReader.Read();
        gdcm::File currentFile = tagsReader.GetFile();
        gdcm::DataSet& dataset = currentFile.GetDataSet();
        std::string name = GdcmUtils::GetPatientFromDataset(dataset);
        std::string study = GdcmUtils::GetStudyFromDataset(dataset);
        std::string series = GdcmUtils::GetSeriesFromDataset(dataset);
        std::array<float, 6> directionCosines = GdcmUtils::GetDirectionCosinesFromDataset(dataset);
        std::array<float, 3> imagePosition = GdcmUtils::GetImagePositionFromDataset(dataset);
        //Get the image
        gdcm::ImageReader imageReader;
        imageReader.SetFileName(currentFilename.c_str());
        if(imageReader.Read())
        {
            gdcm::Image& image = imageReader.GetImage();
            auto cols = image.GetColumns();
            auto rows = image.GetRows();
            float spacing[] = {(float)image.GetSpacing(0),
                               (float)image.GetSpacing(1),
                               (float)image.GetSpacing(2)};
            auto bufferSize = image.GetBufferLength();
            std::string scalarType(image.GetPixelFormat().GetScalarTypeAsString());
            char* buffer = new char[bufferSize];
            image.GetBuffer(buffer);
            //Everything is here - time to fill the struct
            lst[counter].filepath = StringUtils::StringToCstr(currentFilename);
            lst[counter].patient = StringUtils::StringToCstr(name);
            lst[counter].study = StringUtils::StringToCstr(study);
            lst[counter].series = StringUtils::StringToCstr(series);
            std::memcpy(lst[counter].imagePosition, imagePosition.data(), sizeof(float)*3);
            std::memcpy(lst[counter].directionCosines, directionCosines.data(), sizeof(float)*6);
            std::memcpy(lst[counter].spacing, spacing, sizeof(float)*3);
            lst[counter].cols = cols;
            lst[counter].rows = rows;
            lst[counter].scalarType = StringUtils::StringToCstr(scalarType);
            lst[counter].bufferSize = bufferSize;
            lst[counter].imageBuffer = buffer;
            counter++;
        }
        else
        {
            //TODO:Maybe a better way to deal with errors?
            throw "Could not read file "+currentFilename;
        }
    }
    auto numberOfElements = filesWithNeededTags.size();
    list->first = lst;
    list->length = numberOfElements;
}
