package com.myandroid.imx_i2c;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    EditText e;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        e = (EditText) findViewById(R.id.i2c_addr);
        // Example of a call to a native method
        //TextView tv = (TextView) findViewById(R.id.id_text);
        //tv.setText(stringFromJNI());
    }

    public void onClick(View v) {
        int addr = Integer.parseInt(e.getText().toString(), 16);
        System.out.println("addr: " + addr);
        i2c_init(addr);
        //stringFromJNI();
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void i2c_init(int addr);
}
