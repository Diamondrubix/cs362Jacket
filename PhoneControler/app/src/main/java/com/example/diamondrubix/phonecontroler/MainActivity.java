package com.example.diamondrubix.phonecontroler;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

//https://stackoverflow.com/questions/14910360/how-to-play-or-resume-music-of-another-music-player-from-my-code
public class MainActivity extends AppCompatActivity {

    public Client client;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        AudioManager mAudioManager = (AudioManager) this.getSystemService(Context.AUDIO_SERVICE);

        client = new Client("192.168.43.91", 3001);
        String d = "";
        //while(true) {
            d = client.getData();


            if (d.equals("1")) {
                if (mAudioManager.isMusicActive()) {

                    Intent i = new Intent("com.android.music.musicservicecommand");

                    i.putExtra("command", "pause");//pause play next previouse
                    MainActivity.this.sendBroadcast(i);
                } else {
                    Intent i = new Intent("com.android.music.musicservicecommand");

                    i.putExtra("command", "play");
                    MainActivity.this.sendBroadcast(i);
                }
            }
        //}
        //}
    }
}
