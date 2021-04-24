package com.project.aikatauluttaja.myschedule;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentActivity;
import androidx.fragment.app.FragmentManager;

import android.os.Bundle;
import android.widget.Button;

public class MainActivity extends FragmentActivity {

    public static FragmentManager fragmentManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.fragment_welcome);

        fragmentManager = getSupportFragmentManager();

        if(findViewById(R.id.fragment_container) != null) {
            if(savedInstanceState != null) {
                return;
            }

            WelcomeFragment firstFragment = new WelcomeFragment();

            firstFragment.setArguments(getIntent().getExtras());


            fragmentManager.beginTransaction()
                    .add(R.id.fragment_container, firstFragment).commit();
        }
    }


}
