using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LevelSelect : MonoBehaviour
{
    public GameObject mainMenu;

    public Button levelOneButton;
    public Button levelTwoButton;
    public Button levelThreeButton;
    public Button levelFourButton;
    public Button levelFiveButton;
    public Button mainMenuButton;

    private List<Button> buttons = new List<Button>();
    private int currentLevel = 0;

    private AudioClip buttonClick;

    // Start is called before the first frame update
    void Start()
    {
        gameObject.SetActive(false);

        levelOneButton.onClick.AddListener(loadLevelOne);
        buttons.Add(levelOneButton);

        levelTwoButton.onClick.AddListener(loadLevelTwo);
        buttons.Add(levelTwoButton);

        levelThreeButton.onClick.AddListener(loadLevelThree);
        buttons.Add(levelThreeButton);

        levelFourButton.onClick.AddListener(loadLevelFour);
        buttons.Add(levelFourButton);

        levelFiveButton.onClick.AddListener(loadLevelFive);
        buttons.Add(levelFiveButton);

        mainMenuButton.onClick.AddListener(returnToMainMenu);

        buttonClick = Resources.Load<AudioClip>("Audio/ap_mbu/buttonpress");
    }

    private void Update()
    {
        currentLevel = PlayerPrefs.GetInt("currentLevel");
        for (int i = currentLevel; i < buttons.Count; ++i)
        {
            buttons[i].interactable = false;
        }
    }

    private void returnToMainMenu()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        mainMenu.SetActive(true);
        gameObject.SetActive(false);
    }

    private void loadLevelOne()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        SceneManager.LoadScene("Level_1");
    }

    private void loadLevelTwo()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        SceneManager.LoadScene("Level_2");
    }

    private void loadLevelThree()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        SceneManager.LoadScene("Level_3");
    }

    private void loadLevelFour()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        SceneManager.LoadScene("Level_4");
    }

    private void loadLevelFive()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        SceneManager.LoadScene("Level_5");
    }

}
