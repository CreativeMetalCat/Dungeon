#pragma once

#ifndef to_string
#define STRING std::to_string
#endif // !to_string

#ifndef EXEC_IF_VALID
//Executes like of code if given object is valid
//This macro exists purely to reduce amount of multiline "if" in the code
//also it makes code look like BASIC, take that as you wish
//Avoid using this
#define EXEC_IF_VALID(obj, code) if(obj){code}
#endif // !EXEC_IF_VALID


#ifndef EXEC_IF_VALID_OBJ
//Executes like of code if given object is valid
//This macro exists purely to reduce amount of multiline "if" in the code
//also it makes code look like BASIC, take that as you wish
//Avoid using this
#define EXEC_IF_VALID_OBJ(obj, code) if(obj.Valid()){code}
#endif // !EXEC_IF_VALID_OBJ

