//
//  Utilities.hpp
//  openCVtest
//
//  Created by Liyu Zerihun on 7/29/22.
//
#include <vector>
#include <iostream>
#include <random>

#ifndef Utilities_hpp
#define Utilities_hpp
extern double learningRate;



static double uniformRand(int x, int y, int division){
//    std::random_device rd;
//
//        std::mt19937 e2(rd());
//
//    std::normal_distribution<> dist(0, 0.4);
//    return (double)dist(rd);
    
    std::random_device rd; // obtain a random number from hardware
      std::mt19937 gen(rd()); // seed the generator
      std::uniform_int_distribution<> distr( -0.3*1000, 0.3*1000); // define the range
    return (double)distr(gen)/1000;

}

static double uniformTest(int x, int y, int division){
    std::random_device rd; // obtain a random number from hardware
      std::mt19937 gen(rd()); // seed the generator
      std::uniform_int_distribution<> distr( x*division, y*division); // define the range
    
    return (double)distr(gen)/division;
    
}



const int imageWidth=500;
const int imageHeight=500;
using namespace std;
struct RGB{
    
    double r;
    double b;
    double g;
    RGB(double red, double blue, double green){
        r=red;
        b=blue;
        g=green;
    }
    void red(double red){//Methods for RGB value modification
        r=red;
    }
    void green(double green){
        g=green;
    }
    void blue(double blue){
        b=blue;
    }
    
};


static void seLu(vector<double>* input, vector<double>* output){
    for(int i=0; i<input->size(); i++){
    double value=input->at(i);// the final element of tthe input matrix
    if(value<0){
        output->push_back((double)0.001*value);
    }
    else{
    output->push_back(value);
        }
    }
    
}
static void reLu( vector<double>* input, vector<double>* output){
    for(int i=0; i<input->size(); i++){
    double value=input->at(i);// the final element of tthe input matrix
    if(value<=0){
        output->push_back(0.001*value);
    }
    else{
    output->push_back(value);

        }
    }
  //  output->push_back(1/(1+pow(exp(1),-1*input->at(0))));

    
}

static void derReLu( double& derivative, double output, double specificOutput, double numberOf, vector<double>& list){
    
    if(output<0){
        derivative=0.001;
    }
    else if(output==0){
        derivative=0;
    }
    else{
        derivative=1;
    }
    
   // derivative=(1/(1+pow(exp(1),-1*output)))*(1-(1/(1+pow(exp(1),-1*output))));

    
}

static void derMultiply( double& derivative, double output, double specificOutput, double numberOf, vector<double>& list){
    double number=1;
    if(output==0||specificOutput==0){
        for(int i=0; i<list.size(); i++){
            
            double num= list.at(i);
            if(num!=specificOutput){
                number=number*num;
            }
        }
        
        derivative=number;
    }
    else{
    derivative=(double)output/specificOutput;
    }

    
}


static void derAddition( double& derivative, double output, double specificOutput, double numberOf, vector<double>& list){
    
    derivative=1;

    
}

static void multiply( vector<double>* input, vector<double>* output){
    double product=1;
    for(int i=0; i<input->size(); i=i+1){
        product=product*input->at(i);
    }
    output->push_back(product);
    
}

static void subtraction( vector<double>* input, vector<double>* output){
    double difference=0;
    for(int i=0; i<input->size(); i=i+1){
        difference=difference-input->at(i);
    }
    output->push_back(difference);
    
}

static void derSubtraction( double& derivative, double output, double specificOutput, double numberOf, vector<double>& list){
    for(int i=0; i<list.size(); i=i+1){
        if(list.at(i)==specificOutput){
            if(i%2==0){
                derivative=1;
            }
            else{
                derivative=-1;
            }
        }
    }
    
}



static void add( vector<double>* list, vector<double>* output){// Collective node function
    double sum=0;

    for(int i=0; i<list->size(); i=i+1){
        sum= list->at(i)+sum;
    }
    
//    cout<<endl;
//    cout<<sum<<endl;
    output->push_back(sum);
}


static void average( vector<double>* list, vector<double>* output){// Collective node function
    double sum=0;

    for(int i=0; i<list->size(); i=i+1){
        sum= list->at(i)+sum;
    }
    
    sum=sum/list->size();
    output->push_back(sum);
}

static void derAverage( double& derivative, double output, double specificOutput, double numberOf, vector<double>& list){// Collective node function
    derivative=double(1/numberOf);


}


 
typedef void (*collectFunc)( vector<double>*, vector<double>*);// Collective node, with a vector being accepted as a paramter and a void return statement
typedef void (*collectFuncDerivative)( double& derivative, double output, double specificOutput, double number, vector<double>& list);// Collective node, with a vector being accepted as a paramter and a void return statement

static collectFunc collectiveFunc[5]= {&add, &reLu, &multiply, &average, &subtraction};
static collectFuncDerivative derivativeFunc[5]={&derAddition, &derReLu, &derMultiply, &derAverage, &derSubtraction};



static void calculateMeandVariance(vector<double> vals, double& mean, double& variance){
    for(int i=0; i<vals.size(); i++){
        mean= vals.at(i)+mean;
    }
    mean=mean/vals.size();
        
    for(int i=0; i<vals.size(); i++){
        variance= pow(vals.at(i)-mean,2)+variance;
    }
    
    variance=variance/vals.size();
    
    
    
    
}

#endif /* Utilities_hpp */
