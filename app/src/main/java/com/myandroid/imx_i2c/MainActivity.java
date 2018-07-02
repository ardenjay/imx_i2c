package com.myandroid.imx_i2c;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    EditText e;
    TextView tv;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        e = (EditText) findViewById(R.id.i2c_addr);

        tv = (TextView) findViewById(R.id.txtResult);
        //tv.setText(stringFromJNI());
    }

    public void onClick(View v) {
        int addr = Integer.parseInt(e.getText().toString(), 16);
        System.out.println("addr: " + addr);
        int ret = i2c_init(addr);
        if (ret != 0) {
            tv.setText("i2c_init fail");
        } else {
            tv.setText("i2c_init success");
        }
        dynamic_i2c_init(addr);
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int i2c_init(int addr);
    public native int dynamic_i2c_init(int addr);
}
