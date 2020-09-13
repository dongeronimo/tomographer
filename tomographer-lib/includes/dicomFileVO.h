#ifndef _dicom_file_vo
#define _dicom_file_vo

struct DicomFileVO;

struct DicomFileVOList{
    int length;
    DicomFileVO* first;
};

///A struct that carries the mininum information about an image slice.
struct DicomFileVO {
    const char* filepath;
    const char* patient;
    const char* study;
    const char* series;
    float imagePosition[3];
    float directionCosines[6];
    float spacing[3];
    int cols;
    int rows;
    const char* scalarType;
    int bufferSize;
    char* imageBuffer;
};
#endif
