package com.pollsensors;

import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;
import android.view.WindowManager;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;

import android.hardware.*;

import java.io.*;
import java.util.ArrayList;

public class SensorStats extends Activity implements SensorEventListener {

	private SensorManager sm;
	private Sensor gyro;
	private Sensor accel;
	
	private static final int maxEvents = 10000000;
	private static final int eventsBeforeWrite = 1000;
	private static final int eventsBeforeUIUpdate = 100;
	private int numEvents;
	private ArrayList<Float> gyroVals;
	private ArrayList<Float> accelVals;
	
	private final String dataDir = "/sensor_data";
	private final String gyroFilename = "/gyro_vals.dat";
	private final String accelFilename = "/accel_vals.dat";
	
	private SensorStats me;
	private OnCheckedChangeListener speed_listener;
	private static boolean started = false;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		if(!started)
		{
			numEvents = 0;
			clearPrevFiles();
			gyroVals = new ArrayList<Float>(3 * eventsBeforeWrite);
			accelVals = new ArrayList<Float>(3 * eventsBeforeWrite);
			
			//Keep screen on
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
			//Get sensors & register listeners
			sm = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
			accel = sm.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
			gyro = sm.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
			//TODO checking for other accelerators/gyroscopes
			sm.registerListener(this, accel, SensorManager.SENSOR_DELAY_UI);
			sm.registerListener(this, gyro, SensorManager.SENSOR_DELAY_UI);
			started = true;
		}
		
		setContentView(R.layout.activity_sensor_stats);
		System.out.println("In \"onCreate\"");
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.sensor_stats, menu);
		return true;
	}
	
	@Override
	public void onResume() {
		super.onResume();
		
		RadioGroup rg = (RadioGroup)findViewById(R.id.sample_select);
		me = this;
		speed_listener = new OnCheckedChangeListener()
		{
			@Override
			public void onCheckedChanged(RadioGroup rg, int rb) {
				sm.unregisterListener(me);
				int delay = SensorManager.SENSOR_DELAY_NORMAL;
				switch(rb)
				{
				case R.id.slow:
					delay = SensorManager.SENSOR_DELAY_NORMAL;
					break;
				case R.id.medium:
					delay = SensorManager.SENSOR_DELAY_UI;
					break;
				case R.id.fast:
					delay = SensorManager.SENSOR_DELAY_GAME;
					break;
				case R.id.no_delay:
					delay = SensorManager.SENSOR_DELAY_FASTEST;
					break;
				default:
					delay = SensorManager.SENSOR_DELAY_NORMAL;
				}
				sm.registerListener(me, gyro, delay);
				sm.registerListener(me, accel, delay);
			}
		};
		rg.setOnCheckedChangeListener(speed_listener);
	}
	
	@Override
	public void onPause() {
		super.onPause();
		// no-op, we want to keep collecting sensor stats in the background
	}
	
	@Override
	public void onAccuracyChanged(Sensor s, int a) {
		// no-op, don't care
	}

	@Override
	public void onSensorChanged(SensorEvent se) {
		TextView tv;
		
		if(se.sensor.getType() == Sensor.TYPE_GYROSCOPE)
			for(float val : se.values)
				gyroVals.add(val);
		else
			for(float val : se.values)
				accelVals.add(val);
		
		numEvents++;
		if(numEvents >= maxEvents)
		{
			cleanup();
			tv = (TextView)findViewById(R.id.cur_sample_num);
			tv.setText(numEvents + " (finished)");
		}
		else if((numEvents % eventsBeforeUIUpdate) == 0)
		{
			tv = (TextView)findViewById(R.id.cur_sample_num);
			tv.setText(String.valueOf(numEvents));
			
			if((numEvents % eventsBeforeWrite) == 0 && sdCardAvailable())
			{
				writeToSDCard();
				gyroVals.clear();
				accelVals.clear();
			}
		}
	}
	
	public void cleanup()
	{	
		sm.unregisterListener(this);
		if(sdCardAvailable())
			writeToSDCard();
		//TODO write to a different internal location
	}
	
	private boolean sdCardAvailable()
	{
		System.out.println("SD Card status: " + Environment.getExternalStorageState());
		return ((Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED))
				? true : false);
	}
	
	private void clearPrevFiles()
	{
		File gyroFile, accelFile;
		gyroFile = new File(Environment.getExternalStorageDirectory() + dataDir
				+ gyroFilename);
		if(gyroFile.exists())
			gyroFile.delete();
		accelFile = new File(Environment.getExternalStorageDirectory() + dataDir
				+ accelFilename);
		if(accelFile.exists())
				accelFile.delete();
	}
	
	private void writeToSDCard()
	{
		File root, dir, gyroFile, accelFile;
		FileWriter writer;
		int i = 0;
		
		root = android.os.Environment.getExternalStorageDirectory();
		System.out.println("SD Card directory: " + root);
		dir = new File(root.getAbsolutePath() + dataDir);
		System.out.println("Directory: " + dir);
		if(!dir.mkdirs())
			System.out.println("Could not make parent directory!");
		
		try
		{	
			gyroFile = new File(dir.getAbsolutePath() + gyroFilename);
			System.out.println("Gyrofile: " + gyroFile);
			if(!gyroFile.exists())
				gyroFile.createNewFile();
			accelFile = new File(dir.getAbsolutePath() + accelFilename);
			System.out.println("Accelfile: " + accelFile);
			if(!accelFile.exists())
				accelFile.createNewFile();
			
			writer = new FileWriter(gyroFile, true);
			for(Float val : gyroVals)
			{
				writer.write(Integer.toHexString(Float.floatToRawIntBits(val)) + " ");
				i++;
				if((i % 3) == 0)
				{
					i = 0;
					writer.write("\n");
				}
			}
			writer.close();
			
			writer = new FileWriter(accelFile, true);
			for(Float val : accelVals)
			{
				writer.write(Integer.toHexString(Float.floatToRawIntBits(val)) + " ");
				i++;
				if((i % 3) == 0)
				{
					i = 0;
					writer.write("\n");
				}
			}
			writer.close();
		}
		catch(IOException ioe)
		{
			ioe.printStackTrace();
			System.exit(-1);
		}
	}
}
