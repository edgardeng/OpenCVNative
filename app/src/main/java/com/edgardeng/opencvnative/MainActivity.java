package com.edgardeng.opencvnative;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private ImageView imageView;
    private Button showBtn, processBtn;
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageView = (ImageView) findViewById(R.id.imageView);
        showBtn = (Button) findViewById(R.id.show);
        showBtn.setOnClickListener(this);
        processBtn = (Button) findViewById(R.id.process);
        processBtn.setOnClickListener(this);
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.pic_test);
        imageView.setImageBitmap(bitmap);

        String info = this.sayHello();
        Log.e("MainActivity",info);

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Log.e("MainActivity",getDevice());
            }
        },2000);


    }


    @Override
    public void onClick(View v) {
        if (v == showBtn) {
            startActivity(new Intent(this,DeviceInfoActivity.class));
        } else {
            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.pic_test);
//            getImageEdge(bitmap);
            imageView.setImageBitmap(bitmap);
        }
    }


// public static native void getImageEdge(Object obj); //获得Canny边缘
    public static native String sayHello();
    public static native String getDevice();


}
