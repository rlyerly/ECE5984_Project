package com.pollsensors;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;

import android.hardware.*;

public class SensorStats extends Activity implements SensorEventListener
{
	// Sensor information
	private SensorManager sm;
	private Sensor gyro;
	private Sensor accel;
	private int gyroSampleSpeed;
	private int accelSampleSpeed;
	
	// Miscellaneous members
	private SensorStats me;
	private final static String prevSampleSpeed = "prevSampleSpeed";
	
	/**
	 * Obtains accelerometer/gyroscope handles and registers this activity as a
	 * listener.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_sensor_stats);
		me = this;
		
		//Get sensors
		sm = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
		gyro = sm.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
		accel = sm.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

		//Set sample speed
		if(savedInstanceState != null)
		{	
			//Set sample speeds to previous values
			gyroSampleSpeed = savedInstanceState.getInt(prevSampleSpeed);
			accelSampleSpeed = savedInstanceState.getInt(prevSampleSpeed);
			String speedText = "60000";
			
			//Mark correct radio button
			RadioGroup rg = (RadioGroup)findViewById(R.id.speed_select);
			switch(gyroSampleSpeed)
			{
			case SensorManager.SENSOR_DELAY_NORMAL:
				rg.check(R.id.slow);
				speedText = "200000";
				break;
			case SensorManager.SENSOR_DELAY_UI:
				rg.check(R.id.medium);
				speedText = "60000";
				break;
			case SensorManager.SENSOR_DELAY_GAME:
				rg.check(R.id.fast);
				speedText = "20000";
				break;
			case SensorManager.SENSOR_DELAY_FASTEST:
				rg.check(R.id.fastest);
				speedText = "0";
				break;
			default:
				rg.check(R.id.medium);
				speedText = "60000";
				break;
			}
			
			//Update displayed sample speed
			TextView tv = (TextView)findViewById(R.id.sample_speed);
			tv.setText(speedText);
		}
		else
		{
			//Set sample speeds to default values
			gyroSampleSpeed = SensorManager.SENSOR_DELAY_UI;
			accelSampleSpeed = SensorManager.SENSOR_DELAY_UI;
		}
		
		//Register listeners
		sm.registerListener(this, gyro, gyroSampleSpeed);
		sm.registerListener(this, accel, accelSampleSpeed);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.sensor_stats, menu);
		return true;
	}
	
	/**
	 * Register a listener for the radio buttons to set the sample speed
	 */
	@Override
	public void onResume()
	{
		super.onResume();
		
		//Register a radio button listener to change sample speed
		OnCheckedChangeListener speedListener = new OnCheckedChangeListener()
		{
			@Override
			public void onCheckedChanged(RadioGroup rg, int rb)
			{
				String speedText = "60000";
				switch(rb)
				{
				case R.id.slow:
					gyroSampleSpeed = SensorManager.SENSOR_DELAY_NORMAL;
					accelSampleSpeed = SensorManager.SENSOR_DELAY_NORMAL;
					speedText = "200000";
					break;
				case R.id.medium:
					gyroSampleSpeed = SensorManager.SENSOR_DELAY_UI;
					accelSampleSpeed = SensorManager.SENSOR_DELAY_UI;
					speedText = "60000";
					break;
				case R.id.fast:
					gyroSampleSpeed = SensorManager.SENSOR_DELAY_GAME;
					accelSampleSpeed = SensorManager.SENSOR_DELAY_GAME;
					speedText = "20000";
					break;
				case R.id.fastest:
					gyroSampleSpeed = SensorManager.SENSOR_DELAY_FASTEST;
					accelSampleSpeed = SensorManager.SENSOR_DELAY_FASTEST;
					speedText = "0";
					break;
				default:
					gyroSampleSpeed = SensorManager.SENSOR_DELAY_UI;
					accelSampleSpeed = SensorManager.SENSOR_DELAY_UI;
					speedText = "60000";
					break;
				}
				sm.registerListener(me, gyro, gyroSampleSpeed);
				sm.registerListener(me, accel, accelSampleSpeed);
				
				//Display new sample speed
				TextView tv = (TextView)findViewById(R.id.sample_speed);
				tv.setText(String.valueOf(speedText));
			}
		};
		RadioGroup rg = (RadioGroup)findViewById(R.id.speed_select);
		rg.setOnCheckedChangeListener(speedListener);
	}
	
	/**
	 * When the activity is paused, don't listen for sensor events.
	 */
	@Override
	public void onPause()
	{
		super.onPause();
		
		sm.unregisterListener(this);
	}
	
	/**
	 * Save previous sample speed.
	 */
	@Override
	public void onSaveInstanceState(Bundle savedInstanceState)
	{
		super.onSaveInstanceState(savedInstanceState);
		
		savedInstanceState.putInt(prevSampleSpeed, gyroSampleSpeed);
	}
	
	@Override
	public void onAccuracyChanged(Sensor s, int a)
	{
		// no-op, don't care for now
	}

	/**
	 * Feed data from the sensors to the entropy pool.
	 */
	@Override
	public void onSensorChanged(SensorEvent se)
	{	
		if(se.sensor.getType() == Sensor.TYPE_GYROSCOPE)
		{
			for(float val : se.values)
			{
				//TODO post processing/add to entropy pool
			}
		}
		else
		{
			for(float val : se.values)
			{
				//TODO post processing/add to entropy pool
			}
		}
	}
}
