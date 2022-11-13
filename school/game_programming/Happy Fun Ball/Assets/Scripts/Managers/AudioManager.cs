using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AudioManager : MonoBehaviour
{
    // MarbleMovement.cs
    public AudioSource GetKeySource;
    public AudioSource MarbleBounceSource;
    public AudioSource MarbleRollSource;
    public AudioSource MarbleJumpSource;

    // MainMenu.cs
    public AudioSource NewGameSource;

    public AudioSource MusicSource;

    public float lowPitchRange = 0.95f;
    public float highPitchRange = 1.05f;

    public static AudioManager Instance = null;

    private void Awake()
    {
        if (Instance == null)
            Instance = this;
        else if (Instance != this)
            Destroy(gameObject);

        DontDestroyOnLoad(gameObject);

        GetKeySource.volume       = 0.2f;
        MarbleBounceSource.volume = 0.2f;
        MarbleRollSource.volume   = 0.2f;
        MarbleJumpSource.volume   = 0.2f;

        NewGameSource.volume      = 0.2f;
    }

    public void PlayGetKey(AudioClip clip)
    {
        GetKeySource.clip = clip;
        GetKeySource.Play();
    }

    public void PlayMusic(AudioClip clip)
    {
        MusicSource.clip = clip;
        MusicSource.Play();
    }

    public void PlayRandomMarbleBounce(params AudioClip[] clips)
    {
        int randomIndex = Random.Range(0,clips.Length);
        float randomPitch = Random.Range(lowPitchRange, highPitchRange);

        MarbleBounceSource.pitch = randomPitch;
        MarbleBounceSource.clip = clips[randomIndex];
        MarbleBounceSource.Play();
    }

    public void PlayMarbleRoll(AudioClip clip, float velocityMag)
    {
        MarbleRollSource.clip = clip;
        MarbleRollSource.pitch = setPitch(velocityMag, 0.5f, 100f, 0.5f, 2f);

        if (!MarbleRollSource.isPlaying)
            MarbleRollSource.Play();
        if (velocityMag < 1f)
            MarbleRollSource.Pause();
        
    }

    public void PauseMarbleRoll(AudioClip clip)
    {
        MarbleRollSource.clip = clip;
        MarbleRollSource.Pause();
    }

    public void PlayMarbleJump(AudioClip clip)
    {
        MarbleJumpSource.clip = clip;
        MarbleJumpSource.Play();
    }

    public void PlayNewGameSound(AudioClip clip)
    {
        NewGameSource.clip = clip;
        NewGameSource.Play();
    }

    private float setPitch(float mainValue, float inValueMin, float inValueMax, float outValueMin, float outValueMax)
    {
        return (mainValue - inValueMin) * (outValueMax - outValueMin) / (inValueMax - inValueMin) + outValueMin;
    }
}
