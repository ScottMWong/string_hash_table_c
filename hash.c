/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Scott Wong
 */

#include "hash.h"

// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a() {
  //Initalise variables
  int lines;
  int modnum;

  scanf("%d",&lines);
  scanf("%d",&modnum);

  string inputs[lines];
  int charvals[lines][256];
  int stringlengths[lines];
  int hashvals[lines];

  int count;
  int charcount;
  int temphash;
  char tempchar;
  string temp = "";
  int stringlen;
  //Take in all inputs
  for (count = 0; count < lines; count++) {
    scanf("%s", temp);
    inputs[count] = temp;
  }
  //Hash function
  //Get the values for each character
  for (count = 0; count < lines; count++) {
    stringlen = strlen(inputs[count]);
    stringlengths[count] = stringlen;
    for (charcount = 0; charcount < stringlen; charcount++) {
      tempchar = inputs[count][charcount];
      //Checks for cases where char is digit, lowercase or uppercase
      //Digit case
      if (tempchar <= 57) {
        charvals[count][charcount] = tempchar + 4;
      }
      //Uppercase case
      else if (tempchar <= 90 && tempchar >= 65) {
        charvals[count][charcount] = tempchar - 39;
      }
      //Lowercase case
      else {
        charvals[count][charcount] = tempchar - 97;
      }
    }
  }
  //Apply mod M step
  for (count = 0; count < lines; count++) {
    temphash = 0;
    for (charcount = 0; charcount < stringlengths[count]; charcount++) {
      //Use Horner's Rule
      temphash = ((temphash * 64) + charvals[count][charcount]) % modnum;
    }
    //Save final hash value
    hashvals[count] = temphash;
  }
  //Prints the hash values
  for (count = 0; count < lines; count++) {
    printf("%d",hashvals[count]);
  }
}

// Implements a solution to Problem 1 (b), which reads in from stdin:
//   N M K
//   str_1
//   str_2
//   ...
//   str_N
// Each string is inputed (in the given order) into a hash table with size
// M. The collision resolution strategy must be linear probing with step
// size K. If an element cannot be inserted then the table size should be
// doubled and all elements should be re-hashed (in index order) before
// the element is re-inserted.
//
// This function must output the state of the hash table after all insertions
// are performed, in the following format
//   0: str_k
//   1:
//   2: str_l
//   3: str_p
//   4:
//   ...
//   (M-2): str_q
//   (M-1):
void problem_1_b() {
  //Initalise variables
  int lines;
  int modnum;
  int probenum;

  scanf("%d",&lines);
  scanf("%d",&modnum);
  scanf("%d",&probenum);

  string inputs[lines];
  int charvals[lines][256];
  int stringlengths[lines];

  int count;
  int charcount;
  char tempchar;
  string temp;
  temp = malloc(1000);
  int stringlen;
  //Take in all inputs
  for (count = 0; count < lines; count++) {
    scanf("%s", temp);
    inputs[count] = temp;
  }
  //Hash function
  //Get the values for each character
  for (count = 0; count < lines; count++) {
    stringlen = strlen(inputs[count]);
    stringlengths[count] = stringlen;
    for (charcount = 0; charcount < stringlen; charcount++) {
      tempchar = inputs[count][charcount];
      //Checks for cases where char is digit, lowercase or uppercase
      //Digit case
      if (tempchar <= 57) {
        charvals[count][charcount] = tempchar + 4;
      }
      //Uppercase case
      else if (tempchar <= 90 && tempchar >= 65) {
        charvals[count][charcount] = tempchar - 39;
      }
      //Lowercase case
      else {
        charvals[count][charcount] = tempchar - 97;
      }
    }
  }
  //Call hash table function

  hash_table_write(lines, modnum, probenum, inputs, stringlengths, charvals);
}

//1b Hash table function
void hash_table_write(int lines, int modnum, int probenum, string *inputs, int *stringlengths, int charvals[][256]) {
  //Initalise variables
  string hashtable[modnum];
  int hashvals[lines];
  int count;
  int charcount;
  int temphash;
  int keytotry;
  int firstkeytry;

  //For each input
  for (count = 0; count < lines; count++) {
    //get the hash values
    temphash = 0;
    for (charcount = 0; charcount < stringlengths[count]; charcount++) {
      //Use Horner's Rule
      temphash = ((temphash * 64) + charvals[count][charcount]) % modnum;
    }
    hashvals[count] = temphash;
  }
  //Fill hash table with placeholder characters
  for (count = 0; count < modnum; count++) {
    hashtable[count] = "\0";
  }

  //Writing to hash table
  for (count = 0; count < lines; count++) {
    //check if target array cell is not filled
    keytotry = hashvals[count];
    firstkeytry = keytotry;
    if (strcmp(hashtable[keytotry],"\0") == 0) {
      hashtable[keytotry] = inputs[keytotry];
    }
    //if target array cell was filled, linear probe
    else {
      keytotry = (keytotry + probenum) % modnum;
      //keep probing until you get back where you started or insert element
      while (1) {
        //if this is the case need to rehash, call function again with doubled modnum
        if (keytotry == firstkeytry) {
          hash_table_write(lines, modnum * 2, probenum, inputs, stringlengths, charvals);
          return;
        }
        else {
          if (strcmp(hashtable[keytotry],"\0") == 0) {
            hashtable[keytotry] = inputs[keytotry];
            break;
          }
        }
        keytotry = (keytotry + probenum) % modnum;
      }
    }
  }
  //Print hash table
  for (count = 0; count < modnum; count++) {
    //check if there is string in array slot
    if (strcmp(hashtable[count],"\0") == 0) {
      printf("%d", count);
      printf(": ");
      printf("\n");
    }
    else {
        printf("%d", count);
        printf(": ");
        printf("%s", hashtable[count]);
        printf("\n");
    }
  }

}
