#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ESP_Leonardo_Controle";
const char* password = "senha12345";

ESP8266WebServer server(80);

// HTML com CSS para deixar os botões grandes e fáceis de usar no celular
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta charset="utf-8">
  <style>
    body { font-family: sans-serif; text-align: center; background-color: #222; color: #fff; padding: 20px; }
    h2 { color: #f2f2f2; }
    
    /* Estilo do Botão Abrir CMD */
    .btn-cmd {
      background-color: #ff9800; color: white; padding: 15px 32px;
      font-size: 18px; border: none; border-radius: 8px; cursor: pointer;
      width: 100%; margin-bottom: 30px; display: block;
    }
    
    /* Estilo do Formulário de envio */
    input[type=text] {
      padding: 12px; font-size: 16px; width: 70%; border-radius: 5px; border: none;
    }
    input[type=submit] {
      padding: 12px; font-size: 16px; background-color: #4CAF50; 
      color: white; border: none; border-radius: 5px; cursor: pointer; width: 25%;
    }
    .container { max-width: 500px; margin: auto; }
  </style>
</head>
<body>
  <div class="container">
    <h2>Painel de Controle</h2>

    <button class="btn-cmd" onclick="location.href='/abrir'">1. ABRIR CMD</button>
    
    <hr style="border-color: #444;">
    
    <h3>2. Enviar Comando</h3>
    <form action="/enviar" method="GET">
      <input type="text" name="msg" placeholder="Ex: ipconfig" autofocus>
      <input type="submit" value=">>">
    </form>
  </div>
</body>
</html>
)=====";

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

// Rota para abrir o CMD
void handleAbrir() {
  Serial.println("###CMD###"); // Código secreto para o Leonardo
  server.send(200, "text/html", MAIN_page); // Recarrega a página
}

// Rota para digitar texto
void handleEnviar() {
  String msg = server.arg("msg");
  if (msg.length() > 0) {
    Serial.println(msg);
  }
  server.send(200, "text/html", MAIN_page); // Recarrega a página
}

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password); // Cria a rede Wi-Fi
  
  server.on("/", handleRoot);
  server.on("/abrir", handleAbrir);
  server.on("/enviar", handleEnviar);
  
  server.begin();
}

void loop() {
  server.handleClient();
}
