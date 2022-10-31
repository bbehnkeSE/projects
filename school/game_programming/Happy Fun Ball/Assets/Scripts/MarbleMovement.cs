using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MarbleMovement : MonoBehaviour
{
    public  float     speed;
    public  float     jumpHeight;
    public  Transform camTransform;
    private Rigidbody rb;

    private StageFunctions StageFunctions;

    // Start is called before the first frame update
    void Start()
    {
        speed = 50.0f;
        jumpHeight = 10.0f;
        rb = GetComponent<Rigidbody>();
        rb.maxAngularVelocity = Mathf.Infinity;

        StageFunctions = FindObjectOfType<StageFunctions>();
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
                rb.AddForce(Vector3.up * jumpHeight, ForceMode.Impulse);
        }
        else
            rb.AddForce(movement * speed / 10);
    }


    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Key"))
        {
            other.gameObject.SetActive(false);
            StageFunctions.decrementKeyCount();
        }
        if(other.gameObject.CompareTag("LightShaft"))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        }
    }


    bool isGrounded()
    {
        return Physics.Raycast(transform.position, Vector3.down, 0.8f);
    }
}
