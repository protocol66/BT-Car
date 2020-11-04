package com.example.btc_car


import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.content.Context
import android.os.AsyncTask
import android.util.Log
import java.io.IOException
import java.util.*


class CarControlActivity: AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.car_control_layout)
    }
}
