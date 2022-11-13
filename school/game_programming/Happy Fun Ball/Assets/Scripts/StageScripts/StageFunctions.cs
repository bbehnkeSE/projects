using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageFunctions : MonoBehaviour
{
    public Material goalActive, goalNotActive;

    private int remainingKeys;
    private GameObject lightShaft;
    private MeshRenderer pedestalRenderer;

    void Awake()
    {
        remainingKeys = transform.Find("Keys").childCount;

        lightShaft = GameObject.FindGameObjectWithTag("Goal").transform.GetChild(0).gameObject;
        pedestalRenderer = GameObject.FindGameObjectWithTag("Goal").transform.GetChild(1).GetComponent<MeshRenderer>();

        if (remainingKeys > 0)
        {
            lightShaft.SetActive(false);
            pedestalRenderer.material = goalNotActive;
        }
        else
        {
            lightShaft.SetActive(true);
            pedestalRenderer.material = goalActive;
        }
    }

    public void decrementKeyCount()
    {
        if (--remainingKeys == 0)
            activateGoal();
    }

    private void activateGoal()
    {
        lightShaft.SetActive(true);
        pedestalRenderer.material = goalActive;
    }
}
