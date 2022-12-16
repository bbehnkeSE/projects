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

    private AudioClip buttonClick;

    // Start is called before the first frame update
    void Start()
    {
        paused         = false;
        hud            = FindObjectOfType<HUD>();
        marbleMovement = FindObjectOfType<MarbleMovement>();

        continueButton.onClick.AddListener(continueGame);
        mainMenuButton.onClick.AddListener(mainMenu);

        pauseMenu.gameObject.SetActive(false);

        buttonClick = Resources.Load<AudioClip>("Audio/ap_mbu/buttonpress");
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
            switchPause();

        if (paused)
        {
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;
        }
        else
        {
            Cursor.visible = false;
            Cursor.lockState = CursorLockMode.Locked;
        }
    }

    private void continueGame()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
        switchPause();
    }

    private void mainMenu()
    {
        AudioManager.Instance.PlayButtonClick(buttonClick);
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
