#include "List.h"

#include<cmath>
#include<cstdlib>
#include<cstring>

#define ACTION_NA       0
#define ACTION_APPEND   1
#define ACTION_DELETE   2
#define ACTION_PRINT    3
#define ACTION_DONE     4

#ifdef _UNIT_TESTS
    #define CATCH_CONFIG_MAIN
    #include "catch.hpp"
#endif

int parseInt(char * Str, int length)
{
	bool isIntConst = false;
	char * subStr;
	int   value,i;

    //Define the integer state transition matrix
    const int INT_STM[4][3] = {
        {0,0,0},
        {0,2,3},
        {0,0,3},
        {0,0,3}
    };

    int state = 1;
    int input = 0;

    //Loop through input string Str from 0 .. len-1
    for (i = 0; i < length; i += 1)
    {  
        switch(Str[i])
        {
            case '+': case '-': 
            input = 1; break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            input = 2; break;
            default:
            input = 0; break;
        }
        //update state based on state and input
        state = INT_STM[state][input];
    }

    //decide if input string is an integer or not
    isIntConst = (state == 3)?true:false;

	if(isIntConst == true)
    {

		subStr = new  char[length+1];

		for(i=0;i<length;i++) 
            subStr[i]=Str[i];

		subStr[length]='\0';
		value  = atoi(subStr);
		delete (subStr);

		return value;
	}

	return -1;
}

double parseReal(char * Str, int length)
{
	bool isRealConst = false;
	char * subStr;
	double value; int i;

    //define the real state transition matrix
    const int REAL_STM[10][5] = {
        {0,0,0,0,0},
        {0,2,4,3,0},
        {0,0,4,3,0},
        {0,0,6,0,0},
        {0,0,4,5,7},
        {0,0,6,0,7},
        {0,0,6,0,7},
        {0,8,9,0,0},
        {0,0,9,0,0},
        {0,0,9,0,0}
    };

    int state = 1;
    int input = 0;

    for (i = 0; i < length; i += 1)
    {
        switch(Str[i])
        {
            case '+': case '-': 
            input = 1; break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            input = 2; break;
            case '.':
            input = 3; break;
            case 'e': case 'E':
            input = 4; break;
            default:
            input = 0; break;
        }
        //update state based on state and input
        state = REAL_STM[state][input];
    }

    //decide if input string is real or not
    isRealConst = ( state == 4 || state == 5 || \
                    state == 6 || state == 9)?true:false;

	if(isRealConst == true)
    {
		subStr = new  char[length+1];
		for(i=0;i<length;i++) 
            subStr[i]=Str[i];

		subStr[length]='\0';
		value  = atof(subStr);
		delete (subStr);

		return value;
	}

	return nan("");
}

//checks and returns action for each character
int isAction(char c)
{
    int action = ACTION_NA;

    //map characters to respective actions
    switch(c)
    {
        case 'p': case 'P': action = ACTION_PRINT; break;
        case 'a': case 'A': action = ACTION_APPEND; break;
        case 'd': case 'D': action = ACTION_DELETE; break;
        case '\0': action = ACTION_DONE; break;
        default: break;
    }

    return action;
}

//performs action on the list for each (action,value) pair
void parseAction(List *list,int action, char *value,int length)
{
    double real = 0.0;
    int pos = 0;

    switch(action)
    {
        case ACTION_PRINT: list->print(); break;
        case ACTION_APPEND:
            if(isnan(real = parseReal(value,length)))
                break;
            list->append(real);
        break;
        case ACTION_DELETE:
            if((pos = parseInt(value,length)) < 0)
                break;
            list->remove(pos);
        break;
        default: break;
    }

    return;
}


#ifndef _UNIT_TESTS
int main(int argc, char * argv[])
{
	List L;

	if(argc !=2)
    {
		printf("ERROR");
		return 0;
	}

    int index = 0;
    int length = 0;
    int action = ACTION_NA;
    int new_action = ACTION_NA;

    char *value = NULL;

    //allocate space for value
    value = (char*)calloc(strlen(argv[1])+1,sizeof(char));

    //loop through each character till all actions are done
    for(;action != ACTION_DONE;index++)
    {
        //check for new action
        if((new_action = isAction(argv[1][index])) != ACTION_NA)
        {
            parseAction(&L,action,value,length);
            action = new_action;
            memset(value,0,strlen(argv[1])+1);
            length = 0;
        }//append to value if current action is append or delete
        else if(action == ACTION_APPEND || action == ACTION_DELETE)
        {
            value[length++] = argv[1][index];
        }
    }

    free(value);

	return 0;
}
#endif

#ifdef _UNIT_TESTS

TEST_CASE("valid integers","[pint][pos]")
{
    //Single digit
    CHECK(parseInt("0",1) == 0);
    CHECK(parseInt("1",1) == 1);
    CHECK(parseInt("6",1) == 6);

    //Single digit with positive sign
    CHECK(parseInt("+0",2) == 0);
    CHECK(parseInt("+1",2) == 1);
    CHECK(parseInt("+5",2) == 5);
    //Single digit with negative sign
    CHECK(parseInt("-0",2) == 0);
    CHECK(parseInt("-1",2) == -1); //Hmmm???
    CHECK(parseInt("-8",2) == -8);

    //Multiple digits
    CHECK(parseInt("12",2) == 12);
    CHECK(parseInt("345",3) == 345);
    CHECK(parseInt("6789",4) == 6789);

    //Multiple digits with positive sign
    CHECK(parseInt("+12",3) == 12);
    CHECK(parseInt("+345",4) == 345);
    CHECK(parseInt("+6789",5) == 6789);
    //Multiple digits with negative sign
    CHECK(parseInt("-12",3) == -12);
    CHECK(parseInt("-345",4) == -345);
    CHECK(parseInt("-6789",5) == -6789);

    //Ints starting with 0's
    CHECK(parseInt("012",3) == 12);
    CHECK(parseInt("00345",5) == 345);
    CHECK(parseInt("0006789",7) == 6789);

    //Ints starting with +0's and 
    CHECK(parseInt("+012",4) == 12);
    CHECK(parseInt("+00345",6) == 345);
    CHECK(parseInt("+0006789",8) == 6789);
    //Ints starting with -0's
    CHECK(parseInt("-012",4) == -12);
    CHECK(parseInt("-00345",6) == -345);
    CHECK(parseInt("-0006789",8) == -6789);
}

TEST_CASE("invalid strings for integers","[pint][neg]")
{
    CHECK(parseInt("a",1) == -1);
    CHECK(parseInt("+",1) == -1);
    CHECK(parseInt("*",1) == -1);
}

TEST_CASE("valid real numbers","[preal][pos]")
{
    CHECK(parseReal("1",1) == 1.0);
    CHECK(parseReal("+1",2) == 1.0);
    CHECK(parseReal("-1",2) == -1.0);
    CHECK(parseReal("1.",2) == 1.0);
    CHECK(parseReal("+1.",3) == 1.0);
    CHECK(parseReal("-1.",3) == -1.0);
    CHECK(parseReal(".1",2) == 0.1);
    CHECK(parseReal("+.1",3) == 0.1);
    CHECK(parseReal("-.1",3) == -0.1);
    CHECK(parseReal("1.0",3) == 1.0);    
    CHECK(parseReal("+1.0",4) == 1.0);    
    CHECK(parseReal("-1.0",4) == -1.0);

    CHECK(parseReal("1e1",3) == 10.0);
    CHECK(parseReal("+1e1",4) == 10.0);
    CHECK(parseReal("-1e1",4) == -10.0);
    CHECK(parseReal("1e+1",4) == 10.0);
    CHECK(parseReal("1e-1",4) == 0.1);
    CHECK(parseReal("+1e+1",5) == 10.0);
    CHECK(parseReal("-1e-1",5) == -0.1);

    CHECK(parseReal("1.e1",4) == 10.0);
    CHECK(parseReal("+1.e1",5) == 10.0);
    CHECK(parseReal("-1.e1",5) == -10.0);
    CHECK(parseReal(".1e1",4) == 1.0);
    CHECK(parseReal("+.1e1",5) == 1.0);
    CHECK(parseReal("-.1e1",5) == -1.0);
    CHECK(parseReal("1.e+1",5) == 10.0);
    CHECK(parseReal("1.e-1",5) == 0.1);
    CHECK(parseReal("+1.e+1",6) == 10.0);
    CHECK(parseReal("-1.e-1",6) == -0.1);
    CHECK(parseReal("+.1e+1",6) == 1.0);
    CHECK(parseReal("-.1e-1",6) == -0.01);
}

TEST_CASE("invalid input for real numbers","[preal][neg]")
{
    CHECK(isnan(parseReal("a",1)));
    CHECK(isnan(parseReal("--2.0",5)));
    CHECK(isnan(parseReal("1.3.1",5)));
}
#endif

