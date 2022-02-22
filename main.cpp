#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>

using namespace std;


///////////////////////////*********************///////////////////////////////
class Spell
{
private:
    int power;
    string name;

public :
    int getPower()
    {
        return power;
    }
    void setPower(int power1)
    {
        power=power1;
    }
    string getName()
    {
        return name;
    }
    void setName(string name1)
    {
        name=name1;
    }
};


//////////////////////////**********************////////////////////////////////////////
class Fighter

{
private :
    int health=100;
    int energy =500;
    int shield =3;


public :
    Spell spell[7];

    int getEnergy()
    {
        return energy;
    }
    void setEnergy(int energy1)
    {
        energy=energy-energy1;
    }
    int getHealth()
    {
        return health;
    }
    void setHealth(int health1)
    {
        health=health-health1;
    }
    int getShield()
    {
        return shield;
    }
    void setShield()
    {
        --shield;
    }
};





/////////////////////////***************/////////////////////////////////////////////
void ReadFile(Fighter *harry,Fighter *vold)
{
    string myText[3];
    ifstream MyReadFile("spell.txt");
    for(int i=0,n1=0,n2=0; !MyReadFile.eof(); i++) // n1,n2 number of spells
    {
        MyReadFile>>myText[0];
        MyReadFile>>myText[1];    //convert the line to 3 strings
        MyReadFile>>myText[2];


        stringstream ss;  //convert the string to int
        int pow;
        ss<<myText[2];
        ss>>pow;

        if(myText[0]=="A")
        {
            harry->spell[n1].setName(myText[1]);  //giving the spell to harry and vild
            harry->spell[n1].setPower(pow);
            vold->spell[n2].setName(myText[1]);
            vold->spell[n2].setPower(pow);
            n1++;
            n2++;

        }
        else if(myText[0]=="H")
        {

            harry->spell[n1].setPower(pow);
            harry->spell[n1].setName(myText[1]);
            n1++;

        }
        else if(myText[0]=="V")
        {

            vold->spell[n2].setPower(pow);
            vold->spell[n2].setName(myText[1]);
            n2++;
        }




    }


    MyReadFile.close();
}


////////////////////////******************************////////////////////////
void fight(Fighter *harry,string spellHarry,Fighter *vold,string spellVold)
{
    int power1,power2,check=0,i=0;


    for( i=0; i<7; i++)
    {
        if(spellHarry==harry->spell[i].getName())
        {
            power1 =harry->spell[i].getPower();

            break;
        }
    }
    if(i==7)
    {
        cout<<"\n harry does not have this spell\n";
        check=1;
    }


    for( i=0; i<7; i++)
    {
        if(spellVold==vold->spell[i].getName())
        {
            power2 =vold->spell[i].getPower();

            break;
        }
    }
    if(i==7)
    {
        cout<<"\nvoldmort does not have this spell\n";
        check=1;
    }


    if(check==0) // if it checks that harry has the first spell and vold has the second spell
    {
        int dif=power1-power2;
        if(dif>0)  // if div is + then harry'spell is stronger than vold'spell
        {
            if(power2==0&&vold->getShield()!=0)
                vold->setShield();
            else if(vold->getShield()==0&&power2==0)
            {
                cout<<"\nvoldmort can't use sheild\n";
                return ;
            }
            else
                vold->setHealth(dif);

        }
        else if(dif<0)
        {
            if(power1==0&&harry->getShield()!=0)
                harry->setShield();
            else if(harry->getShield()==0&&power1==0)
            {
                cout<<"\nharry can't use sheild\n";
                return ;
            }
            else
                harry->setHealth((dif*(-1)));
        }


        harry->setEnergy(power1); // new power =old power - power1
        vold->setEnergy(power2);

        if(harry->getEnergy()<=0&&vold->getEnergy()<=0)
        {
            cout<<"\nharry and voldmort lose their energy \n ";
            exit(1);
        }
        else if(vold->getEnergy()<=0)
        {
            cout<<"\nvoldmort can't use spell again and he will lose the fight \n";

            exit(1);
        }
        else if(harry->getEnergy()<=0)
        {
            cout<<"\nharry can't use spell again and he will lose the fight\n";
            exit(1);
        }

        if(harry->getHealth()>0&&vold->getHealth()>0)
        {
            cout<<"\t harry\t voldmort\n"<<"health   "<<harry->getHealth()<<"\t "<<vold->getHealth();
            cout<<"\nenergy   "<<harry->getEnergy()<<"\t "<<vold->getEnergy();
            cout<<"\nshield   "<<harry->getShield()<<"\t "<<vold->getShield();
        }
    }
}


////////////////////******************///////////////////////////////
int main()
{
    Fighter harry,vold;
    ReadFile(&harry,&vold);
    char line[50],*sp1,*sp2;
    while(harry.getHealth()>0&&vold.getHealth()>0)
    {
        cout<<"\nenter the two spells(harry then voldmort)\n";
        gets(line);
        sp1=strtok(line," ");// convert the intput to two strings
        sp2=strtok(NULL,"");
        stringstream ss1,ss2;
        string spellHarry,spellVold;  //convert the char array to string
        ss1<<sp1;
        ss1>>spellHarry;
        ss2<<sp2;
        ss2>>spellVold;
        fight(&harry,spellHarry,&vold,spellVold);

    }
    if(harry.getHealth()<=0)
        cout<<"\nvoldmort is winner";
    else if(vold.getHealth()<=0)
        cout <<"\nharry is winner";



    return 0;
}
