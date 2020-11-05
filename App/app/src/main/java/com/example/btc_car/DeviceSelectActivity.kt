package com.example.btc_car

import kotlinx.android.synthetic.main.device_select_layout.*;
import android.app.Activity
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.AdapterView
import android.widget.ArrayAdapter
import org.jetbrains.anko.toast


class DeviceSelectActivity : AppCompatActivity() {

    private val btAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter()
    private val REQUEST_ENABLE_BT = 1

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.device_select_layout)

        if (btAdapter == null) {
            // Device doesn't support Bluetooth
            toast("This device does not support Bluetooth")
            return
        }
        if (!btAdapter.isEnabled) {
            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
        }

        select_device_list.setOnClickListener{ pairedDevicesList() }
    }

    private fun pairedDevicesList() {
        val pairedDevices : Set<BluetoothDevice>? = btAdapter?.bondedDevices
        val deviceList : ArrayList<BluetoothDevice> = ArrayList()
        pairedDevices?.forEach { device ->
            val deviceName = device.name
            val deviceHardwareAddress = device.address // MAC Address
        }
        if (pairedDevices?.isNotEmpty()!!) {
            for (device in pairedDevices) {
                deviceList.add(device)
            }
        } else {
            toast("No devices paired")
        }

        val adapter = ArrayAdapter(this, android.R.layout.simple_list_item_1, deviceList)

    }
}
