using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using static UnityEngine.GraphicsBuffer;

public class PlayerMovement : MonoBehaviour
{
    public float speed;
    public TMP_Text scoreText;
    public TMP_Text winText;
    public GameObject Trigger;
    public GameObject Targets;
    public GameObject newTarget;
    public Material ready;
    public Material notReady;

    // Timer
    public float timeRemaining;
    public float timeInit = 10;
    public TMP_Text timerText;
    private bool timerRunning;
    private float seconds;

    private Rigidbody rb;
    private int score;

    // Start is called before the first frame update
    void Start()
    {
        speed = 15;
        score = 0;
        rb = GetComponent<Rigidbody>();
        timeRemaining = timeInit;
        timerRunning = false;

        setScoreText();
        setTimerText(timeRemaining);
        winText.text = "";
    }

    private void Update()
    {
        if(timerRunning)
        {
            timeRemaining -= Time.deltaTime;
            seconds = Mathf.FloorToInt(timeRemaining % 60);
            setTimerText(seconds);
        }
        if (timeRemaining <= 0.5)
        {
            timerRunning = false;
            if (timeInit <= 2)
                timeInit = 2;
            timeRemaining = --timeInit;
            setTimerText(timeRemaining);
            Trigger.SetActive(true);
            swapTargetState(Targets);
        }
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        Vector3 movement = new Vector3(moveHorizontal, 0.0f, moveVertical);

        rb.AddForce(movement * speed);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Trigger"))
        {
            other.gameObject.SetActive(false);
            swapTargetState(Targets);
            timerRunning = true;
        }

        if(other.gameObject.CompareTag("Multiplier"))
        {
            Vector3 randPos = new Vector3(Random.Range(-5f, 5f), Targets.transform.GetChild(0).position.y, Random.Range(-5f, 5f));
            Instantiate(newTarget, randPos, new Quaternion(0f, 0f, 0f, 0f), Targets.transform);

            // This was the only way I could think of to get the player away from the Type2 block before 30 clones spawned
            // God help you if you bounce on top of it.
            rb.AddForce(new Vector3(1,1,1) * 3, ForceMode.Impulse);
        }

        if(other.gameObject.CompareTag("Target"))
        {
            other.gameObject.SetActive(false);
            ++score;
            setScoreText();
        }
    }

    void setScoreText()
    {
        scoreText.text = "SCORE: " + score.ToString();
        if (score >= 10)
        {
            winText.text = "YOU WIN!";
            timerRunning = false;
        }
    }

    void setTimerText(float sec)
    {
        timerText.text = sec.ToString();
    }

    void swapTargetState(GameObject targets)
    {
        if (targets.transform.GetChild(0).GetComponentInChildren<BoxCollider>().isTrigger)
        {
            foreach (Transform target in targets.transform)
            {
                target.GetComponentInChildren<MeshRenderer>().material = notReady;
                target.GetComponentInChildren<BoxCollider>().isTrigger = false;
                target.GetChild(0).gameObject.SetActive(true);
            }
        }
        else
        {
            foreach (Transform target in targets.transform)
            {
                target.GetComponentInChildren<MeshRenderer>().material = ready;
                target.GetComponentInChildren<BoxCollider>().isTrigger = true;
                target.GetChild(0).gameObject.SetActive(false);
            }
        }
    }
}
