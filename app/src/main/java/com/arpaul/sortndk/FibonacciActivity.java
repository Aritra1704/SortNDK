package com.arpaul.sortndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.arpaul.utilitieslib.StringUtils;

public class FibonacciActivity extends AppCompatActivity {

    private EditText edtFibLength;
    private Button btnFibonacci;
    private TextView tvDMAFib, tvNormalFib;

    static {
        System.loadLibrary("native-fibonacci");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fibonacci);

        initialiseUIControls();

        btnFibonacci.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int length = StringUtils.getInt(edtFibLength.getText().toString());

                int fibSeries[] = normalFibonacciJNI(length);
                if(fibSeries != null) {
                    StringBuilder strBuilder = new StringBuilder();
                    for(int i = 0; i < fibSeries.length; i++)
                        strBuilder.append(fibSeries[i]).append(" , ");
                    tvNormalFib.setText(StringUtils.removeLastComma(strBuilder.toString()));
                }

                int fibrecurSeries[] = recurFibonacciJNI(length);
                if(fibrecurSeries != null) {
                    StringBuilder strBuilder = new StringBuilder();
                    for(int i = 0; i < fibrecurSeries.length; i++)
                        strBuilder.append(fibrecurSeries[i]).append(" , ");
                    tvDMAFib.setText(StringUtils.removeLastComma(strBuilder.toString()));
                }
            }
        });
    }

    void initialiseUIControls() {
        edtFibLength            = (EditText) findViewById(R.id.edtFibLength);

        btnFibonacci            = (Button) findViewById(R.id.btnFibonacci);

        tvDMAFib                = (TextView) findViewById(R.id.tvDMAFib);
        tvNormalFib             = (TextView) findViewById(R.id.tvNormalFib);
    }

    public native int[] normalFibonacciJNI(int length);
    public native int[] recurFibonacciJNI(int length);
}
