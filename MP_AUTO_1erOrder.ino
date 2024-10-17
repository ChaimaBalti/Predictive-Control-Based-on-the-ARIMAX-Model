
int N = 600;
double Yc[600];
double Y[600];
double u[600];

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

double du = 1.0;

  for (int k = 2; k < N - 2; k++) 
  {
    Y[k] = 0.905 * Y[k - 1] + 0.1 * u[k - 1];

    double Y0[3];
      Y0[0] = 1.905* Y[k] - 0.905 * Y[k - 1] ;
      Y0[1] = 2.724* Y[k] - 1.724 * Y[k - 1] ;
      Y0[2] = 3.4652* Y[k] + -2.4652* Y[k - 1] ;

    double V = 0.0;
    V =0.1 * (Yc[k + 0] - Y0[0]) + 0.1905 * (Yc[k + 1] - Y0[1]) + 0.2724 * (Yc[k + 2] - Y0[2]);

    du = 0.47312*V;
    u[k] = du + u[k - 1];
  }

  for (int j = 0; j < 600; j=j+1) {
    Serial.print(Yc[j]);
    Serial.print("\t");
    Serial.println(Y[j]);
    Serial.print("\t");
    Serial.print(u[j]);
    Serial.print("\t");
  }
  
}