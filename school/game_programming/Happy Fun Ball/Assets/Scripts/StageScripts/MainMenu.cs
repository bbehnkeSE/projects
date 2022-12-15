using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    public  GameObject levelSelectMenu;
    public  Button playButton;
    public  Button quitButton;
    public  Button levelSelectButton;
    private AudioClip successClip;

    private void Start()
    {
        gameObject.SetActive(true);
        playButton.onClick.AddListener(newGame);
        levelSelectButton.onClick.AddListener(selectLevelMenu);
        quitButton.onClick.AddListener(quitGame);
        successClip = Resources.Load<AudioClip>("Audio/ap_mbu/success");
    }

    private void newGame()
    {
        AudioManager.Instance.SuccessSound(successClip);
        SceneManager.LoadScene("Level_1");
    }

    private void selectLevelMenu()
    {
        levelSelectMenu.SetActive(true);
        gameObject.SetActive(false);
    }

    private void quitGame()
    {
        Application.Quit();
        if (UnityEditor.EditorApplication.isPlaying)
            UnityEditor.EditorApplication.isPlaying = false;
    }
}
