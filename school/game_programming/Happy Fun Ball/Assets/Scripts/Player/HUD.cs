using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HUD : MonoBehaviour
{
    public  Text  timerText;
    private float timer = 0f;
    private string minutes = "00";
    private string seconds = "00";

    private bool timerRunning = true;

    // Update is called once per frame
    void Update()
    {
        if (timerRunning)
        {
            timer += Time.deltaTime;

            minutes = Mathf.Floor(timer / 60).ToString("00");
            seconds = Mathf.Floor(timer % 60).ToString("00");

        }
        timerText.text = string.Format("{0}:{1}", minutes, seconds);
    }

    public void pauseTimer()
    {
        timerRunning = false;
    }

    public void startTimer()
    {
        timerRunning = true;
    }
}
