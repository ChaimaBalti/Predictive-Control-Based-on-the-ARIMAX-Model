const int Ny = 3; // Longueur de Y
const int Nu = 1; // Longueur de U

const int N = 600;
float Yc[600];
float Y[600];
float F[3][3] = {
  {2.511, -2.06, 0.549},
  {4.2451, -4.6237, 1.3785},
  {6.0358, -7.3664, 2.3306}
};
float H[] = {0.106, 0.26617, 0.44998};
float G[] = {0, 0.106, 0.26617};
float u[600];

float L[2][2] = {
  {0.48104, -0.018964},
  {-0.018964, 0.48104}
};
void setup() 
{
  Serial.begin(9600);

  for (int i = 0; i < N; i=i+1) 
  {
    Yc[i] = 1.0;
    if (i > 100 && i <= 200)
    {
      Yc[i] = 2.0;
    }
    if (i > 300 && i <= 400) 
    {
      Yc[i] = 2.0;
    }
    if (i > 500 && i <= 600) 
    {
      Yc[i] = 2.0;
    }
  }

  for (int i = 0; i < N; i=i+1) 
  {
    u[i] = 0.0;
  }


}

void loop() {
  float du = 1.0;

  for (int k = 2; k < N - 2; k++) {
    Y[k] = 1.511 * Y[k - 1] - 0.549 * Y[k - 2] + 0.106 * u[k - 2];

    float Y0[Ny];
    for (int i = 0; i < Ny; i++) {
      Y0[i] = F[i][0] * Y[k] + F[i][1] * Y[k - 1] + F[i][2] * Y[k - 2] + H[i] * du;
    }

    float V;
      V= 0;
      for (int j = 0; j < 3; j++) {
        V+=(G[j] * (Yc[k + 1 + j] - Y0[j]));
      }
    du = 0.48104*V;
    u[k] = du + u[k - 1];
  
    Serial.print(Yc[k]);
    Serial.print("\t");
    Serial.println(Y[k]);
    Serial.print("\t");
    Serial.print(u[k]);
    Serial.print("\t");
    delay (50) ;
  }
  
}