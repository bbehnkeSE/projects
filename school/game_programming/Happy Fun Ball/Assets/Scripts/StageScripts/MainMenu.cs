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
    public  Button resetButton;

    private AudioClip successClip;
    private AudioClip buttonClick;
    private AudioClip deletePrefs;

    private int currentLevel = 0;

    private void Start()
    {
        gameObject.SetActive(true);

        playButton.onClick.AddListener(play);
        levelSelectButton.onClick.AddListener(selectLevelMenu);
        quitButton.onClick.AddListener(quitGame);
        resetButton.onClick.AddListener(resetProgress);

        successClip = Resources.Load<AudioClip>("Audio/ap_mbu/success");
        buttonClick = Resources.Load<AudioClip>("Audio/ap_mbu/buttonpress");
        deletePrefs = Resources.Load<AudioClip>("Audio/ap_mbu/NukeExplode");

        Cursor.visible = true;
        Cursor.lockState = CursorLockMode.None;
    }

    private void play()
    {
        AudioManager.Instance.SuccessSound(successClip);
        currentLevel = PlayerPrefs.GetInt("currentLevel");
        if (currentLevel == 0)
            SceneManager.LoadScene("Level_1");
        else if(currentLevel >= SceneManager.sceneCountInBuildSettings)
            SceneManager.LoadScene(currentLevel - 1);
        else
            SceneManager.LoadScene(currentLevel);
    }

    private void selectLevelMenu()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        levelSelectMenu.SetActive(true);
        gameObject.SetActive(false);
    }

    private void quitGame()
    {
        Application.Quit();
        if (UnityEditor.EditorApplication.isPlaying)
            UnityEditor.EditorApplication.isPlaying = false;
    }

    private void resetProgress()
    {
        AudioManager.Instance.PlayDeletePrefs(deletePrefs);
        PlayerPrefs.DeleteAll();
    }
}
