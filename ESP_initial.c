



#define SSID 		"No.2"
#define PASSWORD	"0975335365"

void ESP_Initialize(){


	int ESP_TASK =1;


	while(ESP_TASK != 8;){
		switch(ESP_TASK){
			case 1:
				esp8266_isStarted();
				ESP_TASK = 2;
				break;
			case 2:
				esp8266_mode(1);
				ESP_TASK = 3;
				break;
			case 3:
				if(esp8266_connect(SSID,PASSWORD) == ESP8266_OK){
					ESP_TASK = 4;
				}
				else{
					ESP_TASK = 3;
				}
				break;
			case 4:
				esp8266_CIPMUX(1);
				ESP_TASK = 5;
				break;
			case 5:
				if(esp8266_server(1,8080) == ESP8266_OK){
					ESP_TASK = 6;
				}
				else{
					ESP_TASK = 5;
				}
				break;
			case 6:
				esp8266_SLEEP(0);
				ESP_TASK = 7;
				break;
			default:
				ESP_TASK = 1;
				break;
		}
	}


	//ESP8266_ConnectionMode(SINGLE);		/* 0 = Single; 1 = Multi */
	ESP8266_ApplicationMode(NORMAL);	/* 0 = Normal Mode; 1 = Transperant Mode */

	if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)
	ESP8266_JoinAccessPoint(SSID, PASSWORD);
	ESP8266_Start(0, DOMAIN, PORT);
	while(1)
	{
		Connect_Status = ESP8266_connected();




		if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)
		ESP8266_JoinAccessPoint(SSID, PASSWORD);
		if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
		ESP8266_Start(0, DOMAIN, PORT);

		#ifdef SEND_DEMO
		memset(_buffer, 0, 150);
		sprintf(_buffer, "GET /update?api_key=%s&field1=%d", API_WRITE_KEY, Sample++);
		ESP8266_Send(_buffer);
		MSdelay(20000);	/* Thingspeak server delay */
		#endif
		
		#ifdef RECEIVE_DEMO
		memset(_buffer, 0, 150);
		sprintf(_buffer, "GET /channels/%s/feeds/last.txt", CHANNEL_ID);
		ESP8266_Send(_buffer);
		Read_Data(_buffer);
		MSdelay(600);
		#endif
	}
}
