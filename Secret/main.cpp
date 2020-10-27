#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstdio>


void hiddenFunction(int i)
{
    const std::string encrypt = "#<=;7<=*\a+,=>967ii'\ayy\a%";
    for(int i = 0 ; i < 1000; i++)
    {
        for(int counter = 0 ; counter < encrypt.size() ; counter++)
        {
            char temp = encrypt[counter] ^ i;
            printf("%x", temp);
        }
        printf("\n");
    }
}

bool fnc_4009aa()
{
    const char filename[] = "/tmp/secret";
    const char mode[] = "rb";
    char word[];
    auto *file = fopen(filename, mode);
    if(!file)
    {
        exit(1);
    }

    memset('d',


    return 0;
}

int main(int argc, char **argv)
{
    int random_number ;
    int number;
    srand(time(0));
    random_number = rand() % 126;

    if(argc == 1)
    {
        int tmp = atoi(argv[1]);
        if(tmp == 0 || tmp != 127)
            number = random_number;
    }
    else
       number = random_number;

    if(fnc_4009aa())
    {

    }





    return 0;
}
