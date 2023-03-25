package com.skalexey.vocabulary;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.String;

import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Environment;
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

    public static void copyAssets() {
        MainActivity context = (MainActivity) getContext();
        AssetManager assetManager = context.getAssets();
        String[] files = null;
        try {
            files = assetManager.list("");
        } catch (IOException e) {
            Log.e("tag", "Failed to get asset file list.", e);
        }
        for (String filename : files) {
            InputStream in = null;
            OutputStream out = null;
            try {
                in = assetManager.open(filename);

                String outDir = getTempDir();

                File outFile = new File(outDir, filename);

                out = new FileOutputStream(outFile);
                copyFile(in, out);
                in.close();
                in = null;
                out.flush();
                out.close();
                out = null;
            } catch (IOException e) {
                Log.e("tag", "Failed to copy asset file: " + filename, e);
            }
        }
    }

    private static void copyFile(InputStream in, OutputStream out) throws IOException {
        byte[] buffer = new byte[1024];
        int read;
        while ((read = in.read(buffer)) != -1) {
            out.write(buffer, 0, read);
        }
    }

	public static String getTempDir()
	{
		MainActivity context = (MainActivity)getContext();
		return context.getCacheDir().getAbsolutePath();
	}

	public static String getResourcesDir()
	{
		MainActivity context = (MainActivity)getContext();
		return context.getDataDir().getAbsolutePath();
	}

	public static void showKeyboard()
	{
		MainActivity context = (MainActivity)getContext();
		InputMethodManager imm = (InputMethodManager)context.getSystemService(Context.INPUT_METHOD_SERVICE);
		android.view.View view = getContentView();
		imm.showSoftInput(view, InputMethodManager.SHOW_IMPLICIT);
	}
}
