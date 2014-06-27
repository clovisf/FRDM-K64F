#include "mbed.h"
#include "SDFileSystem.h"
#include "DHT.h"
 
SDFileSystem sd(PTE3, PTE1, PTE2, PTE4, "sd"); //MOSI, MISO, SCLK, SSEL. Tested on K64F, correct pins.
AnalogIn LM35(PTB2);
int count=0;
DigitalOut RedLed(LED1); // Error indication
DigitalOut GreenLed(LED2); // LM35 read indication
DigitalOut Blueled(LED3); // DHT11 read indication
DHT sensor(PTB20,DHT11); // Use the DHT11 sensor, on pin 

 
int main() {
    int err;
    wait(1); // wait 1 second for DHT11 to stabilyze
    
    printf("Hello World!\n");   
 
    mkdir("/sd/mydir", 0777);
    
    FILE *fp = fopen("/sd/mydir/data001.csv", "w");
    if(fp == NULL) {
        error("Could not open file for write \n");
        RedLed = 0;
        GreenLed = 1;
        Blueled= 1;
        }
    while (1) {
    
    RedLed = 1;
    GreenLed = 1;
    Blueled= 1;
    if (count < 10000000){
        count++;
        } else{  
        // --------------------------
         Blueled = 0;
        err = sensor.readData();
        if (err == 0) {
            printf("Temperature is %4.2f \r\n",sensor.ReadTemperature(CELCIUS));
            //printf("Temperature is %4.2f F \r\n",sensor.ReadTemperature(FARENHEIT));
            //printf("Temperature is %4.2f K \r\n",sensor.ReadTemperature(KELVIN));
            printf("Humidity is %4.2f \r\n",sensor.ReadHumidity());
            //printf("Dew point is %4.2f  \r\n",sensor.CalcdewPoint(sensor.ReadTemperature(CELCIUS), sensor.ReadHumidity()));
            //printf("Dew point (fast) is %4.2f  \r\n",sensor.CalcdewPointFast(sensor.ReadTemperature(CELCIUS), sensor.ReadHumidity()));
        } else
            printf("\r\nErr %i \n",err);
        Blueled = 1;
        RedLed= 0;
        GreenLed= 1;
        // ----------------------------  
    FILE *fp = fopen("/sd/mydir/data001.csv", "a");
    if(fp == NULL) {
        error("Could not open file for write\n");
        RedLed = 0;
        GreenLed = 1;
        Blueled= 1;
    }
    
    RedLed = 1;
    GreenLed = 0;
    fprintf(fp, "%f\r",333.333*LM35.read(),",");
    fprintf(fp, "%f\r",sensor.ReadTemperature(CELCIUS),",");
    fprintf(fp, "%f\r",sensor.ReadHumidity(),",");
    fclose(fp);  
    printf("Goodbye World!\n");
    count=0;
    }
    }
    }
