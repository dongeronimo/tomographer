#ifndef __dicom_tags_h
#define __dicom_tags_h
#include <gdcmTag.h>
const gdcm::Tag StudyInstanceUID(0x0020,0x000d); // Study Instance UID
const gdcm::Tag SeriesInstanceUID(0x0020,0x000e); // Series Instance UID
const gdcm::Tag PatientName(0x0010,0x0010); // Patient's Name
const gdcm::Tag DirectionCosines(0x0020,0x0037); // Direction Cosines
const gdcm::Tag ImagePosition(0x0020,0x0032); // Image Position
#endif
