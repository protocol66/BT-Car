package com.example.btcar

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.ImageButton
import android.widget.SeekBar
import org.jetbrains.anko.toast
import java.io.IOException
import java.util.*
import java.util.UUID.fromString

class MainActivity : AppCompatActivity() {

    private val btAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter()
    private val REQUEST_ENABLE_BT = 1
    private val UUID = fromString("00001101-0000-1000-8000-00805F9B34FB")
    private val address = "00:18:91:D9:1A:73"

    lateinit var socket: BluetoothSocket

    private val timer = Timer()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if (btAdapter == null) {
            // Device doesn't support Bluetooth
            toast("This device does not support Bluetooth")
            return
        }
        if (!btAdapter.isEnabled) {
            // Bluetooth is disabled, ask to enable it
            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
        }
//        val pairedDevices: Set<BluetoothDevice>? = btAdapter.bondedDevices
//        pairedDevices?.forEach { device ->
//            val deviceName = device.name
//            val deviceHardwareAddress = device.address // MAC address
//        }

        val forwardMax = findViewById<ImageButton>(R.id.forwardMax)
        val forward = findViewById<ImageButton>(R.id.forward)
        val backMax = findViewById<ImageButton>(R.id.backMax)
        val back = findViewById<ImageButton>(R.id.back)
        val fLeftMax = findViewById<ImageButton>(R.id.fLeftMax)
        val fLeft = findViewById<ImageButton>(R.id.fLeft)
        val fRightMax = findViewById<ImageButton>(R.id.fRightMax)
        val fRight = findViewById<ImageButton>(R.id.fRight)
        val bLeftMax = findViewById<ImageButton>(R.id.bLeftMax)
        val bLeft = findViewById<ImageButton>(R.id.bLeft)
        val bRightMax = findViewById<ImageButton>(R.id.bRightMax)
        val bRight = findViewById<ImageButton>(R.id.bRight)
        val dLeft = findViewById<ImageButton>(R.id.donutLeft)
        val dRight = findViewById<ImageButton>(R.id.donutRight)
        val stop = findViewById<ImageButton>(R.id.stop)

        val startByte = 0xFF
        val endByte = 0xFE
        var commandByte = 0x00

        startConnection()

        forwardMax?.setOnClickListener{
            commandByte = 0x02
        }

        forward?.setOnClickListener{
            commandByte = 0x04
        }

        backMax?.setOnClickListener{
            commandByte = 0x06
        }

        back?.setOnClickListener{
            commandByte = 0x08
        }

        fLeftMax?.setOnClickListener{
            commandByte = 0x0A
        }

        fLeft?.setOnClickListener{
            commandByte = 0x0C
        }

        fRightMax?.setOnClickListener{
            commandByte = 0x12
        }

        fRight?.setOnClickListener{
            commandByte = 0x14
        }

        bLeftMax?.setOnClickListener{
            commandByte = 0x16
        }

        bLeft?.setOnClickListener{
            commandByte =0x18
        }

        bRightMax?.setOnClickListener{
            commandByte = 0x1A
        }

        bRight?.setOnClickListener{
            commandByte = 0x1C
        }

        dLeft?.setOnClickListener{
            commandByte = 0x22
        }

        dRight?.setOnClickListener{
            commandByte = 0x24
        }

        stop?.setOnClickListener{
            commandByte = 0xF0
        }

        // Send packet every 100 ms
        timer.scheduleAtFixedRate(
                object : TimerTask() {
                    override fun run() {
                        if ( commandByte != 0x00 ) {
                            writeByte(startByte)
                            writeByte(commandByte)
                            writeByte(endByte)
                        }
                    } },
                100,
                100
        )

        val disconnect = findViewById<Button>(R.id.button)
        disconnect?.setOnClickListener{ endConnection() }
    }

    private fun startConnection() {
        val device = btAdapter!!.getRemoteDevice(address)
        Log.d("", "Connecting to ... $device")
        toast("Connecting to ... ${device.name}  mac: ${device.uuids[0]} address: ${device.address}")
        btAdapter.cancelDiscovery()
        try {
            socket = device.createRfcommSocketToServiceRecord(UUID)
            socket.connect()
            Log.d("", "Connected")
            toast("Connected")
        }
        catch (e: IOException) {
            endConnection()
            Log.d("","Connection Failed")
            toast("Connection Failed")

        }
    }

    private fun writeByte(byte: Int) {
        try {
            val out = socket.outputStream
            out.write(byte)
        }
        catch (e: IOException) {
            Log.d("","Failed to send byte")
            toast("Failed to send byte")
        }
    }

    private fun endConnection() {
        try {
            socket.close()
        }
        catch (e:IOException) {
            Log.d("", "Failed to disconnect")
            toast("Failed to disconnect")
        }
    }
}

