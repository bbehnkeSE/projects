using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MarbleMovement : MonoBehaviour
{
    public float speed;
    public float jumpHeight;
    public Transform camTransform;
    private Rigidbody rb;

    public AudioSource rolling;

    // Start is called before the first frame update
    void Start()
    {
        speed = 70.0f;
        jumpHeight = 10.0f;
        rb = GetComponent<Rigidbody>();
        rolling = GetComponent<AudioSource>();
        rolling.Play(0);
    }

    bool isGrounded()
    {
        return Physics.Raycast(transform.position, Vector3.down, 0.8f);
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");


        // Alter movement based on direction camera is facing
        Vector3 movement = camTransform.TransformDirection(new Vector3(moveHorizontal, 0.0f, moveVertical));

        rb.AddForce(Physics.gravity * rb.mass);

        if (isGrounded())
        {
            rb.AddForce(movement * speed);
            if (Input.GetButton("Jump"))
                rb.AddForce(Vector3.up * jumpHeight, ForceMode.Impulse);

            if (rb.velocity.magnitude > 1)
                rolling.UnPause();
            else
                rolling.Pause();
        }
        else
            rolling.Pause();
    }
}
