#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>

//#define SSID 		"Chien"
//#define PASSWORD	"307140311"


#define SSID 		"yyb"
#define PASSWORD	"a12345678"
//#define SSID 		"No.2"
//#define PASSWORD	"0975335365"

//#define SSID 		"Benjamin's S6 edge"
//#define PASSWORD	"0930392215"

//#define SSID 		"EE6018"
//#define PASSWORD	"smallyellow"



void print_(unsigned char* text , uint8_t length);
void print_ln(unsigned char* text , uint8_t length);
void print_2(unsigned char* text , uint8_t length);
void print_ln2(unsigned char* text , uint8_t length);
void ESP();



uint16_t voltsMeasured = 0;
float calcVoltage=0.0f;
float dustDensity=0.0f;
char pdust[21];
char DataRead[25];


void gets1USART(char *buffer, unsigned char len);
void get_pm(void);
void ESP_Initialize();
int ESP_flag;
void sleep(unsigned int x);
void GPS_read_data();
extern unsigned int timecount;

    
void main(void)
{
    // Initialize the device
    
    SYSTEM_Initialize();
    ADC_Initialize();
    EUSART1_Initialize();
    EUSART2_Initialize();
    TMR0_Initialize();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    
    int m_TASK=1;
    unsigned int oldtimecount =0;
    static char ip[4];
   do
    {  
        ESP_Initialize();
    }while(ESP_flag == 0);
    oldtimecount = timecount;
    
    while((timecount - oldtimecount)<10000 );

    esp8266_ip(ip);

    char data_test[6] = "hello";
    char wait[8]="CONNECT";
    char GPSd_[]="lat:22.626852,lng:120.266734";
    char alldata[80];
    _esp8266_waitFor(wait);
    print_ln(data_test,strlen(data_test));

    
    while(1){
//        EUSART1_Write(48+m_TASK);
        switch(m_TASK){
            case 1:
                get_pm();
                m_TASK = 2;
                oldtimecount = timecount;
                break;
            
            case 2:
                if((timecount-oldtimecount)<10000){
                    m_TASK=2;
                }
                else{
                    print_ln(data_test,strlen(data_test));
//                    GPS_read_data();
                    m_TASK = 3;
                }
                break;
                
            case 3:
                strcat(alldata,pdust);
                strcat(alldata,GPSd_);
//                strcat(alldata,DataRead);
                esp8266_send(alldata);
                memset(alldata,'\0',sizeof(alldata));
                m_TASK = 4 ;
            case 4:
                oldtimecount = timecount;
                while((timecount - oldtimecount)<50000 );
                m_TASK = 1;
                break;
            
            default:
                m_TASK = 1;
                break;     
        }
        
    }//while

}



void print_(unsigned char* text , uint8_t length){
    
    for(int i = 0 ; i<length ; i++){
        EUSART1_Write(text[i]);
    }
}

void print_ln(unsigned char* text , uint8_t length){
    //length--;
    for(int i = 0 ; i<length ; i++){
        EUSART1_Write(text[i]);
    }
    EUSART1_Write('\n');
}



void gets1USART(char *buffer, uint8_t len)
 {
   uint8_t i;    // Length counter
   unsigned char data;
 
   for(i=0;i<len;i++)  // Only retrieve len characters
   {
     while(!EUSART1_is_tx_ready());// Wait for data to be received
 
     data = EUSART1_Read();    // Get a character from the USART
                            // and save in the string
     *buffer = data;
     buffer++;              // Increment the string pointer
   }
 }



void get_pm(void){
    int TASK =1;
    unsigned int oldtimecount1 =0;
    unsigned int oldtimecount2 =0;
    unsigned int oldtimecount3 =0;
    unsigned int oldtimecount4 =0;
//    char c1[]="read value   = " ;
//    char V[] ="calVoltage   = " ;
//    char D[] ="Dust Density = " ;
//    char unit[]="ug/m3"         ;
    

    while (TASK!=7)
    {  
        
        switch(TASK){

            case 1://LED_ON
                PM_LED_LAT = 0;
                oldtimecount1 = timecount;
                TASK = 2;
                //EUSART1_Write('1');
                break;

            case 2://DATA_READY
                if( (timecount - oldtimecount1)<14 )
                {
                    //EUSART1_Write('2');
                    break;
                }
                else
                {
                    ADC_SelectChannel(channel_AN9);
                    ADC_StartConversion();
                    TASK =3;
                    //EUSART1_Write('2');
                }
                    
                
                break;

            case 3://GET_ADC
                if(ADC_IsConversionDone()){
                    voltsMeasured = ADC_GetConversionResult();//uint16_t
                    TASK = 4;
                    oldtimecount2 = timecount;
                    //EUSART1_Write('3');
                    }
                break;

            case 4://LED_OFF
                if( (timecount - oldtimecount2) < 2 ) {
                    break;
                }
                else{
                    PM_LED_LAT = 1;
                    TASK = 5;
                    oldtimecount3 = timecount;
                }
                //EUSART1_Write('4');
                break; 

            case 5://Count
                if( (timecount - oldtimecount3) < 484 ) 
                {
                    break;
                }
                else{

                    calcVoltage = (float)voltsMeasured * 5.0f / 1024.0f;
                    dustDensity = (15 * calcVoltage - 0.0999f);
//                    dustDensity = (0.172 * calcVoltage - 0.0999)*1000.0;

                    char p_V[32] , p_calV[15];
//                    sprintf(p_V    , "%d" ,   voltsMeasured );
//                    sprintf(p_calV , "%f" ,   calcVoltage   );
                    sprintf(pdust  , "averagepm25:%f," ,   dustDensity   );

//                    print_(c1 , strlen(c1)); //"GP2Y1010AU0F readings"
//                    print_ln( p_V , strlen(p_V));

//                    print_(V , strlen(V));   //"Voltage = ";
//                    print_ln( p_calV ,strlen(p_calV));
//                    print_( D , strlen(D) );//"Dust Density = ";

                    print_(pdust , strlen(pdust));//sizeofpdustis8

//                    print_ln(unit , strlen(unit));//"ug/m3"
                    TASK = 6;
                    oldtimecount4 = timecount ;
                }
                //EUSART1_Write('5');
                break;
            case 6:
                if( (timecount - oldtimecount4) < 50000 ){
                    break;
                }
                
                else
                {
                    EUSART1_Write(0x0D);
                    TASK = 7;
                }
                    
                //EUSART2_Write('6');
                break;

        
        default:
            TASK = 1;
        }
    }
}


void ESP_Initialize(){

	int ESP_TASK =1;
    ESP_flag = 0 ;
    unsigned int oldtimecount1 =0;
    unsigned int oldtimecount2 =0;
    unsigned int oldtimecount3 =0;
    unsigned int oldtimecount4 =0;
    unsigned int oldtimecount5 =0;
    
	while(ESP_TASK != 7){
		switch(ESP_TASK){
			case 1:
				esp8266_isStarted();
				ESP_TASK = 2;
                oldtimecount1 = timecount;
				break;
			case 2:
                if((timecount - oldtimecount1)<100 ){
                    ESP_TASK = 2;
                }
                else{
                    esp8266_mode(1);
                    ESP_TASK = 3;
                    oldtimecount2 = timecount;
                    esp8266_connect(SSID,PASSWORD);
                }
				break;
			case 3:
                if((timecount - oldtimecount2)<10000 ){
                    ESP_TASK = 3;
                }
				else{
//                    if(esp8266_connect(SSID,PASSWORD) == ESP8266_OK){
//                        ESP_TASK = 4;
//                        oldtimecount3 = timecount;
//                    }
//                    else{
//                        ESP_TASK=3;
//                    }
                    ESP_TASK = 4;
                    esp8266_CIPMUX(1);
				}
                
				break;
			case 4:
                if((timecount - oldtimecount3)<10000 ){
                    ESP_TASK = 4;
                }
                else{
//                    esp8266_CIPMUX(1);
                    ESP_TASK = 6;
                    esp8266_server(1);
                    oldtimecount4 = timecount;
                }

				break;
			case 5:
                if((timecount - oldtimecount4)<10000 ){
                    ESP_TASK = 5;
                }
                else{
//                    if(esp8266_server(1) == ESP8266_OK){
//                        ESP_TASK = 6;
//                        oldtimecount5 = timecount;
//                    }
//                    else{
//                        ESP_TASK = 5;
//                    }
                    ESP_TASK=6;
                }
				break;
			case 6:
//                if((timecount - oldtimecount5) <10000 ){
//                    ESP_TASK = 5;
//                } 
//                else{
                    esp8266_SLEEP(0);
                    ESP_flag =1;
                    ESP_TASK = 7;
//                }
				break;
			default:
				ESP_TASK = 6;
				break;
		}
	}
}


void print_2(unsigned char* text , uint8_t length){
    
    for(int i = 0 ; i<length ; i++){
        EUSART2_Write(text[i]);
    }
}

void print_ln2(unsigned char* text , uint8_t length){
    //length--;
    for(int i = 0 ; i<length ; i++){
        EUSART2_Write(text[i]);
    }
    EUSART2_Write('\n');
}




void GPS_read_data(){
    //print_ln(timecount,strlen(timecount));
    
    char buf; 
    int readmoney;
    int readGPSMC;
    int dotCount = 0;
    char Databuf[25];
    int addr = 0;
    unsigned int GPSoldtimecount=0;
    int i;
    char p[2];
    char a[6];
    char dotcount_is_7[] ="dotCount = 7";
    char databuf[] ="Databuf ";
    char data_reset[] ="dotreset";
//    char hello[6]="fuck";
    int GPS_flag = 0;
    GPSoldtimecount= timecount;
    while((timecount-GPSoldtimecount)<10000);
    
//    print_()
//    EUSART1_Write('I');
    while(GPS_flag ==0){
//         gets1USART(buf, 1);
        buf = EUSART2_Read();
//        EUSART1_Write('K');
        switch(buf){
            case '$':
//                EUSART2_Write('x');
                readmoney = 1;       //??????RW????1
                break;

            case '!':
//                print_2(DataRead,strlen(DataRead));//Serial.print(DataRead);
                addr=0;
                break;
            case ',':
//                EUSART2_Write('y');
//                print_ln2(hello,strlen(hello));
                if(readGPSMC == 1 ){
//                  EUSART2_Write('p');
                    dotCount++;

                    if(dotCount == 7){
//                        print_ln2(dotcount_is_7,strlen(dotcount_is_7));//Serial.println("dotCount = 7 ");
                        dotCount = 0;
                        readmoney = 0 ;
                        readGPSMC = 0 ;
                        addr = 0;
    //                    for(i=0;i<=25;i++){
    ////                        print_2(databuf,strlen(databuf));//Serial.print("Databuf ") ;
    ////                        print_2((char)i,strlen(i));//Serial.print(i) ;
    ////                        print_2('=',1);//Serial.print("= ") ;
    ////                        print_ln2(Databuf[i],strlen(Databuf[i]));//Serial.println(Databuf[i]); 
    //                    }

                        strcpy(DataRead,Databuf);
                        EUSART1_Write('>');
                        print_ln(DataRead,strlen(DataRead));
                        GPS_flag = 1;
//                        GPSoldtimecount=timecount;
//                        while((timecount-GPSoldtimecount)<500 );
                        break;
                  }
                  if(dotCount==3){
                    memset(Databuf, '\0', sizeof(Databuf));
                    addr = 0;
                  }
                }

                break;

              default:  
//                EUSART2_Write('z');
                if(readmoney==1){
//                    for(i=0;i<5;i++)  
                    Databuf[addr]=buf;
                    addr++;
                }

                if(addr == 5){
                    int c;
                    for(c=0;c<5;c++)
                    {
                       a[c]=Databuf[c]; 
                    }
                    a[5]=0x00;

                    if(strcmp(a,"GPRMC") == 0){
//                      char GPS_readed[] ="Greaded";
//                      print_ln2(GPS_readed,strlen(GPS_readed));
                      readGPSMC = 1;                         //?KW=1??GPRMC????????????
                      addr = 0;
//                      char Data_in[]="Din";
//                      print_ln2(Data_in,strlen(Data_in));
                    }else if (readGPSMC == 0){               //?KW=1?addr??5????
                      readmoney = 0;                         //?KW=0???GPRMC????RW?addr???????
                      addr = 0;

                    }else{
                        char GPS_readed_Error[]="GError";
//                        print_ln2(GPS_readed_Error,strlen(GPS_readed_Error));
                    }
                  }
                  break;       
            }
      }//while
    
}





/*
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>


//#define SSID 		"Chien"
//#define PASSWORD	"307140311"


//#define SSID 		"yyb"
//#define PASSWORD	"a12345678"
#define SSID 		"No.2"
#define PASSWORD	"0975335365"

//#define SSID 		"Benjamin's S6 edge"
//#define PASSWORD	"0930392215"


void print_(unsigned char* text , uint8_t length);
void print_ln(unsigned char* text , uint8_t length);
void print_2(unsigned char* text , uint8_t length);
void print_ln2(unsigned char* text , uint8_t length);
void ESP();



uint16_t voltsMeasured = 0;
float calcVoltage=0.0f;
float dustDensity=0.0f;
char pdust[21];

void gets1USART(char *buffer, unsigned char len);
void get_pm(void);
void ESP_Initialize();
int ESP_flag;
void sleep(unsigned int x);
void GPS_read_data();
void GPS_readall();
extern unsigned int timecount;

    
void main(void)
{
    // Initialize the device
    
    SYSTEM_Initialize();
    ADC_Initialize();
    EUSART1_Initialize();
    EUSART2_Initialize();
    TMR0_Initialize();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    
    
    while(1){
    GPS_read_data();
    }

    }



void print_(unsigned char* text , uint8_t length){
    
    for(int i = 0 ; i<length ; i++){
        EUSART1_Write(text[i]);
    }
}

void print_ln(unsigned char* text , uint8_t length){
    //length--;
    for(int i = 0 ; i<length ; i++){
        EUSART1_Write(text[i]);
    }
    EUSART1_Write('\n');
}

void gets1USART(char *buffer, uint8_t len)
 {
   uint8_t i;    // Length counter
   unsigned char data;
 
   for(i=0;i<len;i++)  // Only retrieve len characters
   {
     while(!EUSART1_is_tx_ready());// Wait for data to be received
 
     data = EUSART1_Read();    // Get a character from the USART
                            // and save in the string
     *buffer = data;
     buffer++;              // Increment the string pointer
   }
 }





void print_2(unsigned char* text , uint8_t length){
    
    for(int i = 0 ; i<length ; i++){
        EUSART2_Write(text[i]);
    }
}

void print_ln2(unsigned char* text , uint8_t length){
    //length--;
    for(int i = 0 ; i<length ; i++){
        EUSART2_Write(text[i]);
    }
    EUSART2_Write('\n');
}

void GPS_read_data(){
    //print_ln(timecount,strlen(timecount));
    
    char buf; 
    int readmoney;
    int readGPSMC;
    int dotCount = 0;
    char Databuf[25];
    char DataRead[25];
    int addr = 0;
    unsigned int GPSoldtimecount=0;
    int i;
    char p[2];
    char a[6];
//    char dotcount_is_7[] ="dotCount = 7";
//    char databuf[] ="Databuf ";
//    char data_reset[] ="dotreset";
//    char hello[6]="fuck";
    int GPS_flag = 0;
    GPSoldtimecount= timecount;
    while((timecount-GPSoldtimecount)<10000);
    
//    print_()
//    EUSART1_Write('I');
    while(GPS_flag ==0){
//         gets1USART(buf, 1);
        buf = EUSART2_Read();
//        EUSART1_Write('K');
        switch(buf){
            case '$':
//                EUSART2_Write('x');
                readmoney = 1;       //??????RW????1
                break;

            case '!':
//                print_2(DataRead,strlen(DataRead));//Serial.print(DataRead);
                addr=0;
                break;
            case ',':
//                EUSART2_Write('y');
//                print_ln2(hello,strlen(hello));
                if(readGPSMC == 1 ){
//                  EUSART2_Write('p');
                    dotCount++;

                    if(dotCount == 7){
//                        print_ln2(dotcount_is_7,strlen(dotcount_is_7));//Serial.println("dotCount = 7 ");
                        dotCount = 0;
                        readmoney = 0 ;
                        readGPSMC = 0 ;
                        addr = 0;
    //                    for(i=0;i<=25;i++){
    ////                        print_2(databuf,strlen(databuf));//Serial.print("Databuf ") ;
    ////                        print_2((char)i,strlen(i));//Serial.print(i) ;
    ////                        print_2('=',1);//Serial.print("= ") ;
    ////                        print_ln2(Databuf[i],strlen(Databuf[i]));//Serial.println(Databuf[i]); 
    //                    }

                        strcpy(DataRead,Databuf);
                        EUSART2_Write('>');/////
                        print_ln2(DataRead,strlen(DataRead));////
                        GPS_flag = 1;
//                        GPSoldtimecount=timecount;
//                        while((timecount-GPSoldtimecount)<500 );
                        break;
                  }
                  if(dotCount==3){
                    memset(Databuf, '\0', sizeof(Databuf));
                    addr = 0;
                  }
                }

                break;

              default:  
//                EUSART2_Write('z');
                if(readmoney==1){
//                    for(i=0;i<5;i++)  
                    Databuf[addr]=buf;
                    addr++;
                }

                if(addr == 5){
                    int c;
                    for(c=0;c<5;c++)
                    {
                       a[c]=Databuf[c]; 
                    }
                    a[5]=0x00;

                    if(strcmp(a,"GPRMC") == 0){
//                      char GPS_readed[] ="Greaded";
//                      print_ln2(GPS_readed,strlen(GPS_readed));
                      readGPSMC = 1;                         //?KW=1??GPRMC????????????
                      addr = 0;
//                      char Data_in[]="Din";
//                      print_ln2(Data_in,strlen(Data_in));
                    }else if (readGPSMC == 0){               //?KW=1?addr??5????
                      readmoney = 0;                         //?KW=0???GPRMC????RW?addr???????
                      addr = 0;

                    }else{
                        char GPS_readed_Error[]="GError";
//                        print_ln2(GPS_readed_Error,strlen(GPS_readed_Error));
                    }
                  }
                  break;       
            }
//        EUSART2_Write('0');
//        print_ln2(DataRead,strlen(DataRead));
      }//while
    
}

/*
void GPS_read_data(){

    
    char buf; 
    int readmoney;
    int readGPSMC;
    int dotCount = 0;
    char Databuf[25];
    char DataRead[25];
    int addr = 0;
    unsigned int GPSoldtimecount=0;
    int i;
    char p[2];
    char a[6];
    char dotcount_is_7[] ="dotCount = 7";
    char databuf[] ="Databuf ";
    char data_reset[] ="dotreset";
    char hello[6]="fuck";
    while(1){
//         gets1USART(buf, 1);
        buf = EUSART2_Read();
        switch(buf){
            case '$':
//                EUSART2_Write('x');
                readmoney = 1;       //??????RW????1
                break;

            case '!':
//                print_2(DataRead,strlen(DataRead));//Serial.print(DataRead);
                addr=0;
                break;
            case ',':
//                EUSART2_Write('y');
//                print_ln2(hello,strlen(hello));
                if(readGPSMC == 1 ){
//                  EUSART2_Write('p');
                    dotCount++;
//                  sprintf(p,"%d",dotCount);
//                  print_2(p,strlen(p));
                    if(dotCount == 7){
//                        print_ln2(dotcount_is_7,strlen(dotcount_is_7));//Serial.println("dotCount = 7 ");
                        dotCount = 0;
                        readmoney = 0 ;
                        readGPSMC = 0 ;
                        addr = 0;
    //                    for(i=0;i<=25;i++){
    ////                        print_2(databuf,strlen(databuf));//Serial.print("Databuf ") ;
    ////                        print_2((char)i,strlen(i));//Serial.print(i) ;
    ////                        print_2('=',1);//Serial.print("= ") ;
    ////                        print_ln2(Databuf[i],strlen(Databuf[i]));//Serial.println(Databuf[i]); 
    //                    }

                        strcpy(DataRead,Databuf);
                        EUSART2_Write('>');
                        print_ln2(DataRead,strlen(DataRead));
                        
                        GPSoldtimecount=timecount;
                        while((timecount-GPSoldtimecount)<500 );
                        break;
                  }
                  if(dotCount==3){
//                    print_ln2(data_reset,strlen(data_reset));//Serial.println("data reset");
                    memset(Databuf, '\0', sizeof(Databuf));
                    addr = 0;
                  }
                }

                break;

              default:  
//                EUSART2_Write('z');
                if(readmoney==1){
//                    for(i=0;i<5;i++)  
                    Databuf[addr]=buf;
                    addr++;
                }

                if(addr == 5){
                    int c;
                    for(c=0;c<5;c++)
                    {
                       a[c]=Databuf[c]; 
                    }
                    a[5]=0x00;

                    if(strcmp(a,"GPRMC") == 0){
                      char GPS_readed[] ="Greaded";
//                      print_ln2(GPS_readed,strlen(GPS_readed));
                      readGPSMC = 1;                         //?KW=1??GPRMC????????????
                      addr = 0;
                      char Data_in[]="Din";
//                      print_ln2(Data_in,strlen(Data_in));
                    }else if (readGPSMC == 0){               //?KW=1?addr??5????
                      readmoney = 0;                         //?KW=0???GPRMC????RW?addr???????
                      addr = 0;

                    }else{
                        char GPS_readed_Error[]="GError";
//                        print_ln2(GPS_readed_Error,strlen(GPS_readed_Error));
                    }
                  }
                  break;       
            }
//        EUSART2_Write('0');
//        print_ln2(DataRead,strlen(DataRead));
      }//while
 
}
*/
 
