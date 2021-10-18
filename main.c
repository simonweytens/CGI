#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <time.h>

#define MAXLEN 80
#define EXTRA 5
/* 4 for field name "data", 1 for "=" */
#define MAXINPUT MAXLEN + EXTRA + 2

// void unencode(char *src, char *last, char *dest)
// {
//  for(; src != last; src++, dest++)
//    if(*src == '+')
//      *dest = ' ';
//    else if(*src == '%') {
//      int code;
//      if(sscanf(src+1, "%2x", &code) != 1) code = '?';
//      *dest = code;
//      src +=2; }
//    else
//      *dest = *src;
//  *dest = '\n';
//  *++dest = '\0';
// }

int main(void)
{
  char *querystr;
  FILE *fp;

  fp = fopen("test.json", "w");

  printf("%s%c%c\n",
         "Content-Type:text/html;charset=iso-8859-1", 13, 10);
  printf("<TITLE>Response</TITLE>");

  querystr = getenv("QUERY_STRING");
  printf("<P>%s", querystr);

  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  //json object creëren
  json_object *jobj = json_object_new_object();

  //json strings maken
  //json_object *jstring = json_object_new_string("Posts");
  json_object *jstring1 = json_object_new_string(querystr);
  json_object *jtime = json_object_new_string(asctime(timeinfo));

  //json array maken
  json_object *jarray = json_object_new_array();

  json_object_array_add(jarray, jstring1);
  json_object_object_add(jobj, "posts", jarray);

  printf("The json object created: %sn", json_object_to_json_string(jobj));
  fprintf(fp, "%s", json_object_to_json_string(jobj));
  fclose(fp);
  return 0;
}