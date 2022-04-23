/**
 * A BLE client example to receive events from an Enocean PTM215b switch
 * 
 * 
 * author Jeroen
 */

#include "enocean_PTM215b.h"

#define BLE_ADDRESS "e2:15:00:01:6b:89"
#define SECURITY_KEY "C18D85427E74FB9A7CF46C29A760E8C5"

class EH : public PTM215b::Eventhandler {
public:
    EH() {};
    virtual ~EH() {};

    void handleEvent(PTM215b::SwitchEvent& evt) override {

        std::string type;
        switch (evt.eventType) {
            case PTM215b::EventType::Pushed:
                type = "Pushed";
                break;
            case PTM215b::EventType::Repeat:
                type = "Repeat";
                break;
            case PTM215b::EventType::ReleaseLong:
                type = "ReleasedLong";
                break;
            case PTM215b::EventType::ReleaseShort:
                type = "ReleasedShort";
                break;
            default:
                break;
        }

        std::string direction = (evt.button == PTM215b::Button::A_UP || evt.button == PTM215b::Button::B_UP) ? "Up" : "Down";

        Serial.print("BleSwitchEvent Received: Node Id: "); Serial.print(evt.nodeId);
        Serial.print(", Type: "); Serial.print(type.c_str());
        Serial.print(", Direction: "); Serial.println(direction.c_str());
    };

};

EH handler;
PTM215b::Enocean_PTM215b enocean_PTM215b(handler, true);

void setup(){
    delay(1100);
    Serial.begin(115200);
    Serial.println(F("Starting Enocean_PTM215b BLE Example application..."));

    BLEDevice::init("ESP32_client");
    enocean_PTM215b.initialize();

    enocean_PTM215b.registerBleSwitch(BLE_ADDRESS, SECURITY_KEY, 0, 1, 2 , 3);
}

void loop(){
    delay(1000);
} 