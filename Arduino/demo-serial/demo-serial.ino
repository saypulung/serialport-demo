#define MAX_PETS 5
#define MAX_CITIES 10
typedef struct {
  uint16_t number1;   // 4 bytes
  char randomPet[50]; // 50 bytes
  float randomTemp;   // 4 bytes
  char randomCity[50];// 50 bytes
  char reserved[20];  // 20 bytes
  // -----------------  128 bytes
} RandomData;

void setup() {
  Serial.begin(57600);
}

void loop() {
  
  String cities[10] = {
    "Jakarta",
    "Bandung",
    "Yogyakarta",
    "Bekasi",
    "Surabaya",
    "Denpasar",
    "Mataram",
    "Palembang",
    "Bandar Lampung",
    "Gunung Sugih"
  };

  String pets[5] = {
    "Kucing",
    "Kelinci",
    "Anjing",
    "Otter",
    "Harimau"
  };

  long randomPetIndex, randomCityIndex, randomNumber;
  float randomTemp;
  //if (Serial.available()) {
    randomPetIndex = random(0, MAX_PETS-1);
    randomCityIndex = random(0, MAX_CITIES-1);
    randomNumber = (uint16_t) random(0, 5000);
    randomTemp = (float) random(0,100);
    randomTemp += (float) random(0,100) / 100.00;

    RandomData rando;
    String city = cities[randomCityIndex];
    city.toCharArray(rando.randomCity, 50);
    String pet = pets[randomPetIndex];
    pet.toCharArray(rando.randomPet, 50);
    rando.randomTemp = randomTemp;
    rando.number1 = randomNumber;
    byte *randos = (byte*) &rando;
    Serial.write(0x0d);
    Serial.write(randos, sizeof(RandomData));
    Serial.write(0x20);
  //}

}
