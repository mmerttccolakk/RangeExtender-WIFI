#include <ESP8266WiFi.h>
#include <lwip/napt.h>
#include <lwip/dns.h>
#include <LwipDhcpServer.h>

String STASSID = "MIYY";
String STAPSK = "yagmur2009";
String NEWSTASSID = "MIYNEW";
String NEWSTAPSK = "yagmur2009";

void setup() {
// first, connect to STA so we can get a proper local DNS server
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }

  // give DNS servers to AP side
  dhcpSoftAP.dhcps_set_dns(0, WiFi.dnsIP(0));
  dhcpSoftAP.dhcps_set_dns(1, WiFi.dnsIP(1));

  WiFi.softAPConfig(  // enable AP, with android-compatible google domain
    IPAddress(10, 0, 1, 1),//SOFT_AP_Local_IP
    IPAddress(10, 0, 1, 1),//SOFT_AP_Gateway
    IPAddress(255, 255, 255, 0)); //SOFT_AP_Subnet

  WiFi.softAP(NEWSTASSID, NEWSTAPSK);

  ESP.getFreeHeap();

}


void loop() {

}
