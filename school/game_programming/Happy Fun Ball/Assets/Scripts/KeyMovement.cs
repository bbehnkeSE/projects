using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyMovement : MonoBehaviour
{
    public float speed;

    private Vector3 origPos;

    private void Start()
    {
        speed = .25f;

        origPos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        transform.position = new Vector3(origPos.x, origPos.y + (Mathf.Sin(Time.time) * speed), origPos.z);
        transform.Rotate(new Vector3(0, 30, 0) * Time.deltaTime);
    }
}
