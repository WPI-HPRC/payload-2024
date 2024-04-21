#include "Flash.h"

FlashChip::FlashChip() {
    
}

void FlashChip::init() {
    Serial.println("[Flash Chip]: Beginning initialization");
    flash = new SPIFlash(10);
    nextAddress = 0; 
    String data  = ""; 

    if(flash->begin()){
        Serial.println("Flash Found");
    }
    else{
        while(true){
            Serial.println("1"); 
        }
    }

    capacity = flash->getCapacity();
    maxPage = flash->getMaxPage();
    
    
    Serial.println("====Flash Chip Configuration====");
    Serial.print("Flash Capacity: "); Serial.println(capacity);
    Serial.print("Max Page: "); Serial.println(maxPage);
    Serial.println("[Flash Chip]: Initialization Complete");

//     while (nextAddress < 16777216 ){
       
//     flash->readStr(nextAddress, data, true);
//     Serial.println(data);
//      if(data.equals("")){
//             while(true){
//                 //Serial.println("Stuck"); 
//             }
//     }

//     nextAddress += 256; 
//   }

//   while(true){
//     //Serial.println("2"); 
//   }

}

int FlashChip::rememberAddress() {


    for(int i=0; i < maxPage; i++) {
        uint32_t pageAddress = 0 + (i * 256);

        uint8_t * buffer = new uint8_t[255];

        for(int j=0; j < 255; j++) {
            buffer[j] = flash->readByte(pageAddress + j);
        }
        

        bool isUnwritten = true;
        for(uint32_t k = 0; k < 255; k++) {
            if(buffer[k] != 255) {
                isUnwritten = false;
                break;
            }
        }
        
        delete[] buffer;

        if(isUnwritten) {
            nextAddress = pageAddress;
            return pageAddress;
        }
    }

    return 0;
}

bool FlashChip::writeStruct(String structString) {
    if(nextAddress == capacity) {
        return false;
    }
    
    flash->writeStr(nextAddress, structString);
    nextAddress = nextAddress + 256;  
    Serial.println(nextAddress); 
    return true;
}


bool FlashChip::eraseMemory() {
    if(!flash->eraseChip()) {
        return false;
    }
    return true;

}