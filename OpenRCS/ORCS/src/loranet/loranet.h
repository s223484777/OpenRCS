#ifndef ORCS_LORA
#define ORCS_LORA

#include<src/objects.h>

void loraInit(String mac);
bool loraUpdate();
void loranetAlert(String msg);
void loranetPage(String msg);
bool loraMessage(Message msg);
bool loraTX(String msg, int access_idx);

extern Status status;
extern Message msg;
extern LoRaConfig conf;

#endif