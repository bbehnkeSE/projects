using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LevelSelect : MonoBehaviour
{
    public GameObject mainMenu;

    public Button levelOneButton;
    public Button levelTwoButton;
    public Button levelThreeButton;
    public Button levelFourButton;
    public Button mainMenuButton;

    // Start is called before the first frame update
    void Start()
    {
        gameObject.SetActive(false);

        levelOneButton.onClick.AddListener(loadLevelOne);
        levelTwoButton.onClick.AddListener(loadLevelTwo);
        levelThreeButton.onClick.AddListener(loadLevelThree);
        levelFourButton.onClick.AddListener(loadLevelFour);

        mainMenuButton.onClick.AddListener(returnToMainMenu);
    }

    private void returnToMainMenu()
    {
        mainMenu.SetActive(true);
        gameObject.SetActive(false);
    }

    private void loadLevelOne()
    {
        SceneManager.LoadScene("Level_1");
    }

    private void loadLevelTwo()
    {
        SceneManager.LoadScene("Level_2");
    }

    private void loadLevelThree()
    {
        SceneManager.LoadScene("Level_3");
    }

    private void loadLevelFour()
    {
        SceneManager.LoadScene("Level_4");
    }

}
