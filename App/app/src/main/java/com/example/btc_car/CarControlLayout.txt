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

    companion object {
        var myUUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
        var btSocket: BluetoothSocket? = null
        lateinit var m_progress: ProgressDialog
        lateinit var btAdapter: BluetoothAdapter
        var isConnected: Boolean = false
        lateinit var address: String
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.car_control_layout)
        address = intent.getStringExtra(DeviceSelectActivity.EXTRA_ADDRESS).toString()

        ConnectToDevice(this).execute()

        //control_led_on.setOnClickListener { sendCommand("a") }
        //control_led_off.setOnClickListener { sendCommand("b") }
        //control_led_disconnect.setOnClickListener { disconnect() }
    }

    private fun sendCommand(input: String) {
        if (btSocket != null) {
            try{
                btSocket!!.outputStream.write(input.toByteArray())
            } catch(e: IOException) {
                e.printStackTrace()
            }
        }
    }

    private fun disconnect() {
        if (btSocket != null) {
            try {
                btSocket!!.close()
                btSocket = null
                isConnected = false
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        finish()
    }

    private class ConnectToDevice(c: Context) : AsyncTask<Void, Void, String>() {
        private var connectSuccess: Boolean = true
        private val context: Context = c

        override fun onPreExecute() {
            super.onPreExecute()
            m_progress = ProgressDialog.show(context, "Connecting...", "please wait")
        }

        override fun doInBackground(vararg p0: Void?): String? {
            try {
                if (btSocket == null || !isConnected) {
                    btAdapter = BluetoothAdapter.getDefaultAdapter()
                    val device: BluetoothDevice = btAdapter.getRemoteDevice(address)
                    btSocket = device.createInsecureRfcommSocketToServiceRecord(myUUID)
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery()
                    btSocket!!.connect()
                }
            } catch (e: IOException) {
                connectSuccess = false
                e.printStackTrace()
            }
            return null
        }

        override fun onPostExecute(result: String?) {
            super.onPostExecute(result)
            if (!connectSuccess) {
                Log.i("data", "couldn't connect")
            } else {
                isConnected = true
            }
            m_progress.dismiss()
        }
    }
}