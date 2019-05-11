#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<vector>

using namespace std;
#include <Eigen/Dense>
using namespace Eigen;

/*
* Kalman Filter Class Definition.
* 
* by Fabio Carbone, 23/12/2016
*   www.fabiocarbone.org
* 
* Matrix Dimension must be:
*
* A: n x n
* B: n x m
* H: n x n
* Q: n x n
* R: n x n
* I: n x n
* X: n x 1
* U: m x 1
* Z: n x 1
* P: n x n
* K: n x n
*
*/

class KalmanFilter {

  public:

    /* Problem Dimension */
    int n; //State vector dimension
    int m; //Control vector (input) dimension (if there is not input, set to zero)

    /* Fixed Matrix */
    MatrixXf A; //System dynamics matrix
    MatrixXf B; //Control matrix 
    MatrixXf H; //Mesaurement Adaptation matrix
    MatrixXf Q; //Process Noise Covariance matrix
    MatrixXf R; //Measurement Noise Covariance matrix
    MatrixXf I; //Identity matrix

    /* Variable Matrix */
    VectorXf X; //(Current) State vector
    MatrixXf P; //State Covariance
    MatrixXf K; //Kalman Gain matrix

    /* Inizial Value */
    VectorXf X0; //Initial State vector
    MatrixXf P0; //Initial State Covariance matrix
    
    /* 
    * Constructor 
    * _n: state vector dimension
    * _m: control vector dimension (if there is not input, set to zero)
    */
    KalmanFilter(int _n,  int _m);

    /* Set Fixed Matrix (NO INPUT) */
    void setFixed ( MatrixXf _A, MatrixXf _H, MatrixXf _Q, MatrixXf _R );

    /* Set Fixed Matrix (WITH INPUT) */
    void setFixed ( MatrixXf _A, MatrixXf _B, MatrixXf _H, MatrixXf _Q, MatrixXf _R );

    /* Set Initial Value */
    void setInitial( VectorXf _X0, MatrixXf _P0 );
    
    /* Do prediction (NO INPUT) */
    void predict ( void );

    /* Do prediction (INPUT) */
    void predict ( VectorXf U );

    /* Do correction */
    void correct ( VectorXf Z );

};
KalmanFilter::KalmanFilter(int _n,  int _m) {
  n = _n;
  m = _m;
}

/* Set Fixed Matrix */
void KalmanFilter::setFixed( MatrixXf _A, MatrixXf _H, MatrixXf _Q, MatrixXf _R ){
  A = _A;
  H = _H;
  Q = _Q;
  R = _R;
  I = I.Identity(n, n);
}

/* Set Fixed Matrix */
void KalmanFilter::setFixed( MatrixXf _A, MatrixXf _H, MatrixXf _Q, MatrixXf _R, MatrixXf _B ){
  A = _A;
  B = _B;
  H = _H;
  Q = _Q;
  R = _R;
  I = I.Identity(n, n);
}

/* Set Initial Matrix */
void KalmanFilter::setInitial( VectorXf _X0, MatrixXf _P0 ){
  X0 = _X0;
  P0 = _P0;
}

/* Do prediction based of physical system (No external input)
*/   
void KalmanFilter::predict(void){
  X = (A * X0);
  P = (A * P0 * A.transpose()) + Q;
}

/* Do prediction based of physical system (with external input)
* U: Control vector
*/   
void KalmanFilter::predict( VectorXf U ){
  X = (A * X0) + (B * U);
  P = (A * P0 * A.transpose()) + Q;
}

/* Correct the prediction, using mesaurement 
*  Z: mesaure vector
*/
void KalmanFilter::correct ( VectorXf Z ) {
  K = ( P * H.transpose() ) * ( H * P * H.transpose() + R).inverse();

  X = X + K*(Z - H * X);
  
  P = (I - K * H) * P;

  X0 = X;
  P0 = P;
}

static int i; //maintaining data set number

vector<float> x[22];
vector<float> y[22];
vector<float> z[22];
vector<float> latitude[22];
vector<float> longitude[22];
vector<float> speed[22];
vector<float> sound[22];
vector<float> timestamp[22];
  vector<float> v;

void record_data()
{
  int j=0;
  string c;
  float k;
  string line,word,temp;

  while(i<10)
  {
    fstream fin;
    string ext="/home/abhijit/csv_docu/overtake_";
    c=to_string(i);
    string name=".csv";
    name.insert(0,c);
    ext.append(name);
    cout<<ext<<endl;
    int first_flag=1;
    fin.open(ext,ios::in);
    cout<<"d"<<endl;

    while(fin>>temp)
    {
      cout<<"e"<<endl;
      if(first_flag==1)
      {
        cout<<"f"<<endl;
        first_flag=0;
        continue;
      }


      fin>>line;
      stringstream s(line);
      cout<<line<<endl;

       while (getline(s, word, ',')) 
      {
        cout<<"g"<<endl;
        switch(j)
        {

          case 0:
             // k=stof(word);
              x[i].push_back(stof(word));
              break;
              case 1:
              y[i].push_back(stof(word));
              break;
              case 2:
              z[i].push_back(stof(word));
              break;
              case 3:
              latitude[i].push_back(stof(word));
              break;
              case 4:
              longitude[i].push_back(stof(word));
              break;
              case 5:
              speed[i].push_back(stof(word));
              break;
              case 6:
              sound[i].push_back(stof(word));
              break;
              case 7:
              timestamp[i].push_back(stof(word));
              break;
        }
        cout<<"a"<<endl;
        j++;

      }
      cout<<"b"<<endl;
      j=0;
    }
    cout<<"c"<<endl;
    
    first_flag=1;
    i++;

}
cout<<"abab"<<endl;
int l;
for(int i=0;i<10;i++)
    {
      cout<<z[i].size()<<endl;
      l=z[i].size();
      for(j=0;j<l;j++)
      {
        v.push_back(z[i][j]);
      }
    }
    cout<<v.size()<<endl;
}

int main()
{
  //vector<float> v1;
  record_data();
  
  MatrixXf A(1, 1); A << 1;
  MatrixXf H(1, 1); H << 1;
  MatrixXf Q(1, 1); Q << 0;
  MatrixXf R(1, 1); R << 0.1;
  VectorXf X0(1); X0 << 0;
  MatrixXf P0(1, 1); P0 << 1;
  KalmanFilter filter1(1, 0);
  vector<float> val[22];
//float mesaure[10] = {0.39, 0.50, 0.48, 0.29, 0.25, 0.32, 0.34, 0.48, 0.41, 0.45};
  
  /* Initialize the Filter*/
  
  filter1.setFixed(A, H, Q, R);
  filter1.setInitial(X0, P0);

  /* Create measure vector, and store measure value */
  
  VectorXf Z(1);
  i=1;
  //val=record_data();
  for (int i = 0; i<v.size(); i++)
  {
    
    filter1.predict(); //Predict phase
    Z<<v[i];
    filter1.correct( Z ); //Correction phase
  
    cout << "X" << i << ": " << filter1.X << endl;

  }
  
  return 0;

}



