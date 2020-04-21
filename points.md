# CJson_use
我学到了什么
作业内容及输入输出规范https://docs.qq.com/doc/DRFFwbXFIV1NzVndZ
1.JSON是什么？(https://www.json.org/json-en.html)。简单来说,json就是javascript的对象和数组，本质是字符串。对象由{}界定，数组由[]界定
2.cJSON构建，解析函数(https://www.json.org/json-en.html)
   1.构建
        1. 主要使用的构建函数` cJSON_AddItemToObject(root,content,item) `将content加到item中
        2. 难点，根据要求的内容构建出符合逻辑的json字符串，搞清内外层的关系。
        3. 读入时构建线性表，根据不同的类型进行分类。
        4. 构建时phone中可能有1个或两个电话号码，中间用“，”相隔。
              本例中使用strtok函数来隔离“，”`char *strtok(char *str, const char *delim) `
              delim为分隔符，对str进行分割
              使用例子
```
  char *token;
   
   /* 获取第一个子字符串 */
   token = strtok(str, s);
   
   /* 继续获取其他的子字符串 */
   while( token != NULL ) {
      printf( "%s\n", token );
    
      token = strtok(NULL, s);
   }
```
    2.解析
        1. 主要函数`  cJSON_GetObjectItem(cjson,"string"); ` 得到指定string键的值内容
        2.` cJSON_GetArrayItem(array,j)->valuestring; `得到数组array中的第j个内容，valuestring也可以是valueing，valuechar等
        3. 本例中电话号的多少不确定，使用` cJSON_GetArraySize(phones); ` 得到数组大小
