using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformMovement : MonoBehaviour
{
    public Transform initPos;
    public Transform destPos;
    public float speed;
    public bool changeDir = false;

    // Start is called before the first frame update
    void Start()
    {
        if (this.CompareTag("Obstacle"))
            speed = 10f;
        else
            speed = 5f;
    }

    // Update is called once per frame
    void Update()
    {
        if (!changeDir)
            transform.position = Vector3.MoveTowards(transform.position, destPos.position, speed * Time.deltaTime);
        else
            transform.position = Vector3.MoveTowards(transform.position, initPos.position, speed * Time.deltaTime);

        if (transform.position == destPos.position)
            changeDir = true;
        if (transform.position == initPos.position)
            changeDir = false;
    }
}
