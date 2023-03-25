package com.skalexey.vocabulary;

import java.lang.String;
import android.util.Log;
import java.io.File;
import android.view.inputmethod.InputMethodManager;
import android.content.Context;
import org.libsdl.app.SDLActivity; 

/**
 * A sample wrapper class that just calls SDLActivity 
 */ 

public class MainActivity extends SDLActivity
{
	private final static String TAG = MainActivity.class.getSimpleName();
	public static String getTempDir()
    {
        Log.v(TAG, "MainActivity.getTempDir");
        MainActivity context = (MainActivity)getContext();
        return context.getCacheDir().getAbsolutePath();
    }

    public static void showKeyboard()
    {
        Log.v(TAG, "MainActivity.showKeyboard");
        MainActivity context = (MainActivity)getContext();
        InputMethodManager imm = (InputMethodManager)context.getSystemService(Context.INPUT_METHOD_SERVICE);
        android.view.View view = getContentView();
        imm.showSoftInput(view, InputMethodManager.SHOW_IMPLICIT);
    }
}
