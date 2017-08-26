package com.arpaul.sortndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.arpaul.utilitieslib.StringUtils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PalindromeActivity extends AppCompatActivity {

    private TextView tvNormalPalindrome, tvDMAPalindrome;
    private EditText edtActualNumber;
    private Button btnPalinCheck;

    static {
        System.loadLibrary("native-palindrome");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_palindrome);

        initialiseUIControls();

         btnPalinCheck.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String inputString = edtActualNumber.getText().toString();
                Pattern p = Pattern.compile("^[0-9]*$");
                Matcher m = p.matcher(inputString);
                if(m.matches()) {
                    long actualNumber = StringUtils.getLong(inputString);

                    boolean isPalindrome = normalPalindromeJNI(actualNumber);
                    tvNormalPalindrome.setText("" + isPalindrome);
                } else {
                    boolean isPalindrome = stringPalindromeJNI(inputString);
                    tvNormalPalindrome.setText("" + isPalindrome);
                }
            }
        });

    }

    void initialiseUIControls() {
        edtActualNumber         = (EditText) findViewById(R.id.edtActualNumber);

        btnPalinCheck           = (Button) findViewById(R.id.btnPalinCheck);

        tvNormalPalindrome      = (TextView) findViewById(R.id.tvNormalPalindrome);
        tvDMAPalindrome         = (TextView) findViewById(R.id.tvDMAPalindrome);
    }

    public native boolean normalPalindromeJNI(long actualNumber);
    public native boolean stringPalindromeJNI(String actualString);
}
