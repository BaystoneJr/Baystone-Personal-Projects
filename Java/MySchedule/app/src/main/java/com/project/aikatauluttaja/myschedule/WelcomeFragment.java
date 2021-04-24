package com.project.aikatauluttaja.myschedule;

import android.content.Context;
import android.net.Uri;
import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;


import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

public class WelcomeFragment extends Fragment {
    private Button setupButton;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_welcome, container, false);

        setupButton = view.findViewById(R.id.toSetupButton);

        setupButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                InfoSetupFragment infoSetupFragment = new InfoSetupFragment();
                MainActivity.fragmentManager.beginTransaction().replace(R.id.fragment_container, infoSetupFragment).addToBackStack(null).commit();

            }
        });

        return view;
    }
}
