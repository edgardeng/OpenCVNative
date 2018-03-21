package com.edgardeng.opencvnative;

import android.Manifest;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.pm.PackageManager;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.telephony.TelephonyManager;

import android.text.method.ScrollingMovementMethod;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class DeviceInfoActivity extends AppCompatActivity {

    private TextView deviceInfo;

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_deviceinfo);
        deviceInfo = (TextView) findViewById(R.id.textview_info);
        StringBuilder sb = new StringBuilder();
        sb.append(getDeviceInfo());
        sb.append(getDuildInfo());
        sb.append(getNetWorkInfo());
        deviceInfo.setText(sb);
        deviceInfo.setMovementMethod(ScrollingMovementMethod.getInstance());
    }

    private StringBuilder getDeviceInfo() {
        StringBuilder sb = new StringBuilder();

        TelephonyManager phone = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);

        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return sb;
        }
        sb.append("imei(deviceID) : " + phone.getDeviceId() + "\n");
        sb.append("deviceversion（系统版本） : " + phone.getDeviceSoftwareVersion() + "\n" );
        sb.append("imsi : " + phone.getSubscriberId() + "\n" );
        sb.append("number(手机号) : " + phone.getLine1Number() + "\n" );
        sb.append("simserial(sim序列号) : " + phone.getSimSerialNumber() + "\n" );
        sb.append("simoperator(运营商) : " + phone.getSimOperator() + "\n" );
        sb.append("simoperatorname(运营商名) : " + phone.getSimOperatorName() + "\n" );
        sb.append("simcountryiso(国家iso) : " + phone.getSimCountryIso() + "\n" );

        sb.append("workType(网络) : " + phone.getNetworkType() + "\n" );
        sb.append("netcountryiso(网络国家) : " + phone.getNetworkCountryIso() + "\n" );
        sb.append("netoperator(网络运营商) : " + phone.getNetworkOperator() + "\n" );
        sb.append("netoperatorname(网络运营商名) : " + phone.getNetworkOperatorName() + "\n" );

        sb.append("phonetype:" + phone.getPhoneType()+"\n" );
        sb.append("simstate:" + phone.getSimState()+ "\n" );

        // String myIMEI = android.os.SystemProperties.get(android.telephony.TelephonyProperties.PROPERTY_IMEI);
        return sb;
    }

    private StringBuilder getDuildInfo() {
        StringBuilder sb = new StringBuilder();
        sb.append("--- Build --- " + "\n");
        sb.append("serial(序列号) : " + android.os.Build.SERIAL+ "\n");

        sb.append("brand(品牌):" + android.os.Build.BRAND+ "\n" );
        sb.append("tags:" +  android.os.Build.TAGS+ "\n" );
        sb.append("device:" + android.os.Build.DEVICE + "\n" );
        sb.append("fingerprint:" + android.os.Build.FINGERPRINT+ "\n" );
        sb.append("bootloader:" +  Build.BOOTLOADER+ "\n" );
        sb.append("release:" +  Build.VERSION.RELEASE+ "\n" );
        sb.append("sdk:" + Build.VERSION.SDK+ "\n" );
        sb.append("sdk_INT:" + Build.VERSION.SDK_INT+ "\n" );
        sb.append("codename:" + Build.VERSION.CODENAME+ "\n" );
        sb.append("incremental:" + Build.VERSION.INCREMENTAL+ "\n" );
        sb.append("cpuabi:" +  android.os.Build.CPU_ABI+ "\n" );
        sb.append("cpuabi2:" +  android.os.Build.CPU_ABI2+ "\n" );
        sb.append("board:" +  android.os.Build.BOARD+ "\n" );
        sb.append("model:" +  android.os.Build.MODEL+ "\n" );
        sb.append("product:" +  android.os.Build.PRODUCT+ "\n" );
        sb.append("type:" +  android.os.Build.TYPE+ "\n" );
        sb.append("user:" +  android.os.Build.USER+ "\n" );
        sb.append("disply:" +  android.os.Build.DISPLAY+ "\n" );
        sb.append("hardware:" +  android.os.Build.HARDWARE+ "\n" );
        sb.append("host:" +  android.os.Build.HOST+ "\n" );
        sb.append("厂商:" +  android.os.Build.MANUFACTURER+ "\n" );
        sb.append("b_id:" +  Build.ID+ "\n" );
        return  sb;

    }
    
    private StringBuilder getNetWorkInfo() {
        StringBuilder sb = new StringBuilder();
        sb.append("--- Network --- " + "\n");
        
        //获取网络连接管理者
        ConnectivityManager connectionManager = (ConnectivityManager)
                getSystemService(CONNECTIVITY_SERVICE);
        //获取网络的状态信息，有下面三种方式
        @SuppressLint("MissingPermission") NetworkInfo networkInfo = connectionManager.getActiveNetworkInfo();

        sb.append("联网方式:"  + networkInfo.getType() + "\n");
        sb.append("联网方式名:"  + networkInfo.getTypeName()+ "\n");


        @SuppressLint("WifiManagerLeak") WifiManager wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);

        sb.append("radiovis:"  + android.os.Build.getRadioVersion()+ "\n");
        sb.append("wifimac:"  +  wifi.getConnectionInfo().getMacAddress()+ "\n");
        sb.append("ssid:"  + wifi.getConnectionInfo().getSSID()+ "\n");
        sb.append("bssid:"  + wifi.getConnectionInfo().getBSSID()+ "\n");
        sb.append("ip:"  + wifi.getConnectionInfo().getIpAddress() + "\n");
        sb.append("蓝牙MAC:"  +  BluetoothAdapter.getDefaultAdapter()
                .getAddress() + "\n");
        sb.append("蓝牙名:"  +  BluetoothAdapter.getDefaultAdapter().getName()+ "\n"
        );

        sb.append("CPU:"  + getCpuName()+ "\n");

        sb.append("androidID:"  +
                Settings.Secure.getString(getContentResolver(), Settings.Secure.ANDROID_ID)+ "\n");

        return sb;
    }

    /**
     * 获取CPU型号
     * @return
     */
    public static String getCpuName(){

        String str1 = "/proc/cpuinfo";
        String str2 = "";

        try {
            FileReader fr = new FileReader(str1);
            BufferedReader localBufferedReader = new BufferedReader(fr);
            while ((str2=localBufferedReader.readLine()) != null) {
                if (str2.contains("Hardware")) {
                    return str2.split(":")[1];
                }
            }
            localBufferedReader.close();
        } catch (IOException e) {
        }
        return null;

    }

}
