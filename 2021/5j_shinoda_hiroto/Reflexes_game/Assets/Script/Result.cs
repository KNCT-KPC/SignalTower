using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;  // 追加しましょう

public class Result : MonoBehaviour{
    Alert Alertscript;
    public Text ResultText; // Textオブジェクト
    private bool firstPush = false;

    void Start(){
        //Alertscript = GameObject.Find("alert_Image").GetComponent<Alert>(); //GetComponentはスクリプト名
        Debug.Log(Alert.result);
    }

    // Update is called once per frame
    void Update(){
        // テキストの表示を入れ替える
        if(Alert.result == -1){
            ResultText.text = "Too early!!";
        }else{
            ResultText.text = Alert.result + "ms";
        }

        if (Input.GetKeyDown(KeyCode.Space)){
            PressMemory();
        }
    }

    public void PressMemory(){
        Debug.Log("Press Memory");
        if(!firstPush){
            Debug.Log("Go Next Scene");
            firstPush = true;
            //Alert.result = -1;
            //Alert.otetuki_count = 0;
            //次のシーンへスクリプト
            SceneManager.LoadScene("titleScene");
        }
    }
}
