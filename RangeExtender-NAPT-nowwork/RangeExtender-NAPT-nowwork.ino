#define STASSID "MIYY"
#define STAPSK  "yagmur2009"

#include <ESP8266WiFi.h>
#include <lwip/napt.h>
#include <lwip/dns.h>
#include <LwipDhcpServer.h>

#define NAPT 1000
#define NAPT_PORT 10


void setup() {
  Serial.begin(115200);
 ESP.getFreeHeap();
  // first, connect to STA so we can get a proper local DNS server
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.printf("\nSTA: %s (dns: %s / %s)\n",
                WiFi.localIP().toString().c_str(),
                WiFi.dnsIP(0).toString().c_str(),
                WiFi.dnsIP(1).toString().c_str());

  // give DNS servers to AP side
  dhcpSoftAP.dhcps_set_dns(0, WiFi.dnsIP(0));
  dhcpSoftAP.dhcps_set_dns(1, WiFi.dnsIP(1));

  WiFi.softAPConfig(
    IPAddress(172, 217, 28, 254),
    IPAddress(172, 217, 28, 254),
    IPAddress(255, 255, 255, 0));
  WiFi.softAP(STASSID "extender", STAPSK);
  Serial.println("AP:" + WiFi.softAPIP().toString());

  if (ip_napt_init(NAPT, NAPT_PORT) == ERR_OK) {
    ip_napt_enable_no(SOFTAP_IF, 1);
  }

}


void loop() {
}

