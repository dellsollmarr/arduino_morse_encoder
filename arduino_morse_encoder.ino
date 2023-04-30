#define BASE_DELAY 2000
//morse code from A to Z
String const morseCode[] = 
{
  ".-", "-...", "-.-.", "-..", ".", "..-.",
  "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
  ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

int StringCount = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial) { }; // wait for initialization.
  setPinModes();

  Serial.println("Enter data:");
  testSignal(true);
  while (Serial.available() == 0) {}  //wait for data available
  testSignal(false);
  String words[20];
  String morseCodeValue;
  String text = Serial.readString();  //read until timeout
  text.trim();                        // remove any \r \n whitespace at the end of the String
  for (int i = 0; i < text.length(); i++)
  {
    if (text[i] != ' ')
      {   
        text[i]=toupper(text[i]);
        morseCodeValue+=morseCode[text[i]-'A']+" ";
      }
      if (text[i] ==' ')
      {
        morseCodeValue+="/ ";      
      }
  }
  while(morseCodeValue.length() > 0)
  {
    int index = morseCodeValue.indexOf(' ');
    if (index == -1) // No space found
    {
      words[StringCount++] = morseCodeValue;
      break;
    }
    else 
    {
      words[StringCount++] = morseCodeValue.substring(0, index);
      morseCodeValue = morseCodeValue.substring(index+1);
    }
  }

  for (int i = 0; i < StringCount; i++)
  {
    String word = words[i];
    Serial.print(' ');
    for (int j = 0; j < word.length(); j++)
    {    
      if (word[j] == '-')
      {
        Serial.print('-');
        digitalWrite(8+j, true);
        delay(BASE_DELAY);
        digitalWrite(8+j,false);
        delay(BASE_DELAY);
        digitalWrite(8+j,true);
        delay(BASE_DELAY);
        digitalWrite(8+j,false);
      }
      else if (word[j] == '.')
      {
        Serial.print('.');
        digitalWrite(8+j, true);
        delay(3 * BASE_DELAY);
        digitalWrite(8+j,false);

      }
      else 
      {
        Serial.print('/');
        digitalWrite(7, true);
        delay(BASE_DELAY);
        digitalWrite(7,false);
      } 
    }
  } 
}

void loop()
{

}

// sends signal on all used pins
void testSignal(bool light)
{
  digitalWrite(7, light);
  digitalWrite(8, light);
  digitalWrite(9, light);
  digitalWrite(10, light);
  digitalWrite(11, light);
  digitalWrite(12, light);
}

void setPinModes()
{
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}
