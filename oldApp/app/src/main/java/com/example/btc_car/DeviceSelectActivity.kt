package com.example.btc_car

import kotlinx.android.synthetic.main.device_select_layout.*;
import android.app.Activity
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.TextView
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import org.jetbrains.anko.toast

class MyAdapter(private val dataset: ArrayList<BluetoothDevice>) :
        RecyclerView.Adapter<MyAdapter.MyViewHolder> () {
    class MyViewHolder (val textView: TextView) : RecyclerView.ViewHolder(textView)

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MyViewHolder {
        val textView = LayoutInflater.from(parent.context).inflate(R.layout.device_select_layout, parent, false) as TextView
        textView.autoSizeMaxTextSize
        return MyViewHolder(textView)
    }

    override fun onBindViewHolder(holder: MyViewHolder, position: Int) {
        holder.textView.text = dataset[position].name
    }

    override fun getItemCount() = dataset.size
}

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
        var recyclerView: RecyclerView
        var viewAdapter: RecyclerView.Adapter<*>
        var viewManager: RecyclerView.LayoutManager

//        pairedDevices?.forEach { device ->
//             val deviceName = device.name
//             val deviceHardwareAddress = device.address // MAC Address
//        }
        if (pairedDevices?.isNotEmpty()!!) {
            for (device in pairedDevices) {
                deviceList.add(device)
            }
        } else {
            toast("No devices paired")
        }

        viewManager = LinearLayoutManager(this)
        viewAdapter = MyAdapter(deviceList)

        recyclerView = findViewById<RecyclerView>(R.id.select_device_list).apply {
            setHasFixedSize(true)
            layoutManager = viewManager
            adapter = viewAdapter
        }
    }
}
