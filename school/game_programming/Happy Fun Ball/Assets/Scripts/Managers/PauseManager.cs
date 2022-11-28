using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PauseManager : MonoBehaviour
{
    private bool           paused;

    private MarbleMovement marbleMovement;
    private Vector3        currentVelocity = Vector3.zero;
    private HUD            hud;

    public  Image  pauseMenu;
    public  Button continueButton;
    public  Button mainMenuButton;

    // Start is called before the first frame update
    void Start()
    {
        paused         = false;
        hud            = FindObjectOfType<HUD>();
        marbleMovement = FindObjectOfType<MarbleMovement>();
        continueButton.onClick.AddListener(continueGame);
        mainMenuButton.onClick.AddListener(mainMenu);
        pauseMenu.gameObject.SetActive(false);
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
            switchPause();
    }

    private void continueGame()
    {
        switchPause();
    }

    private void mainMenu()
    {
        SceneManager.LoadScene("_Main_Menu");
        switchPause();
    }

    private void switchPause()
    {
        if(!paused)
        {
            Time.timeScale = 0;
            pauseMenu.gameObject.SetActive(true);
            paused = true;
        }
        else
        {
            Time.timeScale = 1;
            pauseMenu.gameObject.SetActive(false);
            paused = false;
        }
    }

    public bool getPaused()
    {
        return paused;
    }
}
