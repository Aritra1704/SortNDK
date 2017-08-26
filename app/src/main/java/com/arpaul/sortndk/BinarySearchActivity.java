package com.arpaul.sortndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.arpaul.utilitieslib.StringUtils;

public class BinarySearchActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-c-lib");
    }

    static {
        System.loadLibrary("native-binarysearch");
    }

    private TextView tvUnsortedArray, tvSorted, tvSearchResult;
    private EditText edtSearch;
    private Button btnSearch;

    private int oldValues[];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_binary_search);

        intialiseUIControls();

        oldValues = getRandomListJNI(100, 1000);
        tvUnsortedArray.setText(getStringFromIntArray(oldValues));

        final int sortedList[] = quicksortSortJNI(oldValues);
        tvSorted.setText(getStringFromIntArray(sortedList));

        btnSearch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int searchVal = StringUtils.getInt(edtSearch.getText().toString());
                int result = binarySearchJNI(sortedList, searchVal);
                if(result >= 0 )
                    tvSearchResult.setText("Found at position: " + result);
                else
                    tvSearchResult.setText("Not Found.");
            }
        });
    }

    private String getStringFromIntArray(int values[]) {
        StringBuilder strBuilder = new StringBuilder();
        for(int i = 0; i < values.length; i++)
            strBuilder.append(values[i]).append(", ");
        return StringUtils.removeLastComma(strBuilder.toString());
    }

    void intialiseUIControls() {
        tvUnsortedArray     = (TextView) findViewById(R.id.tvUnsortedArray);
        tvSorted            = (TextView) findViewById(R.id.tvSorted);
        tvSearchResult      = (TextView) findViewById(R.id.tvSearchResult);

        edtSearch           = (EditText) findViewById(R.id.edtSearch);

        btnSearch           = (Button) findViewById(R.id.btnSearch);
    }

    public native int[] getRandomListJNI(int length, int maxVal);

    public native int[] quicksortSortJNI(int[] oldValues);

    public native int binarySearchJNI(int[] values, int search);
}
