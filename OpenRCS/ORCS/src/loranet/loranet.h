#ifndef ORCS_LORA
#define ORCS_LORA

#include<src/config.h>
#include<src/objects.h>

// Signatures
void loraInit(String mac);
bool loraUpdate();
void loranetAlert(String msg);
void loranetPage(String msg);
bool loraMessage(Message msg);
bool loraTX(String msg, int access_idx);

// Global variables
extern Status status;
extern Message msg;
extern LoRaConfig conf;
extern IOMgr iomgr;

#endif