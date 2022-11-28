using JetBrains.Annotations;
using Microsoft.Unity.VisualStudio.Editor;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MarbleMovement : MonoBehaviour
{
    public  float       speed;
    public  float       jumpHeight;
    public  Transform   camTransform;

    private AudioClip   getKey;
    private AudioClip   roll;
    private AudioClip   jump;
    private AudioClip   success;
    private AudioClip[] collide;
    
    private Rigidbody   rb;

    private StageFunctions StageFunctions;
    private int nextSceneIndex;

    // Start is called before the first frame update
    void Start()
    {
        speed      = 50.0f;
        jumpHeight = 10.0f;
        rb         = GetComponent<Rigidbody>();
        rb.maxAngularVelocity = Mathf.Infinity;
        nextSceneIndex = SceneManager.GetActiveScene().buildIndex + 1;

        StageFunctions = FindObjectOfType<StageFunctions>();

        getKey     = Resources.Load<AudioClip>("Audio/ap_mbu/getKey");
        roll       = Resources.Load<AudioClip>("Audio/ap_mbu/rolling_hard");
        jump       = Resources.Load<AudioClip>("Audio/ap_mbu/jump");
        success    = Resources.Load<AudioClip>("Audio/ap_mbu/success");

        collide    = new AudioClip[4];
        collide[0] = Resources.Load<AudioClip>("Audio/ap_mbu/bouncehard1");
        collide[1] = Resources.Load<AudioClip>("Audio/ap_mbu/bouncehard2");
        collide[2] = Resources.Load<AudioClip>("Audio/ap_mbu/bouncehard3");
        collide[3] = Resources.Load<AudioClip>("Audio/ap_mbu/bouncehard4");
    }


    // Update is called once per frame
    void FixedUpdate()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical   = Input.GetAxis("Vertical");


        // Alter movement based on direction camera is facing
        Vector3 movement     = camTransform.TransformDirection(new Vector3(moveHorizontal, 0.0f, moveVertical));

        rb.AddForce(Physics.gravity * rb.mass);

        if (isGrounded())
        {
            rb.AddForce(movement * speed);
            if (Input.GetButton("Jump"))
            {
                rb.AddForce(Vector3.up * jumpHeight, ForceMode.Impulse);
                AudioManager.Instance.PlayMarbleJump(jump);
            }
            if (rb.velocity.y > 0.0f || rb.velocity.z > 0.0f)
                AudioManager.Instance.PlayMarbleRoll(roll, rb.velocity.magnitude);
        }
        else
        {
            AudioManager.Instance.PauseMarbleRoll(roll);
            rb.AddForce(movement * speed / 8);
        }
    }


    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Key"))
        {
            other.gameObject.SetActive(false);
            other.transform.GetChild(0).gameObject.GetComponentInChildren<ParticleSystem>().Play();
            StageFunctions.decrementKeyCount();
            AudioManager.Instance.PlayGetKey(getKey);
        }
        if (other.gameObject.CompareTag("LightShaft"))
        {
            AudioManager.Instance.SuccessSound(success);
            if(nextSceneIndex < SceneManager.sceneCountInBuildSettings)
                SceneManager.LoadScene(nextSceneIndex);
            else
                SceneManager.LoadScene(0);
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        AudioManager.Instance.PlayRandomMarbleBounce(collide);
        if(collision.gameObject.CompareTag("MovingPlat"))
            transform.parent.parent = collision.transform;
    }

    private void OnCollisionExit(Collision collision)
    {
        if (collision.gameObject.CompareTag("MovingPlat"))
            transform.parent.parent = null;
    }

    bool isGrounded()
    {
        return Physics.Raycast(transform.position, Vector3.down, 0.8f);
    }
}
