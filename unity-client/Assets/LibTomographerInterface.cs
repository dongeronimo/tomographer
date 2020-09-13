using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using System.Linq;

public class SomeData
{
    private int id;
    private string value;

    public SomeData(SomeDataDAO dao)
    {
        this.id = dao.id;
        this.value = dao.value;
    }
    public int Id() { return id; }
    public string Value() { return value; }
}
[StructLayout(LayoutKind.Sequential)]
public struct SomeDataDAO
{
    public int id;
    public string value;
}
[StructLayout(LayoutKind.Sequential)]
public struct DicomFileVOList
{
    public int length;
    public System.IntPtr first;
}
[StructLayout(LayoutKind.Sequential)]
public struct DicomFileVO
{
    public string filepath;
    public string patient;
    public string study;
    public string series;
    public System.IntPtr imagePosition;
    public System.IntPtr directionCosines;
    public System.IntPtr spacing;
    public int cols;
    public int rows;
    public string scalarType;
    public int bufferSize;
    public System.IntPtr imageBuffer;
}
public class LibTomographerInterface : MonoBehaviour
{
    [DllImport("tomographer", EntryPoint = "BeginImageLoad", CallingConvention = CallingConvention.Cdecl,
        CharSet = CharSet.Ansi)]
    public static extern void BeginImageLoad(string dirpath);

    [DllImport("tomographer", EntryPoint = "EndImageLoad", CallingConvention = CallingConvention.Cdecl,
        CharSet = CharSet.Ansi)]
    public static extern void EndImageLoad();

    [DllImport("tomographer", EntryPoint = "GetNumberOfFiles", CallingConvention = CallingConvention.Cdecl,
        CharSet = CharSet.Ansi)]
    public static extern int GetNumberOfFiles();

    [DllImport("tomographer", EntryPoint = "EndImageLoad", CallingConvention = CallingConvention.Cdecl,
        CharSet = CharSet.Ansi)]
    public static extern System.IntPtr GetFile(int id);

    private void Start()
    {
        
    }

    private void Update()
    {
        BeginImageLoad(Application.persistentDataPath);
        //TODO: GET THE IMAGES
        EndImageLoad();
    }
    //[DllImport("tomographer", EntryPoint = "FillSomeData")]
    //private static extern void _FillSomeData(int amount, System.IntPtr outData);
    //[DllImport("tomographer", EntryPoint = "CanReadDicomFileWithGDCM")]
    //private static extern bool _CanReadDicomFileWithGDCM(string filepath);
    ////[DllImport("tomographer", EntryPoint = "FindAllDicomsInPath", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    ////private static extern void _FindAllDicomsInPath(string dirpath, ref int outNumberOfFiles, System.IntPtr outFiles);
    //[DllImport("tomographer", EntryPoint = "FindAllDicomsInPath", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    //private static extern void _FindAllDicomsInPath(string dirpath, ref DicomFileVOList fileList);
    //public int FindAllDicomsInPath()
    //{
    //    var path = Application.persistentDataPath;
    //    DicomFileVOList dicomList = new DicomFileVOList();
    //    _FindAllDicomsInPath(path, ref dicomList);
    //    Debug.Log(path.Length);
    //    return dicomList.length;
    //    //System.IntPtr ptrNumberOfFiles = Marshal.AllocHGlobal(sizeof(System.Int32));
    //    //_FindAllDicomsInPath(path, ptrNumberOfFiles, System.IntPtr.Zero);
    //    //int numberOfFiles = Marshal.ReadInt32(ptrNumberOfFiles);
    //    //Marshal.FreeHGlobal(ptrNumberOfFiles);
    //    //return numberOfFiles;
    //}
    //public static void MarshalUnmananagedArray2Struct<T>(System.IntPtr unmanagedArray, int length, out T[] mangagedArray)
    //{
    //    var size = Marshal.SizeOf(typeof(T));
    //    mangagedArray = new T[length];
    //    for (int i = 0; i < length; i++)
    //    {
    //        System.IntPtr ins = new System.IntPtr(unmanagedArray.ToInt64() + i * size);
    //        mangagedArray[i] = Marshal.PtrToStructure<T>(ins);
    //    }
    //}
    //public List<SomeData> TestFillStructInCpp()
    //{
    //    int size = 5;
    //    int structSize = Marshal.SizeOf<SomeDataDAO>();
    //    System.IntPtr allocatedMemoryBlockToSendToDll = Marshal.AllocHGlobal(size * structSize); //Allocates the memory
    //    _FillSomeData(size, allocatedMemoryBlockToSendToDll);//Calls the dll 
    //    //TODO... translate the memory block to useful data
    //    SomeDataDAO[] returningDaos = new SomeDataDAO[size];
    //    LibTomographerInterface.MarshalUnmananagedArray2Struct(allocatedMemoryBlockToSendToDll, size, out returningDaos);
    //    List<SomeData> result = returningDaos.Select(currentDao =>
    //    {
    //        return new SomeData(currentDao);
    //    }).ToList();
    //    Marshal.FreeHGlobal(allocatedMemoryBlockToSendToDll);//Releases the memory
    //    return result;
    //}
    //public bool TestCanReadDicomFile()
    //{
    //    var path = Application.persistentDataPath + "/MarchingMan48.dcm";
    //    return _CanReadDicomFileWithGDCM(path);
    //}
}
