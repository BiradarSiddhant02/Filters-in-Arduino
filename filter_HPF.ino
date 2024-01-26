const int resolution = 512;  // Number of steps in one period
const int delayTime = 2;    // Delay between steps in milliseconds
int sample = 0;

double b[] = {9.49082422e-01, -3.79632969e+00, 5.69449453e+00, -3.79632969e+00, 9.49082422e-01};
double a[] = {1.0, -3.8954922741642717, 5.691903145992599, -3.697165885589683, 0.9007574434123555};

double y[] = {0, 0, 0, 0, 0};
double x[] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
}

float sine_base(int sample){
  return sin(2 * PI * sample / resolution);  
}

float sine_noise(int sample){
  return sin(2 * PI * 50 * sample / resolution);  
}

void loop() {
    // Input signal (sum of base sine wave and noise)
    x[0] = sine_base(sample) + sine_noise(sample);

    // High-Pass Filter logic
    y[0] = b[0] * x[0] + b[1] * x[1] + b[2] * x[2] + b[3] * x[3] + b[4] * x[4]
          - a[1] * y[1] - a[2] * y[2] - a[3] * y[3] - a[4] * y[4];

    // Shift values for the next iteration
    for (int i = 4; i > 0; --i) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    // Output signal after High-Pass Filter
    Serial.print(y[0]);
    Serial.print(" ");
    Serial.println(x[0]);

    // Increment sample for the next iteration
    sample += 1;

    // Introduce a delay
    delay(delayTime);
}
