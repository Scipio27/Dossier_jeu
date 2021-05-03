package com.example.jeudeds;

import androidx.appcompat.app.AppCompatActivity;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.AudioAttributes;
import android.media.AudioManager;
import android.media.SoundPool;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.bumptech.glide.Glide;

import static android.os.Build.VERSION_CODES.M;

import java.util.Objects;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    public static final Random RANDOM = new Random();
    private Button rollDices;
    private ImageView imageView1, imageView2, imageView3;
    private int img1, img2, img3, value1, value2, value3;
    private boolean loaded;
    private int soundIdDes, total;
    private SoundPool soundPool;
    private float volume, mouv, mouvCur, mouvLast;
    private AudioManager audioManager;
    private static final int MAX_STREAMS = 5;
    private static final int streamType = AudioManager.STREAM_MUSIC;
    TextView textView;
    SensorManager sensorManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        rollDices = (Button) findViewById(R.id.lancerdedes);
        imageView1 = (ImageView) findViewById(R.id.imageView1);
        imageView2 = (ImageView) findViewById(R.id.imageView2);
        imageView3 = (ImageView) findViewById(R.id.imageView3);
        audioManager = (AudioManager) getSystemService(AUDIO_SERVICE);
        textView = (TextView) findViewById(R.id.textView);
        float currentVolumeIndex = (float) audioManager.getStreamMaxVolume(streamType);
        float maxVolumeIndex = (float) audioManager.getStreamMaxVolume(streamType);
        this.volume = currentVolumeIndex / maxVolumeIndex;
        this.setVolumeControlStream(streamType);
        sensorManager = (SensorManager) getSystemService(this.SENSOR_SERVICE);
        Objects.requireNonNull(sensorManager).registerListener(sensorListener,sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),SensorManager.SENSOR_DELAY_NORMAL);
        if (Build.VERSION.SDK_INT >= 21 ) {
            AudioAttributes audioAttrib = new
                    AudioAttributes.Builder()
                    .setUsage(AudioAttributes.USAGE_GAME)

                    .setContentType(AudioAttributes.CONTENT_TYPE_SONIFICATION)
                    .build();
            SoundPool.Builder builder= new SoundPool.Builder();

            builder.setAudioAttributes(audioAttrib).setMaxStreams(MAX_STREAMS);
            this.soundPool = builder.build();
        }else {
            this.soundPool = new SoundPool(MAX_STREAMS,
                    AudioManager.STREAM_MUSIC, 0);
        }
        this.soundPool.setOnLoadCompleteListener(new SoundPool.OnLoadCompleteListener() {
            @Override
            public void onLoadComplete(SoundPool soundPool, int sampleId, int status) {
                loaded = true;
            }
        });
        this.soundIdDes = this.soundPool.load(this,R.raw.shake_dice,1);


        rollDices.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                onPause();
                rollDices.setEnabled(false);
                gif();
                Handler handler = new Handler();
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        playSoundDes();
                        rollDices.setEnabled(true);
                        onResume();
                    }
                }, 1000);

            }
        });
    }

    public void playSoundDes() {
        if(loaded) {
            float leftVolumn = volume;
            float rightVolumn = volume;
            int streamId = this.soundPool.play(this.soundIdDes,leftVolumn,rightVolumn, 1, 0, 1f);
        }
        value1 = randomDiceValue();
        value2 = randomDiceValue();
        value3 = randomDiceValue();

        img1 = getResources().getIdentifier("dice_" + value1, "drawable", "com.example.jeudeds");
        img2 = getResources().getIdentifier("dice_" + value2, "drawable", "com.example.jeudeds");
        img3 = getResources().getIdentifier("dice_" + value3, "drawable", "com.example.jeudeds");

        imageView1.setImageResource(img1);
        imageView2.setImageResource(img2);
        imageView3.setImageResource(img3);

        total=value1+value2+value3;
        doubleTriple();

        textView.setText("Score: " + total);
    }

    public static int randomDiceValue() {
        return RANDOM.nextInt(6) + 1;
    }

    public void gif() {
        Glide.with(this).load(R.drawable.star).into(imageView1);
        Glide.with(this).load(R.drawable.star).into(imageView2);
        Glide.with(this).load(R.drawable.star).into(imageView3);
    }

    public void doubleTriple(){
        if(value1==value2 && value1==value3){
            Toast.makeText(MainActivity.this, "Un triple de "+value1+" bien joué",Toast.LENGTH_SHORT).show();
        }else if(value1==value2 || value1==value3){
            Toast.makeText(MainActivity.this, "Un double de "+value1+" bien joué",Toast.LENGTH_SHORT).show();
        }else if(value2==value3){
            Toast.makeText(MainActivity.this, "Un double de "+value2+" bien joué",Toast.LENGTH_SHORT).show();
        }
    }

    private final SensorEventListener sensorListener = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            float x = event.values[0];
            float y = event.values[1];
            float z = event.values[2];
            mouvLast = mouvCur;
            mouvCur = (float) Math.sqrt((double) (x * x + y * y + z * z));
            float delta = mouvCur - mouvLast;
            mouv = mouv * 0.9f + delta;
            if (mouv > 10) {
                onPause();
                rollDices.setEnabled(false);
                gif();
                Handler handler = new Handler();
                handler.postDelayed(new Runnable() {
                    public void run() {
                        playSoundDes();
                        rollDices.setEnabled(true);
                        onResume();
                    }
                }, 1000);
            }
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int i){

        }
    };

    @Override
    protected void onResume() {
        sensorManager.registerListener(sensorListener, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
                SensorManager.SENSOR_DELAY_NORMAL);
        super.onResume();
    }

    @Override
    protected void onPause() {
        sensorManager.unregisterListener(sensorListener);
        super.onPause();
    }
}

