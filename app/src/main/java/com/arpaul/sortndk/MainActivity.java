package com.arpaul.sortndk;

import android.support.v4.view.PagerTitleStrip;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import com.arpaul.utilitieslib.StringUtils;

import java.util.LinkedHashMap;

public class MainActivity extends AppCompatActivity {

    private TextView tvUnsortedArray;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    static {
        System.loadLibrary("native-c-lib");
    }

    //https://developer.android.com/studio/projects/add-native-code.html

    private ViewPager vpSorts;
    private PagerTitleStrip ptsSorts;

    private SortPagerAdapter adapter;
    private int oldValues[];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initialiseUIControls();

        oldValues = getRandomListJNI(100, 1000);
        if(oldValues != null) {
            StringBuilder strBuilder = new StringBuilder();
            for(int i = 0; i < oldValues.length; i++)
                strBuilder.append(oldValues[i]).append(" , ");
            tvUnsortedArray.setText(StringUtils.removeLastComma(strBuilder.toString()));
        }

        getAllSorts();
    }

    private void getAllSorts() {
        LinkedHashMap<String, String> hashSorts = new LinkedHashMap<>();
        hashSorts.put("Bubble Sort", getStringFromIntArray(bubbleSortJNI(oldValues)));

        hashSorts.put("Insertion Sort", getStringFromIntArray(insertionSortJNI(oldValues)));

        hashSorts.put("Selection Sort", getStringFromIntArray(selectionSortJNI(oldValues)));

        hashSorts.put("Merge Sort", getStringFromIntArray(mergeSortJNI(oldValues)));

        hashSorts.put("Quick Sort", getStringFromIntArray(quicksortSortJNI(oldValues)));

        adapter.refresh(hashSorts);
    }

    private String getStringFromIntArray(int values[]) {
        StringBuilder strBuilder = new StringBuilder();
        for(int i = 0; i < values.length; i++)
            strBuilder.append(values[i]).append(", ");
        return StringUtils.removeLastComma(strBuilder.toString());
    }

    void initialiseUIControls() {
        tvUnsortedArray     = (TextView) findViewById(R.id.tvUnsortedArray);

        vpSorts             = (ViewPager) findViewById(R.id.vpSorts);
        ptsSorts            = (PagerTitleStrip) findViewById(R.id.ptsSorts);


        adapter = new SortPagerAdapter(this, new LinkedHashMap<String, String>());
        vpSorts.setAdapter(adapter);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int[] getRandomListJNI(int length, int maxVal);

    public native int[] bubbleSortJNI(int[] oldValues);

    public native int[] insertionSortJNI(int[] oldValues);

    public native int[] selectionSortJNI(int[] oldValues);

    public native int[] mergeSortJNI(int[] oldValues);

    public native int[] quicksortSortJNI(int[] oldValues);

    public native int[] separateZerosJNI(int[] oldValues);
}
