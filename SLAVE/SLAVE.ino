#include <esp_now.h>
#include <WiFi.h>              

const int ledConfirmacao = 2;

const uint8_t macAddrMestre1[] = { 0x94, 0xE6, 0x86, 0x3D, 0x6D, 0x1C }; // Endereço MAC do dispositivo mestre 1. Coloque o endereço MAC de sua placa aqui
const uint8_t macAddrMestre2[] = { 0xEC, 0x62, 0x60, 0x93, 0xC8, 0xBC }; // Endereço MAC do dispositivo mestre 2. Coloque o endereço MAC de sua placa aqui

typedef struct struct_message {

    float temperaturaEnviada;
    float umidadeEnviada;

    float temperatura;
    float umidade;
} struct_message;

struct_message myData;


typedef struct dadosSensores {
  float temperatura;
  float umidade;
} dadosSensores;

dadosSensores dadosSensor1;

void OnDataRecv(const uint8_t * macAddrMestre1, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println("-----------------------------------------------------------");
  Serial.println("-----------------------------------------------------------");
  Serial.println("DADOS SENSOR 1");
  Serial.print(myData.umidadeEnviada);
  Serial.println("%");
  Serial.print(myData.temperaturaEnviada);
  Serial.println("ºC");
  Serial.println("-----------------------------------------------------------");

  Serial.println("-----------------------------------------------------------");
  Serial.println("DADOS SENSOR 2");
  Serial.print(dadosSensor1.umidade);
  Serial.println("%");
  Serial.print(dadosSensor1.temperatura);
  Serial.println("ºC");
  Serial.println("-----------------------------------------------------------");
  Serial.println("-----------------------------------------------------------");

}


void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledConfirmacao, OUTPUT);

  WiFi.disconnect();    // Desconecta de qualquer rede WiFi previamente conectada
  WiFi.mode(WIFI_STA);  // Define o modo WiFi como Station (cliente)
  Serial.begin(115200);
  Serial.println(WiFi.macAddress());

  if (esp_now_init() == ESP_OK) {   // Inicializa o ESP-NOW e verifica se há erros
  digitalWrite(ledConfirmacao, 1);
                 
  } else if(esp_now_init() != ESP_OK ){
  digitalWrite(ledConfirmacao, 1);
  delay(500);
  digitalWrite(ledConfirmacao, 0);
  delay(500);
  
     ESP.restart();  
  }

   esp_now_register_recv_cb(OnDataRecv);
   //esp_now_register_recv_cb(OnDataRecv2);
}

void loop() {

  delay(1);  // Delay de 1 milissegundo
}