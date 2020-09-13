#ifndef __tomographer_h
#define __tomographer_h
#ifdef WIN32
    #define DllExport __declspec(dllexport)
#else
    #define DllExport
#endif
#include "dicomFileVO.h"

extern "C" DllExport void __cdecl BeginImageLoad(const char* dirpath);
extern "C" DllExport int __cdecl GetNumberOfFiles();
extern "C" DllExport DicomFileVO __cdecl GetFile(int id);
extern "C" DllExport void __cdecl EndImageLoad();
//#include "dicomFileVO.h"
//struct SomeData
//{
//    int id;
//    const char* value;
//};

//extern "C" DllExport void __cdecl BeginImageLoad(const char* _path);
//extern "C" DllExport int __cdecl GetNumberOfImages();
//extern "C" DllExport void __cdecl GetImageList(DicomFileVO* voList);
//extern "C" DllExport void __cdecl EndImageLoad();
//////Get all dicom files in the given directory. They won't be ordered nor grouped.
//extern "C" DllExport void __cdecl FindAllDicomsInPath(const char* _path, DicomFileVOList* fileList);
//extern "C" DllExport void __cdecl FillSomeData(unsigned int amount, SomeData* outData);
//extern "C" DllExport bool __cdecl CanReadDicomFileWithGDCM(const char* file);
//struct SomeData{
//    int id;
//    const char* value;
//};
//typedef void (*SimpleCallback)(float someParam);

////Demonstrates how to pass as value and get a basic type result
//extern "C" DllExport int TestSimpleParameters(int p0, int p1);
////Demonstrates how to pass strings and get something from them like the size
//extern "C" DllExport int TestStringParameters(const char* myStr);
////Demonstrates how get a list of structs as a function return
//extern "C" DllExport SomeData* TestGetStruct(int amount);
////Demonstrates how to pass a function.
//extern "C" DllExport void TestCallback(SimpleCallback cbk);
////Initializes the library context object.
//extern "C" DllExport void InitializeLibrary();
////Releases the library context object
//extern "C" DllExport void FinalizeLibrary();
////Do something with the context
//extern "C" DllExport int DoSomethingWithTheContext();
////Releases memory allocated in the dll world.
//extern "C" DllExport void FreePointer(void* addr);
#endif
