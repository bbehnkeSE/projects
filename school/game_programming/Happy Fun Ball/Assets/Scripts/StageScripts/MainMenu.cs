using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    public  Button playButton;
    public  Button quitButton;
    private AudioClip successClip;

    private void Start()
    {
        playButton.onClick.AddListener(newGame);
        quitButton.onClick.AddListener(quitGame);
        successClip = Resources.Load<AudioClip>("Audio/ap_mbu/success");
    }

    private void newGame()
    {
        AudioManager.Instance.SuccessSound(successClip);
        SceneManager.LoadScene("Level_1");
    }

    private void quitGame()
    {
        Application.Quit();
        if (UnityEditor.EditorApplication.isPlaying)
            UnityEditor.EditorApplication.isPlaying = false;
    }
}
