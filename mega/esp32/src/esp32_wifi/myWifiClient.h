#include <WiFi.h>

class MyWifiClient {
    public:
        MyWifiClient();
        void initWiFi(String hostName);
        String myWiFiReadString();
        bool connectWithRFID(String rfid);
        void sendToServer(String msg);
        String recieveFromServer();
    private:
        WiFiClient client = NULL;
        String host[3] = {"esp32_1", "esp32_2", "esp32_3"};
        String password = "12345678";
        String serverIP = "192.168.4.1";
        String rfid[4] = {"13329ad", "6911b40", "56420d9", "82f5f85"};
        int serverPort = 80;
};