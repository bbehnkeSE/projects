using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UIElements;

public class CameraControl : MonoBehaviour
{
    Transform        camTransform;
    public Transform marble;
    public float     senX;
    public float     senY;
    public float     minRotationY;
    public float     maxRotationY;
    public float     camSpeed;

    private PauseManager pauseManager;

    float verticalLookRotation;

    // Start is called before the first frame update
    void Start()
    {
        senX         = 3f;
        senY         = 1.5f;
        minRotationY = -50f;
        maxRotationY = 0.1f;
        camSpeed     = 15f;

        camTransform = GetComponentInChildren<Camera>().transform;
        pauseManager = FindObjectOfType<PauseManager>();
    }

    // Update is called once per frame
    void LateUpdate()
    {
        if (!pauseManager.getPaused())
        {
            transform.position = marble.position;
            transform.Rotate(Vector3.up * Input.GetAxis("Mouse X") * senX);
            verticalLookRotation += Input.GetAxis("Mouse Y") * senY;

            verticalLookRotation = Mathf.Clamp(verticalLookRotation, minRotationY, maxRotationY);
            camTransform.localEulerAngles = Vector3.left * verticalLookRotation;
        }
    }
}
