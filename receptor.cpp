#include <Keyboard.h>

String inputString = "";
bool stringComplete = false;

void setup() {
  Serial1.begin(9600); // Escuta o ESP8266
  Keyboard.begin();
}

void loop() {
  if (stringComplete) {
    inputString.trim(); // Limpa espaços e quebras de linha

    if (inputString.length() > 0) {
      
      // VERIFICA SE É O COMANDO PARA ABRIR A JANELA
      if (inputString == "###CMD###") {
        abrirCMD();
      } 
      // CASO CONTRÁRIO, APENAS DIGITA O TEXTO RECEBIDO
      else {
        digitarComando(inputString);
      }
    }

    // Limpa
    inputString = "";
    stringComplete = false;
  }
}

// Função 1: Abre a janela do CMD
void abrirCMD() {
  // Win + R
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(100);
  Keyboard.releaseAll();
  delay(500); // Espera o "Executar" aparecer

  // Digita cmd e dá Enter
  Keyboard.print("cmd");
  Keyboard.write(KEY_RETURN);
  delay(500); // Espera a tela preta abrir
}

// Função 2: Digita texto normal + Enter
void digitarComando(String texto) {
  Keyboard.print(texto);
  Keyboard.write(KEY_RETURN);
}

// Leitura da Serial (não precisa alterar)
void serialEvent1() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
