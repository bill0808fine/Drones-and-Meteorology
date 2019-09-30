void GPS_read_data(){
    //print_ln(timecount,strlen(timecount));
    /*if(timecount-GPSoldtimecount>1000){
        print_(Databuf, 25);
        GPSoldtimecount=timecount;
    }*/
    
    char buf; 
    int readmoney;
    int readGPSMC;
    int dotCount = 0;
    char Databuf[25];
    char DataRead[25];
    int addr = 0;
    int GPSoldtimecount;
    int i;

    char a[5];
    char dotcount_is_7[] ="dotCount = 7";
    char databuf[] ="Databuf ";
    char data_reset[] ="data reset";

        while(1){
        // gets1USART(buf, 1);
        EUSART1_Read(buf);
        switch(buf){
            case '$':
                readmoney = 1;       //??????RW????1
                break;

            case '!':
                print_(DataRead,strlen(DataRead));//Serial.print(DataRead);
                addr=0;
                break;
            case ',':
                if(readGPSMC == 1 ){
                  dotCount++;
                  if(dotCount == 7){
                    print_ln(dotcount_is_7,strlen(dotcount_is_7));//Serial.println("dotCount = 7 ");
                    dotCount = 0;
                    readmoney = 0 ;
                    readGPSMC = 0 ;
                    addr = 0;
                    for(i=0;i<=25;i++){
                      print_(databuf,strlen(databuf));//Serial.print("Databuf ") ;
                      // print_((char)i,strlen(i));//Serial.print(i) ;
                      // print_('=',1);//Serial.print("= ") ;
                      print_ln(Databuf[i],strlen(Databuf[i]));//Serial.println(Databuf[i]); 
                    }

                    strcpy(DataRead,Databuf);
                    break;
                  }
                  if(dotCount==3){
                    print_ln(data_reset,strlen(data_reset));//Serial.println("data reset");
                    memset(Databuf, '\0', sizeof(Databuf));
                    addr = 0;
                  }
                }

                break;

              default:  
                if(readmoney==1){
                  Databuf[addr]=buf;
                  addr++;
                }

                if(addr == 5){
                    for(int c=0;c<5;c++)
                    {
                       a[c]=Databuf[c]; 
                    }
                  //char a[5] = {Databuf[0],Databuf[1],Databuf[2],Databuf[3],Databuf[4]};

                  if(strcmp(a,"GPRMC") == 0){
                    char GPS_readed[] ="GPS readed";
                    print_ln(GPS_readed,strlen(GPS_readed));
                    readGPSMC = 1;                         //?KW=1??GPRMC????????????
                    addr = 0;
                    char Data_in[]="Data in";
                    print_ln(Data_in,strlen(Data_in));//Serial.println("Data in");
                  }else if (readGPSMC == 0){               //?KW=1?addr??5????
                    readmoney = 0;                         //?KW=0???GPRMC????RW?addr???????
                    addr = 0;
                    
                  }else{
                    char GPS_readed_Error[]="GPS readed Error";
                    print_ln(GPS_readed_Error,strlen(GPS_readed_Error));
                    char Data_in[]="Data in";
                    print_ln(Data_in,strlen(Data_in));//Serial.println("Data in");
                  }
                }
                break;       
        }
      }//while
    
}


void GPS_readall(){
    char GPSreadall_buf[];
    //memset(GPSreadall_buf,0,64);
    //print_("1",1);
    gets1USART(GPSreadall_buf,1);
    print_(GPSreadall_buf,1);
    //EUSART1_Write(GPSreadall_buf);
}