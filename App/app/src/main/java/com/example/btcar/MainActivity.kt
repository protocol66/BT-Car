package com.example.btcar

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothSocket
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.ImageButton
import org.jetbrains.anko.toast
import java.io.IOException
import java.util.*
import java.util.UUID.fromString

class MainActivity : AppCompatActivity() {

    private val btAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter()
    private val REQUEST_ENABLE_BT = 1
    // Universally Unique Identifier
    private val UUID = fromString("00001101-0000-1000-8000-00805F9B34FB")
    // MAC address of a specific HC-05
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

        // Buttons
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

        // Packet
        val startByte = 0xFF
        var commandByte = 0x00
        val endByte = 0xFE
        startConnection()

        // Whenever a button is pressed, update commandByte
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
                            // Send packet
                            writeByte(startByte)
                            writeByte(commandByte)
                            writeByte(endByte)
                        }
                    } },
                100,
                100
        )

        // Disconnect Button
        val disconnect = findViewById<Button>(R.id.button)
        disconnect?.setOnClickListener{ endConnection() }
    }

    private fun startConnection() {
        val device = btAdapter!!.getRemoteDevice(address)
        Log.d("", "Connecting to ... $device")
        // Notify user of connection attempt
        toast("Connecting to ... ${device.name}  mac: ${device.uuids[0]} address: ${device.address}")
        // Turn off bt discovery to save battery life
        btAdapter.cancelDiscovery()
        try {
            // Starts bt connection to device
            socket = device.createRfcommSocketToServiceRecord(UUID)
            socket.connect()
            Log.d("", "Connected")
            // Notifies user of successful connection
            toast("Connected")
        }
        catch (e: IOException) {
            endConnection()
            Log.d("","Connection Failed")
            // Notifies user of failed connection
            toast("Connection Failed")

        }
    }

    private fun writeByte(byte: Int) {
        try {
            // Send byte over bt
            val out = socket.outputStream
            out.write(byte)
        }
        catch (e: IOException) {
            Log.d("","Failed to send byte")
            // Notify user of failure to send
            toast("Failed to send byte")
        }
    }

    private fun endConnection() {
        try {
            // disconnect from device
            socket.close()
        }
        catch (e:IOException) {
            Log.d("", "Failed to disconnect")
            // Notify user of failure to disconnect
            toast("Failed to disconnect")
        }
    }
}

