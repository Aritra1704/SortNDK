package com.arpaul.sortndk;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class StartActivity extends AppCompatActivity {

    private Button btnSort, btnPalindrome, btnFibonacci, btnBinarySearch;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_start);

        initaliseUIControls();

        bindControls();
    }

    void bindControls() {
        btnSort.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(StartActivity.this, SortActivity.class));
            }
        });

        btnPalindrome.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(StartActivity.this, PalindromeActivity.class));
            }
        });

        btnFibonacci.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(StartActivity.this, FibonacciActivity.class));
            }
        });

        btnBinarySearch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(StartActivity.this, BinarySearchActivity.class));
            }
        });
    }

    void initaliseUIControls() {
        btnSort             = (Button)findViewById(R.id.btnSort);
        btnPalindrome       = (Button)findViewById(R.id.btnPalindrome);
        btnFibonacci        = (Button)findViewById(R.id.btnFibonacci);
        btnBinarySearch     = (Button)findViewById(R.id.btnBinarySearch);
    }
}
