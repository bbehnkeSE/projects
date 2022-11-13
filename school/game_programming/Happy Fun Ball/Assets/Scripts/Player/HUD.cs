using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HUD : MonoBehaviour
{
    public  Text  timerText;
    private float timer = 0f;


    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;

        string minutes = Mathf.Floor(timer / 60).ToString("00");
        string seconds = Mathf.Floor(timer % 60).ToString("00");

        timerText.text = string.Format("{0}:{1}", minutes, seconds);
    }
}
