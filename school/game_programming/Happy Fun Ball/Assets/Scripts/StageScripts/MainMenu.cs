using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    public  Button playButton;
    private AudioClip newGame;

    private void Start()
    {
        playButton.onClick.AddListener(changeScene);
        newGame = Resources.Load<AudioClip>("Audio/ap_mbu/newGame");
    }

    private void changeScene()
    {
        AudioManager.Instance.PlayNewGameSound(newGame);
        SceneManager.LoadScene("Level_1");
    }
}
