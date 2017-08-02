package com.example.api_5;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.*;

public class MainActivity extends Activity {
	
	SurfaceView view;
	SurfaceHolder  holder;
	TextView text;
	Button btn1,btn2;
	int mWidth = 0;
	int mHeight = 0;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		RelativeLayout mLayout = (RelativeLayout)findViewById(R.id.mainLayout);
		mLayout.setBackgroundColor(Color.parseColor("#000000"));
		view = (SurfaceView)findViewById(R.id.surface);
		//text = (TextView)findViewById(R.id.view);
		btn1 = (Button)findViewById(R.id.button1);
		btn1.setOnClickListener(new OnClickListener()
				{

					@Override
					public void onClick(View arg0) {
						// TODO Auto-generated method stub
						setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
					}
			
				});
		btn2 = (Button)findViewById(R.id.button2);
		btn2.setOnClickListener(new OnClickListener()
				{

					@Override
					public void onClick(View arg0) {
						// TODO Auto-generated method stub
						setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
					}
			
				});
		mWidth = view.getWidth();
		mHeight = view.getHeight();
		holder = view.getHolder();
		holder.addCallback(new SurfaceHolder.Callback() {
			@Override
			public void surfaceDestroyed(SurfaceHolder arg0) {
				// TODO Auto-generated method stub	
			}
			
			@Override
			public void surfaceCreated(SurfaceHolder arg0) {
				// TODO Auto-generated method stub
				loadFile(holder.getSurface(),mWidth,mHeight);
				
				new Thread(new Runnable() 
				{
					public void run()
					{
						//text.setText("run");
						stingFromJNI();
					}
				}).start();
			}
			
			@Override
			public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3) {
				// TODO Auto-generated method stub
				//text.setText("surfaceChanged");
				
			}
		});
		
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	public native String stingFromJNI();
	
	public native boolean loadFile(Surface view,int width,int heigth);
	static {
		System.loadLibrary("hello-jni");
		System.loadLibrary("avcodec-57");
		System.loadLibrary("avfilter-6");
		System.loadLibrary("avutil-55");
		System.loadLibrary("avformat-57");
		System.loadLibrary("swresample-2");
		System.loadLibrary("swscale-4");
	}
}
