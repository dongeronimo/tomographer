using PowerUI;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class SampleSceneViewController : MonoBehaviour
{
    private LibTomographerInterface libInterface;
    private HtmlDocument document;
    // Start is called before the first frame update
    void Start()
    {
        libInterface = GetComponent<LibTomographerInterface>();
        document = GetComponent<Manager>().document;
    }

    // Update is called once per frame
    unsafe void Update()
    {
        Dom.Element container = document.getElementsByClassName("root-container").item(0);
        ApplyFullHeightToContainerElement();
        SetPersistentDataPath();
       //SomeDataListToDivs(libInterface.TestFillStructInCpp(), container);
        TestCanLoadDicom();
       // libInterface.FindAllDicomsInPath();
       
    }
    //private void TestNumberOfDicoms()
    //{
    //    var amount = libInterface.FindAllDicomsInPath();
    //    document.getElementById("number-of-dicoms").innerText = amount.ToString();
    //}
    /// <summary>
    /// Root div won't have full height even with height = 100%. So in Update I manually set it's size in pixels
    /// to be equal to the screen height. It assumes an element with class name equal to "root-container".
    /// </summary>
    private void ApplyFullHeightToContainerElement()
    {
        Dom.Element container = document.getElementsByClassName("root-container").item(0);
        container.style.height = Screen.height + "px";
    }
    /// <summary>
    /// Delete all children in the given target.
    /// </summary>
    /// <param name="target"></param>
    private void RemoveAllChildren(Dom.Element target)
    {
        target.children.ToList().ForEach(child =>
        {
            target.removeChild(child);
        });
    }

    private List<Dom.Element> FindChildrenByName(Dom.Element target, string name)
    {
        return target.getElementsByName(name).ToList();
    }
    private void SomeDataListToDivs(List<SomeData> someDataList, Dom.Element target)
    {
        var someDataItems = FindChildrenByName(target, "someDataItem");
        foreach (var s in someDataItems)
        {
            s.remove();
        }

        someDataList
            .OrderBy(current => current.Id())
            .Select(currentData =>
            {
                //TODO: Cria os span
                var idSpan = document.createElement("span");
                idSpan.innerText = currentData.Id().ToString();
                idSpan.style.paddingRight = "5vw";
                var idValue = document.createElement("span");
                idValue.innerText = currentData.Value().ToString();
                //TODO: Cria a div que embala os span
                var divBox = document.createElement("div");
                divBox.appendChild(idSpan);
                divBox.appendChild(idValue);
                divBox.style.paddingTop = "2vh";
                divBox.style.paddingRight = "2vw";
                divBox.style.paddingLeft = "2vw";
                divBox.setAttribute("name", "someDataItem");
                //TODO: Retorna a div
                return divBox;
            })
            .ToList()
            .ForEach(currentElement => {
                target.appendChild(currentElement);
            });
    }

    private void SetPersistentDataPath()
    {
        document.getElementById("persistent-data-path").innerText = Application.persistentDataPath;
       //Debug.Log("Application.persistentDataPath = " + Application.persistentDataPath);
    }
    private void TestCanLoadDicom()
    {
        //var couldOpen = libInterface.TestCanReadDicomFile();
        //document.getElementById("can-read-file").innerText = couldOpen.ToString();
    }
}
