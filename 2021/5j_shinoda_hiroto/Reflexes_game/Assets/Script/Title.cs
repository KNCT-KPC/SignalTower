using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Title : MonoBehaviour{
    private bool firstPush = false;

    void Update(){
        if (Input.GetKeyDown(KeyCode.Space)){
            PressMemory();
        }
    }

    public void PressMemory(){
        Debug.Log("Press Memory");
        if(!firstPush){
            Debug.Log("Go Next Scene");
            firstPush = true;
            //次のシーンへスクリプト
            SceneManager.LoadScene("alertScene");
        }
    }
}
