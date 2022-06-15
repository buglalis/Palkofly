// Подключение библиотек SPI и SD:
#include <SPI.h>
#include <SD.h>
 
// установка переменных, используемых функциями библиотеки SD:
Sd2Card card;
SdVolume volume;
SdFile root;
 
// измените эту переменную  в зависимости от подключения модуля и использования шилдов;
// Ethernet shield: пин 4
const int chipSelect = 4;
 
void setup() {
  // Инициализация сериал порта:
  Serial.begin(9600);
  while (!Serial) {
    ; // ожидание подключения к Serial порту. Только для собственных USB портов
  }
 
 
  Serial.print("\nInitializing SD card...");
 
 
  // инициализация карты, и проверка работает ли модуль с данной картой
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
 
  // Вывод типа карты
  Serial.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }
 
  // Теперь мы попробуем открыть  'volume'/'partition' (том/раздел) - файловая система должна быть FAT16 или FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }
 
 
  // вывод типа и размера первого FAT-тома
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();
 
  volumesize = volume.blocksPerCluster();    // кластеры и коллекции блоков
  volumesize *= volume.clusterCount();       // получим много кластеров
  volumesize *= 512;                            // на SD карте блоки всегда по 512 байт
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
 
 
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);
 
  // Вывод всех файлов с карты с датой и размером
  root.ls(LS_R | LS_DATE | LS_SIZE);
}
 
 
void loop(void) {
 
}
