#include <string>
#include <sstream>
#include <memory>
#include <list>
#include <iostream>
#include <algorithm>
#include <thread>

#include <gdcmReader.h>
#include <gdcmWriter.h>
#include <gdcmAttribute.h>
#include <gdcmSorter.h>
#include <gdcmIPPSorter.h>
#include <gdcmScanner.h>
#include <gdcmDataSet.h>
#include <gdcmAttribute.h>
#include <gdcmImageReader.h>

#include "tomographer.h"
#include "dicomTags.h"
#include "findAllDicomsInPath.h"
#include "LibraryContext.h"
#include "stringUtils.h"
#include "gdcmUtils.h"
#include "datasetUtils.h"
#include "readDicoms.h"

std::unique_ptr<DicomFilesReader> readerContext;

void __cdecl BeginImageLoad(const char* dirpath)
{
    readerContext.reset(new DicomFilesReader(dirpath));
}
int __cdecl GetNumberOfFiles()
{
    return readerContext->GetNumberOfFiles();
}
DicomFileVO __cdecl GetFile(int id)
{
    DicomFileVO vo;
    vo.bufferSize = -1;
    return vo;
}
void __cdecl EndImageLoad()
{
    DicomFilesReader* ptrToDelete = readerContext.release();
    delete ptrToDelete;
}


int main(int argc, char** argv)
{
        std::thread t([](){
            while(true)
            {
                BeginImageLoad("C:/dicoms/Marching Man");
                int numberOfImages = GetNumberOfFiles();
                EndImageLoad();
            }
        });
        t.join();
        return 0;


}
//gdcm::File CreateFile(gdcm::Directory::FilenameType& filename){
//    gdcm::Reader reader;
//    reader.SetFileName(filename.c_str());
//    reader.Read();
//    auto file = reader.GetFile();
//    return file;
//}

//std::list<gdcm::Directory::FilenameType> filesFoundInDir;
//void __cdecl BeginImageLoad(const char* _path)
//{
//    filesFoundInDir.clear();
//    //1)Lê o diretório
//    gdcm::Directory::FilenamesType rawFileList = GdcmUtils::GetRawFilesList(_path);
//    std::list<gdcm::Directory::FilenameType> filesWithNeededTags = GdcmUtils::FilterListByBeingValidDicomAndHavingTags(rawFileList);
//    //2)Guarda na lista
//    for(auto i=filesWithNeededTags.begin(); i!=filesWithNeededTags.end(); ++i)
//    {
//        gdcm::Directory::FilenameType currentFilename = *i;
//        filesFoundInDir.push_back(currentFilename);
//    }
//}
//int __cdecl GetNumberOfImages()
//{
//    return filesFoundInDir.size();
//}
//void __cdecl GetImageList(DicomFileVO* voList)
//{
//    std::list<DicomFileVO> files;
//    std::transform(filesFoundInDir.begin(), filesFoundInDir.end(),
//                          std::back_inserter(files), [](gdcm::Directory::FilenameType& current){
////        gdcm::File currentFile = CreateFile(current);
////        gdcm::DataSet& dataset = currentFile.GetDataSet();
////        std::string name = GdcmUtils::GetPatientFromDataset(dataset);
////        std::string study = GdcmUtils::GetStudyFromDataset(dataset);
////        std::string series = GdcmUtils::GetSeriesFromDataset(dataset);
////        std::array<float, 6> directionCosines = GdcmUtils::GetDirectionCosinesFromDataset(dataset);
////        std::array<float, 3> imagePosition = GdcmUtils::GetImagePositionFromDataset(dataset);
//        //Fill the VO
//        DicomFileVO newVo;
//        newVo.filepath = current.c_str();
//        return newVo;
//    });
//    //Fill the output pointer
//    int counter = 0;
//    std::for_each(files.begin(), files.end(), [&counter, &voList](DicomFileVO& current){
//        voList[counter] = current;
//        counter++;
//    });
//    //std::back_inserter(filesWithNeededTags),
//}
//DllExport void __cdecl EndImageLoad()
//{
//    //1)Limpa o que foi preparado pra leitura do diretório
//    filesFoundInDir.clear();
//}


//void FillSomeData(unsigned int amount, SomeData* outData)
//{
//    for(unsigned int i=0; i < amount; i++)
//    {
//        std::stringstream ss;
//        ss<<"Foobar "<<i;
//        outData[i].value = StringUtils::CloneStringFromStringstream(ss);
//        outData[i].id = i;
//    }
//}

//bool CanReadDicomFileWithGDCM(const char * file)
//{
//    gdcm::Reader reader;
//    reader.SetFileName(file);
//    return reader.Read();
//}

////void __cdecl FindAllDicomsInPath(const char* _path, int* outNumberOfFiles, DicomFileVO* outFiles)
//void __cdecl FindAllDicomsInPath(const char* _path, DicomFileVOList* fileList)
//{
//    DicomFileVOList dicoms;
//    tomographer::FindAllDicomsInPath(_path, &dicoms);
//    fileList->first = dicoms.first;
//    fileList->length = dicoms.length;
//}


//int main(int argc, char** argv)
//{
//    std::thread t([](){
//        while(true)
//        {
//            BeginImageLoad("C:/dicoms/Marching Man");
//            int numberOfImages = GetNumberOfImages();
//            DicomFileVO* files = new DicomFileVO[numberOfImages];
//            GetImageList(files);
//            EndImageLoad();
//            for(int i=0; i<numberOfImages; i++){
//                std::cout<<files[i].filepath<<std::endl;
//            }
//            std::cout<<"---------------------"<<std::endl;
//            delete[] files;
//        }

//    });
//    t.join();
//    return 0;
////    int x = 0;
////    DicomFileVOList lst;
////    FindAllDicomsInPath("C:/dicoms/Marching Man", &lst);
////    std::cout<<lst.length<<std::endl;
////    std::cout<<lst.first<<std::endl;
//}
////std::unique_ptr<LibraryContext> libraryContext;

////int TestSimpleParameters(int p0, int p1){
////    return p0 + p1;
////}

////int TestStringParameters(const char* myStr){
////    std::string s(myStr);
////    return s.length();
////}

////SomeData* TestGetStruct(int amount){
////    SomeData* listOfDatas = new SomeData[amount];//Allocate
////    for(auto i=0; i<amount; i++){//Fill with something
////        auto currentData = listOfDatas[i];
////        currentData.id = i;
////        std::stringstream ss;
////        ss<<"my value is "<<i;
////        currentData.value = CloneStringFromStringstream(ss);
////    }
////    return listOfDatas;//Returns the pointer to allocated memory
////}
////void FreePointer(void* addr){
////    free(addr);
////}
////void TestCallback(SimpleCallback cbk){
////    for(auto i=0; i<10; i++){
////        cbk(static_cast<float>(i)/10.0f);
////    }
////}

////void InitializeLibrary(){
////    libraryContext.reset(new LibraryContext());
////}

////void FinalizeLibrary(){
////    libraryContext.release();
////}

////int DoSomethingWithTheContext(){
////    libraryContext->TestIncrement();
////    return libraryContext->TestCounter();
////}


