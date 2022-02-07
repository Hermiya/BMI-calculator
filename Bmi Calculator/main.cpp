#include <iostream>

//using string cmp, string variables
#include<string.h>

//read and  write file
#include<fstream>

using namespace std;


class BMI
{
private:
    string username;
    float weight;
    float height;
    float TotalBmi;
public:
    void CalculateBmi(string, float,float );
    void displayAll();
    void displayByName(string);
    int search(string);

    void deleteRecordByName(string);
    void update(string, float, float);

    void clearScreen();
    float KgToPounds(float);
    float CmToInches(float);
    float CalculateBmi(float, float);
    string Msg(float);
};
BMI bmi;


void BMI::clearScreen()
{
    system("clear");
}

void BMI::CalculateBmi(string name, float weight, float height)
{
    ofstream File("Records.txt", ios::app);
    //convert weight to pounds
    bmi.weight = bmi.KgToPounds(weight);
    //convert height to inches
    bmi.height = bmi.CmToInches(height);

    bmi.TotalBmi = BMI::CalculateBmi(bmi.weight, bmi.height);

    cout<<"\n\t"<<name<<"Your BMI is : "<<bmi.TotalBmi<<endl;
    cout<<"\n\t"<<name<<"your are "<<BMI::Msg(bmi.TotalBmi)<<endl;
    File << name <<" "<< weight <<" "<< height <<endl;
    File.close();
}

float BMI::KgToPounds(float kg)
{
    return kg * 2.20462;
}

float BMI::CmToInches(float cm)
{
    return cm * 0.393701;
}

string BMI::Msg(float bmi)
{
    if(bmi > 25)
        return "Overweight";
    else if(bmi<25 && bmi>18.5)
        return "Optimal";
    else
        return "Underweight";
}

void BMI::displayAll()
{
//display name, id, sex and age
    ifstream File("Records.txt");
    cout<<"\n\tAll Records"<<endl;
    cout<<"\n\t---------------------------------------"<<endl;
    int n=0;
    cout <<"\n\tNo Name w   h   TotalBmi     "<<endl;
    while(File >> bmi.username >> bmi.weight >> bmi.height)
    {

        cout <<"\n\t"<<++n<<". "<< bmi.username<<" | "<<bmi.weight<<" | "<< bmi.height<<" | "<<BMI::CalculateBmi(BMI::KgToPounds(bmi.weight),BMI::CmToInches(bmi.height))<<endl;

    }
    cout<<"\n\t---------------------------------------"<<endl;
}

void BMI::displayByName(string name)
{
//display name, id, sex and age
    ifstream File("Records.txt");
    cout<<"\n\tAll Records"<<endl;
    cout<<"\n\t---------------------------------------"<<endl;
    int n=0;
    cout <<"\n\tNo Name w   h   TotalBmi     "<<endl;
    while(File >> bmi.username >> bmi.weight >> bmi.height)
    {
        if(bmi.username == name)
            cout <<"\n\t"<<++n<<". "<< bmi.username<<" | "<<bmi.weight<<" | "<< bmi.height<<" | "<<BMI::CalculateBmi(BMI::KgToPounds(bmi.weight),BMI::CmToInches(bmi.height))<<endl;

    }
    cout<<"\n\t---------------------------------------"<<endl;
}


float BMI::CalculateBmi(float w, float h)
{
    return (w * 703)/(h * h );
}

int BMI::search(string name)
{
    ifstream File("Records.txt");
    while(File >> bmi.username >> bmi.weight >> bmi.height)
    {
        if(bmi.username == name)
        {
            return 1;
            break;
        }

    }
    return 0;
}

void BMI::deleteRecordByName(string key)
{
    ifstream File("Records.txt");
    ofstream Temp("temp.txt");
    while(File >> bmi.username >> bmi.weight >> bmi.height )
    {
        if(bmi.username == key);
        else
        {
            Temp << bmi.username <<" "<< bmi.weight<<" "<< bmi.height<<endl;
        }

    }
    File.close();
    Temp.close();
    remove("Records.txt");
    rename("temp.txt","Records.txt");
    bmi.clearScreen();
    cout<<"\n\t---------------------------------------"<<endl;
    cout<<"\n\t Record successfully deleted!"<<endl;
    cout<<"\n\t---------------------------------------"<<endl;

}



void BMI::update(string key, float weight, float height)
{
    ifstream File("Records.txt");
    ofstream Temp("temp.txt");
    while(File >> bmi.username >> bmi.weight >> bmi.height)
    {
        if(bmi.username == key)
        {
            bmi.weight = weight;
            bmi.height = height;
        }
        Temp << bmi.username <<" "<< bmi.weight <<" "<<bmi.height<<endl;
    }
    File.close();
    Temp.close();
    remove("Records.txt");
    rename("temp.txt","Records.txt");
    bmi.clearScreen();
    cout<<"\n\t---------------------------------------"<<endl;
    cout<<"\n\t Record successfully updated!"<<endl;
    cout<<"\n\t---------------------------------------"<<endl;

}




int main()
{
    int choice,n,numRec,reopenCounter;
    float w,h;
    string name;
    char key;
    int _key_;
    n=0;

    //console background color f-white and text color 0-black
    system("color f0");

    bmi.clearScreen();
    do
    {
        cout<<"\n\t BMI CALCULATOR ";
        cout<<"\n\t---------------------------------------"<<endl;
        cout<<"\n\t\t1-Calculate your BMI "<<endl;
        cout<<"\n\t\t2-Display ALl"<<endl;
        cout<<"\n\t\t3-Update BMI Record"<<endl;
        cout<<"\n\t\t4-Delete BMI Record"<<endl;
        cout<<"\n\t\t5-Search by Name"<<endl;
        cout<<"\n\t\t0-EXIT"<<endl;
        cout<<"\n\t---------------------------------------";
        cout<<"\n\t\tEnter Your choice:";
        cin>>choice;
        if(choice==1)
        {
            bmi.clearScreen();
            cout<<"\n\tPlease Enter your name: ";
            cin>>name;
            cout<<"\n\tPlease Enter your weight in kg : ";
            cin>>w;
            cout<<"\n\tPlease Enter your Height in cm : ";
            cin>>h;
            bmi.CalculateBmi(name,w,h);

        }
        else if(choice == 2)
        {
            bmi.clearScreen();
            bmi.displayAll();
        }
        else if(choice == 3)
        {
            bmi.clearScreen();
            cout<<"\n\t\tEnter first username to update record: ";
            cin>>name;
            if(bmi.search(name) == 1)
            {
                bmi.clearScreen();
                cout<<"\n\tPlease Enter your weight in kg : ";
                cin>>w;
                cout<<"\n\tPlease Enter your Height in cm : ";
                cin>>h;
                bmi.update(name,w,h);
            }
            else
            {
                bmi.clearScreen();
                cout<<"\n\tThe username not available"<<endl;
            }


        }
        else if(choice == 4)
        {
            bmi.clearScreen();
            cout<<"\n\t\tEnter first username to delete from record: ";
            cin>>name;
            if(bmi.search(name) == 1)
            {
                bmi.clearScreen();
                bmi.deleteRecordByName(name);
            }
            else
            {
                bmi.clearScreen();
                cout<<"\n\tThe username not available"<<endl;
            }

        }
        else if(choice == 5)
        {
            bmi.clearScreen();
            cout<<"\n\tPlease enter name: ";
            cin>>name;
            if(bmi.search(name) == 1)
            {
                bmi.clearScreen();
                bmi.displayByName(name);
            }
            else
            {
                bmi.clearScreen();
                cout<<"\n\tThe username not available"<<endl;
            }

        }
        else if(choice==0);
        else
        {
            bmi.clearScreen();

            cout<<"\n\t\tInvalid choice! Try again!"<<endl;
        }

    }
    while(choice!=0);
}
