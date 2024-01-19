int freq = 5000;    // frequency
int channel = 0;    // thoroughfare
int resolution = 8;   // resolution ratio
const int led = 18;
const int gm = 35; //Photosensitive resistor pins
int Filter_Value;
void setup()
{
  Serial.begin(115200); 
    
  //Set photoresistor input
  pinMode(gm,INPUT); 
  randomSeed(analogRead(gm));
  
  ledcSetup(channel, freq, resolution); // Set up channels
  ledcAttachPin(led, channel);  // Connect the channel to the corresponding pin
  
}
#define FILTER_N 20
int Filter() {
  int i;
  int filter_sum = 0;
  int filter_max, filter_min;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = analogRead(gm);
    delay(1);
  }
  filter_max = filter_buf[0];
  filter_min = filter_buf[0];
  filter_sum = filter_buf[0];
  for(i = FILTER_N - 1; i > 0; i--) {
    if(filter_buf[i] > filter_max)
      filter_max=filter_buf[i];
    else if(filter_buf[i] < filter_min)
      filter_min=filter_buf[i];
    filter_sum = filter_sum + filter_buf[i];
    filter_buf[i] = filter_buf[i - 1];
  }
  i = FILTER_N - 2;
  filter_sum = filter_sum - filter_max - filter_min + i / 2; // +The purpose of i/2 is to round
  filter_sum = filter_sum / i;
  return filter_sum;
}
void loop()
{
  Filter_Value = Filter();
  ledcWrite(0,map(Filter_Value,0,4095,0,255));
}
