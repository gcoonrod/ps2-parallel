// Copyright 2023 Greg Coonrod
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <TimerThree.h>

#define PS2_CLK 42
#define PS2_DATA 40
#define IRQA 52
#define IRQB 50
#define PA5 48
#define PA6 46
#define PA7 44

const char PDATA[] = {36, 34, 32, 30, 28, 26, 24, 22};

void setup() {
    pinMode(PS2_CLK, OUTPUT);
    pinMode(PS2_DATA, OUTPUT);

    digitalWrite(PS2_CLK, HIGH);
    digitalWrite(PS2_DATA, HIGH);

    pinMode(IRQA, INPUT);
    pinMode(IRQB, INPUT);

    for (int n = 0; n < 8; n++){
        pinMode(PDATA[n], INPUT);
    }
    
    attachInterrupt(digitalPinToInterrupt(IRQA), onIRQA, RISING);

    Timer3.initialize(5000000UL); // Every 1 seconds
    Timer3.attachInterrupt(sendScanCodeOnISR);
    
    Serial.begin(115200);
}

void ps2SendBit(uint8_t bit) {
    digitalWrite(PS2_CLK, LOW);
    delayMicroseconds(10);
    //delay(10000);
    digitalWrite(PS2_DATA, bit);
    delayMicroseconds(10);
    //delay(10000);
    digitalWrite(PS2_CLK, HIGH);
    //delay(10000);
}

void ps2SendByte(byte packet) {
    ps2SendBit(LOW);    // Start bit
    for (uint8_t i = 0; i < 8; ++i) {   // 8 data bits
        ps2SendBit(packet & 1);
        packet >>= 1;
    }
    ps2SendBit(__builtin_parity((unsigned int)packet)); // odd parity
    ps2SendBit(HIGH); // stop bit
}

void sendScanCodeOnISR() {
    //send start bit
    cli();
    ps2SendByte(0x15);
    Serial.println("Sending scan code.");
    sei();
}

void onIRQA() {
    cli();
    char output[7];
    unsigned int data = 0;
    for (int i = 0; i < 8; i++) {
        int bit = digitalRead(PDATA[i] ? 1 : 0);
        Serial.print(bit);
        data = (data << 1) + bit;
    }
    Serial.print("  ");

    sprintf(output, " %02x", data);
    Serial.print(output);
    Serial.println();
    sei();
}

void loop() {
    // Do nothing in the loop
}