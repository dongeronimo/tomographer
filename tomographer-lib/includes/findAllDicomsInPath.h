#ifndef __find_all_dicom_in_path
#define __find_all_dicom_in_path
#include "dicomFileVO.h"

namespace tomographer {
//    void FindAllDicomsInPath(const char* _path,
//                             int* outNumberOfFiles,
//                             DicomFileVO* outFiles);
    void FindAllDicomsInPath(const char* _path, DicomFileVOList* list);
}
#endif
