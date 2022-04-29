/**
 * A BLE client example to receive events from an EnOcean PTM215b switch
 *
 *
 * author Jeroen
 */
#include "EnOceanBLEScanner.h"

#define BLE_ADDRESS "e2:15:00:01:6b:89"
#define SECURITY_KEY "C18D85427E74FB9A7CF46C29A760E8C5"

class Handler : public EnOcean::PTM215EventHandler {
public:
    Handler(const uint8_t id) : EnOcean::PTM215EventHandler(id) {};
    virtual ~Handler() {};

    void handleEvent(EnOcean::PTM215Event& event) override {
        log_i("Handling Event by node %d", getId());
        log_i("DeviceAddress: %s", event.device->address.toString().c_str());
        log_i("Event: button %d type %d", event.button, event.eventType);
    }

};

EnOcean::BLEScanner* scanner;
Handler* handler1;
Handler* handler2;

void setup() {
    Serial.begin(115200);
    log_i("Starting EnOcean BLE Example application...");

    scanner = new EnOcean::BLEScanner();
    handler1 = new Handler(1);
    handler2 = new Handler(2);

    NimBLEDevice::init("ESP32_client");

    scanner->initialize();

    log_d("Adding devices");
    // register handler for A0 and B0 buttons using pointer to handler
    scanner->registerPTM215Device(BLE_ADDRESS, SECURITY_KEY, handler1, true, false, true, false);
    // register handler for A1, B0 and B1 buttons, using nodeId of handler
    scanner->registerPTM215Device(BLE_ADDRESS, SECURITY_KEY, 2, false, true, true, true);
    log_i("Initialization done");
    log_i("===========================================");
}

void loop() {
    // Nothing to do here
    delay(1000);
}