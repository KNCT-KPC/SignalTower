using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Alert : MonoBehaviour{
    [SerializeField] GameObject alert;
    float seconds;
    bool alert_enable = false;
    bool shooeSE_play = false;
    public static int result = -1;
    public static int otetuki_count = 0;
    public AudioClip shootSE;
    AudioSource audioSource;
    System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();

    void Start(){
        audioSource = GetComponent<AudioSource>();
        //DontDestroyOnLoad (this);
    }

    void Update(){
        seconds += Time.deltaTime;
        if (seconds >= Random.Range(2.0f, 10.0f)){
            alert_enable = true;
            alert.SetActive(true);
            if (!shooeSE_play) {
                audioSource.PlayOneShot(shootSE);
                shooeSE_play = true;
            }
            sw.Start(); //時間計測開始
        }
        if (Input.GetKeyDown(KeyCode.Space)){
            sw.Stop();
            if (alert_enable){
                Debug.Log(sw.ElapsedMilliseconds + "ms");
                result = (int)sw.ElapsedMilliseconds;
                //リザルトシーンへ
                SceneManager.LoadScene("resultScene");
            }
            else{
                otetuki_count++;
                Debug.Log("お手つき!! x " + otetuki_count);
                result = -1;
                //ゲームオーバーシーンへ
                SceneManager.LoadScene("resultScene");
            }
            sw.Reset();
            seconds = 0;
            alert.SetActive(false);
            alert_enable = false;
        }
    }
}
