package com.arpaul.sortndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.arpaul.utilitieslib.StringUtils;

public class MainActivity extends AppCompatActivity {

    private TextView tvUnsortedArray, tvSortedArray;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    static {
        System.loadLibrary("native-c-lib");
    }

    //https://developer.android.com/studio/projects/add-native-code.html

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initialiseUIControls();

        int oldValues[] = {5, 6, 8, 1, 0, 3, 0, 7, 2};
        oldValues = getRandomListJNI(100, 1000);
        if(oldValues != null) {
            StringBuilder strBuilder = new StringBuilder();
            for(int i = 0; i < oldValues.length; i++)
                strBuilder.append(oldValues[i]).append(" , ");
            tvUnsortedArray.setText(StringUtils.removeLastComma(strBuilder.toString()));
        }

        int values[] = bubbleSortJNI(oldValues);
        if(values != null) {
            StringBuilder strBuilder = new StringBuilder();
            for(int i = 0; i < values.length; i++)
                strBuilder.append(values[i]).append(" , ");
            tvSortedArray.setText(StringUtils.removeLastComma(strBuilder.toString()));
        }
        else
            tvSortedArray.setText("values is null");
    }

    void initialiseUIControls() {
        tvUnsortedArray = (TextView) findViewById(R.id.tvUnsortedArray);
        tvSortedArray = (TextView) findViewById(R.id.tvSortedArray);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int[] getRandomListJNI(int length, int maxVal);

    public native int[] bubbleSortJNI(int[] oldValues);

    public native int[] separateZerosJNI(int[] oldValues);
}
