%skeleton "lalr1.cc"
%require  "3.0.1"

%defines 
%define api.namespace {IPL}
%define api.parser.class {Parser}

%define parse.trace

%code requires{
   namespace IPL {
      class Scanner;
   }
   #include "symbol_table.hh"
   #include "location.hh"

  // # ifndef YY_NULLPTR
  // #  if defined __cplusplus && 201103L <= __cplusplus
  // #   define YY_NULLPTR nullptr
  // #  else
  // #   define YY_NULLPTR 0
  // #  endif
  // # endif

}

%printer { std::cerr << $$; } INT
%printer { std::cerr << $$; } VOID
%printer { std::cerr << $$; } FLOAT
%printer { std::cerr << $$; } STRUCT
%printer { std::cerr << $$; } WHILE
%printer { std::cerr << $$; } FOR
%printer { std::cerr << $$; } IF
%printer { std::cerr << $$; } ELSE
%printer { std::cerr << $$; } RETURN
%printer { std::cerr << $$; } OR_OP
%printer { std::cerr << $$; } AND_OP
%printer { std::cerr << $$; } EQ_OP
%printer { std::cerr << $$; } NE_OP
%printer { std::cerr << $$; } LE_OP
%printer { std::cerr << $$; } GE_OP
%printer { std::cerr << $$; } INC_OP
%printer { std::cerr << $$; } PTR_OP
%printer { std::cerr << $$; } IDENTIFIER
%printer { std::cerr << $$; } INT_CONSTANT
%printer { std::cerr << $$; } FLOAT_CONSTANT
%printer { std::cerr << $$; } STRING_LITERAL
%printer { std::cerr << $$; } EOFILE
%printer { std::cerr << $$; } OTHERS

%parse-param { Scanner  &scanner  }
%locations
%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>
   #include <vector>
   #include <map>
   
   
   #include "scanner.hh"
   #include "symbol_table.hh"

#undef yylex
#define yylex IPL::Parser::scanner.yylex

using namespace IPL;
  int count_label = 0;
  int curr_offset = 0;
  int count_temp_var = 0;
  int esp_increase_index;
  std::string curr_struct_name;
  std::vector<std::string> labels;
  std::vector<std::string> functions;

  std::stack<int> reserve_lbl1;
  std::stack<int> reserve_lbl2;


  std::vector<GST_entry> GST;
  LST *lst;

  std::map<std::string, int> func_to_return_size;
  std::map<std::string, bool>func_to_isReturnStruct;
  std::map<std::string, Func_Def> funName_to_FuncDef;
  std::map<std::string, int> struct_to_size;
  std::map<std::string, LST> struct_to_lst;

  std::string curr_fun;


  void function_start_helper(std::string fun_name)
  {
    functions.push_back(".globl\t"+fun_name);
    functions.push_back(".type\t"+fun_name+", @function");
    functions.push_back(fun_name+":");
    functions.push_back("\tpushl\t%ebp");
    functions.push_back("\tmovl\t%esp, %ebp");
  }

  void function_end_helper()
  {
    functions.push_back("\tleave");
    functions.push_back("\tret");
  }

  void print_labels()
  {
    for(auto i:labels)
      std::cout<<i<<std::endl;
  }

  void print_functions()
  {
    for(auto i:functions)
      std::cout<<i<<std::endl;
  }
}

%define api.value.type variant
%define parse.assert

%start program

%token '\n' '\t'
%token <std::string> MAIN PRINTF
%token <std::string> INT VOID FLOAT STRUCT WHILE FOR IF ELSE RETURN
%token <std::string> OR_OP AND_OP EQ_OP NE_OP LE_OP GE_OP
%token <std::string> INC_OP PTR_OP
%token <std::string> INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token <std::string> IDENTIFIER
%token <std::string> OTHERS EOFILE
%token '{' '}' ';' '*' '(' ')' ',' '[' ']' '=' '<' '>' '+' '-' '/' '.' '!' '&'

%nterm <int> program
%nterm <int> main_definition
%nterm <int> translation_unit
%nterm <Func_Def*> function_definition
%nterm <int> struct_specifier
%nterm <int> compound_statement
%nterm <int> statement_list
%nterm <int> statement
%nterm <Type_Specifier*> type_specifier
%nterm <Declaration_List*> declaration_list
%nterm <Declaration*> declaration
%nterm <Declarator_List*> declarator_list
%nterm <Declarator*> declarator declarator_arr
%nterm <Expression_node*> expression
%nterm <Expression_List*> expression_list
%nterm <Assign_Node*> assignment_expression
%nterm <Expression_node*> logical_and_expression
%nterm <Expression_node*> equality_expression
%nterm <Expression_node*> relational_expression
%nterm <Expression_node*> additive_expression multiplicative_expression
%nterm <Expression_node*> unary_expression
%nterm <Expression_node*> postfix_expression
%nterm <Expression_node*> primary_expression
%nterm <Unary_Operator_Node*> unary_operator
%nterm <printf_astnode*> printf_call
%nterm <selection_astnode*> selection_statement
%nterm <iteration_astnode*> iteration_statement
%nterm <Parameter_List*> parameter_list
%nterm <Parameter*> parameter_declaration
%nterm <int> procedure_call



%%

program :
  main_definition
  {
    print_labels();
    print_functions();
  }
  | translation_unit main_definition // P3
  {
    print_labels();
    print_functions();
  }

main_definition : 
  INT MAIN '('
  {
    function_start_helper("main");
    lst = new LST();
    count_temp_var = 0;
    curr_offset = 0;
    curr_fun = $2;
    func_to_isReturnStruct[$2] = false;
  } ')' compound_statement
  {
    //A place was reserved when the control was inside compound statement to increase esp by the size required
    //to store all the temporary variables, which is stored in count_temp_var
    functions[esp_increase_index] = "\tsubl\t$" + std::to_string(4*count_temp_var) + ", %esp";
    
    function_end_helper();


    Func_Def* temp_func_def;
    temp_func_def = new Func_Def();
    // TODO : Fun_def() is not initialized yet. We will see if we need it later
    temp_func_def->return_size = 1;
    temp_func_def->b_type = Base_Type::INT;

    funName_to_FuncDef[$2] = *temp_func_def;

    // functions.push_back("var to struct of x : " + lst->var_to_struct["x"] + "\n");
    // functions.push_back("var to struct of y : " + lst->var_to_struct["y"] + "\n");
    // functions.push_back("\taddl\t$" + std::to_string(4*count_temp_var) + ", %esp");
    //GST.push_back(new GST_entry("main", Symbol_Type::Func, lst));
  }

translation_unit
  : struct_specifier // P4
  | function_definition // P3
  | translation_unit function_definition // P3
  | translation_unit struct_specifier // P4

/* Struct Declaration */

struct_specifier
  : STRUCT IDENTIFIER '{'
  {
    lst = new LST();
    curr_offset = 0;
    curr_struct_name = $2;

  } declaration_list '}'
  {
    int struct_size = 0;
    
    // functions.push_back("entering struct\n");
    // Set offsets of all variables in the struct and prepare its lst
    while(!$5->declarations_stack.empty())
    {
      int size_ = $5->declarations_stack.top().type_spec_size;

      std::stack<Declarator> var_stack = $5->declarations_stack.top().var_stack;
      $5->declarations_stack.pop();

      // struct_size += (var_stack.size()*size_);
      
      while(!var_stack.empty())
      {
        Declarator d = var_stack.top();
        var_stack.pop();

        // lst->var_to_struct[d.name] = $2;

        lst->var_offsets[d.name] = curr_offset-4;
        // functions.push_back("offset of " + d.name + " is " + std::to_string(curr_offset-4) + "\n");

        // std::cout<<"Offset of "<<d.name<<"is "<<curr_offset-4<<"\n or "<< lst->var_offsets[d.name]<<"\n";
        if(lst->pointer_to_details.count(d.name) > 0)
        {
          curr_offset -= 4*d.array_size;
          struct_size += 1*d.array_size;
        }
        else
        {
          curr_offset -= size_*4;
          struct_size += size_;
        }

      }
    }

    //Make entry for struct lst and struct size
    struct_to_size[$2] = struct_size;
    struct_to_lst[$2] = *lst;

    // functions.push_back("Offset of XYZ in struct is " + std::to_string(struct_to_lst[$2].var_offsets["XYZ"]) + "\n");

  }
   ';' // P4

/* Function Definition */

function_definition
  : type_specifier IDENTIFIER '('
  {
    function_start_helper($2);
    lst = new LST();
    count_temp_var = 0;
    //First place is reserved to store the value of edx
    curr_offset = -4;
    curr_fun = $2;

    if($1->b_type == Base_Type::STRUCT)
    {
      func_to_isReturnStruct[$2] = true;
    }
    else
    {
      func_to_isReturnStruct[$2] = false;
    }
  } ')' compound_statement // P3
  {
    Func_Def* temp_func_def;
    temp_func_def = new Func_Def();
    // TODO : Fun_def() is not initialized yet. We will see if we need it later
    temp_func_def->return_size = $1->size;
    temp_func_def->b_type = $1->b_type;

    funName_to_FuncDef[$2] = *temp_func_def;


    // Make an entry for the function name and its return size
    func_to_return_size[$2] = $1->size;

    if($1->b_type == Base_Type::STRUCT)
    {
      func_to_isReturnStruct[$2] = true;
      temp_func_def->struct_name = $1->struct_name;
    }
    else
    {
      func_to_isReturnStruct[$2] = false;
    }

    //A place was reserved when the control was inside compound statement to increase esp by the size required
    //to store all the temporary variables, which is stored in count_temp_var
    functions[esp_increase_index] = "\tsubl\t$" + std::to_string(4*count_temp_var) + ", %esp";

    function_end_helper();

    $$ = temp_func_def;
  }
  | type_specifier IDENTIFIER '('
  {
    function_start_helper($2);
    lst = new LST();
    count_temp_var = 0;
    //First place is reserved to store the value of edx
    curr_offset = -4;
    curr_fun = $2;

    if($1->b_type == Base_Type::STRUCT)
    {
      func_to_isReturnStruct[$2] = true;
    }
    else
    {
      func_to_isReturnStruct[$2] = false;
    }
  } parameter_list ')'
  {
    
    // Set the mapping of parameter variables to its local offsets in the current lst
    Parameter* temp_param;
    int temp_offset=0;

    std::stack<Parameter*> p_list;
    p_list = $5->param_list;

    while(!(p_list.empty()))
    {
      temp_param = p_list.top();
      p_list.pop();

      if(temp_param->b_type == Base_Type::STRUCT)
      {
        if(temp_param->numberOfStars == 0)
        {
        
        int struct_size = struct_to_size[temp_param->struct_name];
        lst->var_to_struct[temp_param->name] = temp_param->struct_name;

        temp_offset += 4*struct_size;
        }
        else
        {
          PointerVariable* pointerDetails = new PointerVariable();

          pointerDetails->numberOfStars = temp_param->numberOfStars;
          pointerDetails->base_type = Base_Type::STRUCT;
          pointerDetails->struct_name = temp_param->struct_name;

          lst->pointer_to_details[temp_param->name] = *pointerDetails;
          temp_offset += 4*temp_param->array_size;
        }          
      }
      else
      {
        if(temp_param->numberOfStars > 0)
        {
          PointerVariable* pointerDetails = new PointerVariable();

          pointerDetails->numberOfStars = temp_param->numberOfStars;
          pointerDetails->base_type = temp_param->b_type;
          pointerDetails->struct_name = "";

          lst->pointer_to_details[temp_param->name] = *pointerDetails;
        }
        
        temp_offset += 4*temp_param->array_size;
      }

      // functions.push_back("Setting offset of " + temp_param->name + "to " + std::to_string(temp_offset));

      lst->var_offsets[temp_param->name] = temp_offset+4;
      
    }
  } compound_statement // P3
  {
    Func_Def* temp_func_def;
    temp_func_def = new Func_Def();
    // TODO : Fun_def() is not initialized yet. We will see if we need it later
    temp_func_def->return_size = $1->size;
    temp_func_def->b_type = $1->b_type;
    

    

    funName_to_FuncDef[$2] = *temp_func_def;
    // Make an entry for the function name and its return size
    func_to_return_size[$2] = $1->size;

    if($1->b_type == Base_Type::STRUCT)
    {
      // functions.push_back("return type of " + $2 + "is STRUCT");
      func_to_isReturnStruct[$2] = true;
      temp_func_def->struct_name = $1->struct_name;
    }
    else
    {
      func_to_isReturnStruct[$2] = false;
    }
    
    //A place was reserved when the control was inside compound statement to increase esp by the size required
    //to store all the temporary variables, which is stored in count_temp_var
    functions[esp_increase_index] = "\tsubl\t$" + std::to_string(4*count_temp_var) + ", %esp";

    function_end_helper();

    $$ = temp_func_def;    
  }

type_specifier
  : VOID // P3
  {
    $$ = new Type_Specifier();
    $$->b_type = Base_Type::VOID;
    $$->size = 0;
  }
  | INT // P1
  {
    $$ = new Type_Specifier();
    $$->b_type = Base_Type::INT;
    $$->size = 1;
  }
  | STRUCT IDENTIFIER // P4
  {
    $$ = new Type_Specifier();
    $$->b_type = Base_Type::STRUCT;
    $$->struct_name = $2;
    $$->size = struct_to_size[$2];
  }

declaration_list : 
  declaration
  {
    $$ = new Declaration_List();
    $$->declarations_stack.push(*$1);
  }
  | declaration_list declaration
  {
    $$ = $1;
    $$->declarations_stack.push(*$2);
  }

declaration :
  type_specifier declarator_list ';'
  {
    $$ = new Declaration();
    $$->var_stack = $2->var_stack;
    $$->type_ = $2->type_;
    $$->type_spec_size = $1->size;

    if($1->b_type == Base_Type::STRUCT)
    {

      // std::cout<<"Size of "<<$1->struct_name << "is "<<s.size<<"\n";

      std::stack<Declarator> var_stack;
      var_stack = $2->var_stack;

      // creating a variable to struct name mapping so as to know later
      // if a variable is struct and if yes, of which type
      while(!var_stack.empty())
      {
        Declarator d = var_stack.top();
        
        if(d.numberOfStars == 0)
        {
          lst->var_to_struct[d.name] = $1->struct_name;
        }
        else
        {
          PointerVariable* pointerDetails = new PointerVariable();

          pointerDetails->numberOfStars = d.numberOfStars;
          pointerDetails->base_type = $1->b_type;
          pointerDetails->struct_name = $1->struct_name;

          lst->pointer_to_details[d.name] = *pointerDetails;
        }
        var_stack.pop();
      }
    }
    else
    {
      std::stack<Declarator> var_stack;
      var_stack = $2->var_stack;

      // creating a variable to struct name mapping so as to know later
      // if a variable is struct and if yes, of which type
      while(!var_stack.empty())
      {
        Declarator d = var_stack.top();
        
        if(d.numberOfStars > 0)
        {
          PointerVariable* pointerDetails = new PointerVariable();
          
          pointerDetails->numberOfStars = d.numberOfStars;
          pointerDetails->base_type = $1->b_type;
          pointerDetails->struct_name = "";
          
          lst->pointer_to_details[d.name] = *pointerDetails;
        }
        var_stack.pop();
      }
    }
  }

declarator_list :
  declarator
  {
    $$ = new Declarator_List();
    $$->var_stack.push(*$1);
    $$->type_ = $1->type_;
  }
  | declarator_list ',' declarator
  {
    $$ = $1;
    $$->var_stack.push(*$3);
  }

declarator :
  declarator_arr
  {
    $$ = $1;
  }
  | '*' declarator  //P5
  {
    $$ = $2;
    $$->is_pointer = true;
    $$->numberOfStars += 1;
  }


declarator_arr :
  IDENTIFIER
  {
    $$ = new Declarator();
    $$->name = $1;
  }
  | declarator_arr '[' INT_CONSTANT ']'   //P6
  {
    $$ = $1;
    $$->is_pointer = true;
    $$->numberOfStars += 1;
    $$->array_size = $$->array_size * std::stoi($3);
  }






/* Parameter List */

parameter_list
  : parameter_declaration // P3
  {
    $$ = new Parameter_List();
    $$->param_list.push($1);
  }
  | parameter_list ',' parameter_declaration // P3
  {
    $$ = $1;
    $$->param_list.push($3);
  }

parameter_declaration
  : type_specifier declarator // P3
  {
    $$ = new Parameter();
    $$->name = $2->name;
    $$->type_ = $2->type_;
    $$->b_type = $1->b_type;
    $$->array_size = $2->array_size;

    $$->numberOfStars = $2->numberOfStars;
    if($1->b_type == Base_Type::STRUCT)
      $$->struct_name = $1->struct_name;
  }

compound_statement
  : '{' '}'
  | '{'
  {
    // Leaving a space to increase the esp so as to accomodate the temporary variables
    // create inside the function
    esp_increase_index = functions.size();
    functions.push_back("asdfghjkl");

    //store the value of %edx in -4(%esp)
    functions.push_back("\tmovl\t%edx, -4(%ebp)\n");
  } statement_list '}'
  | '{' declaration_list '}'
  | '{' declaration_list
  {
    //writing offsets

    while(!$2->declarations_stack.empty())
    {
      int size_ = $2->declarations_stack.top().type_spec_size;

      std::stack<Declarator> var_stack = $2->declarations_stack.top().var_stack;
      $2->declarations_stack.pop();

      while(!var_stack.empty())
      {
        Declarator d = var_stack.top();
        var_stack.pop();


        lst->var_offsets[d.name] = curr_offset-4;

        // std::cout<<"Offset of "<<d.name<<"is "<<curr_offset-4<<"\n or "<< lst->var_offsets[d.name]<<"\n";
        // curr_offset -= size_*4;

        if(lst->pointer_to_details.count(d.name) > 0)
        {
          curr_offset -= 4*d.array_size;
        }
        else
        {
          curr_offset -= size_*4;
        }

      }
    }

    // increasing esp to accomodate all the declared variables
    functions.push_back("subl\t$"+std::to_string(-curr_offset)+", %esp");

    // Leaving a space to increase the esp so as to accomodate the temporary variables
    // create inside the function
    esp_increase_index = functions.size();
    functions.push_back("asdfghjkl");

    //store the value of %edx in -4(%esp)
    functions.push_back("\tmovl\t%edx, -4(%ebp)\n");
  }
  statement_list '}'

statement_list
  : statement
  | statement_list statement

statement
  : ';'
  | '{' statement_list '}'
  | assignment_expression ';'
  | selection_statement
  {
    functions.push_back("LC" + std::to_string(reserve_lbl2.top()) + ":");
    reserve_lbl2.pop();
  }
  | iteration_statement
  {
    functions.push_back("LC" + std::to_string(reserve_lbl1.top()) + ":");
    reserve_lbl1.pop();
  }
  | procedure_call // P3
  | printf_call
  {
    std::reverse($1->arguments.begin(), $1->arguments.end());
    for(auto i:$1->arguments)
    {
      if(i.is_struct || i.is_pointer)
      {
        functions.push_back("\tmovl\t" + std::to_string(lst->var_offsets[i.var_name]) + "(%ebp), %eax");
        functions.push_back("\tpushl\t(%eax)");
      }
      else
        functions.push_back("\tpushl\t" + std::to_string(lst->var_offsets[i.var_name]) + "(%ebp)");
    }
      functions.push_back("\tpushl\t$LC"+std::to_string($1->label_number));
      functions.push_back("\tcall\tprintf");

    functions.push_back("\taddl\t$" + std::to_string(4*($1->arguments.size()+1)) + ", %esp");

  }
  | RETURN expression ';' // P1
  {
  
    // auto it = funName_to_FuncDef.find(curr_fun);
    // if(it == funName_to_FuncDef.end())
    //   functions.push_back("Entry for func doesn't exists");

    // functions.push_back("return type of " + curr_fun + " is " + funName_to_FuncDef[curr_fun].struct_name);
    if(func_to_isReturnStruct[curr_fun])
    // if($2->is_struct)
    {
      int return_size = struct_to_size[lst->var_to_struct[$2->var_name]];


      // functions.push_back("Size of struct returning is " + std::to_string(return_size) + "\n");
      
      functions.push_back("\tmovl\t" + std::to_string(lst->var_offsets[$2->var_name]) + "(%ebp), %eax");
      functions.push_back("\tmovl\t%eax, %ebx");

      //load the value of %edx from -4(%ebp)
      functions.push_back("\tmovl\t-4(%ebp), %edx\n");

      for(int i=0;i<return_size;i++)
      {
          // functions.push_back("variable name : " + exp1->var_name + " size : " + std::to_string(exp1->type_spec_size));
          functions.push_back("\tmovl\t" + std::to_string(-4*i) + "(%ebx), %ecx");
          functions.push_back("\tmovl\t%ecx, " + std::to_string(-4*i) + "(%edx)");
      }

      //base address of the return space is stored in %ecx
      functions.push_back("\tmovl\t%edx, %ecx");
    }
    else
    {
      struct_OP_handler($2, functions, lst);
      // store the return value in %ecx
      functions.push_back(load(lst->var_offsets[$2->var_name], "%ecx", 1));
    }


    // functions.push_back("\taddl\t$" + std::to_string(4*count_temp_var) + ", %esp");
    // functions.push_back("\tpopl\t%ebp");

    function_end_helper();
  
  }

assignment_expression : 
  unary_expression '=' expression
  {
    $$ = new Assign_Node();
    $$->exp1 = $1;
    $$->exp2 = $3;

    $$->assembly_print(functions, lst);
  }

expression :
  logical_and_expression
  {
    $$ = $1;
  }
  | expression OR_OP logical_and_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::OR, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }

logical_and_expression :
  equality_expression
  {
    $$ = $1;
  }
  | logical_and_expression AND_OP equality_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::AND, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }

equality_expression :
  relational_expression
  {
    $$ = $1;
  }
  | equality_expression EQ_OP relational_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::EQ, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }
  | equality_expression NE_OP relational_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::NE, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }

relational_expression :
  additive_expression
  {
    $$ = $1;
  }
  | relational_expression '<' additive_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::LL, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }
  | relational_expression '>' additive_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::GG, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }
  | relational_expression LE_OP additive_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::LE, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }
  | relational_expression GE_OP additive_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::GE, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }

additive_expression :
  multiplicative_expression
  {
    $$ = $1;
  }
  | additive_expression '+' multiplicative_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::ADD, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }
  | additive_expression '-' multiplicative_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::SUB, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }

multiplicative_expression :
  unary_expression
  {
    $$ = $1;
  }
  | multiplicative_expression '*' unary_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::MUL, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }
  | multiplicative_expression '/' unary_expression
  {
    $$ = Binary_Operation_Helper($1, $3, Binary_OP::DIV, count_temp_var, curr_offset, functions, lst);

    
    curr_offset -=4;

    count_temp_var+=1;
  }

unary_expression :
  postfix_expression
  {
    $$ = $1;
  }
  | unary_operator unary_expression
  {
    $$ = Unary_Operation_Helper($2, $1->op, count_temp_var, curr_offset, functions, lst, struct_to_size);

    

    curr_offset -=4;

    count_temp_var+=1;
  }

postfix_expression :
  primary_expression
  {
    $$ = $1;
  }
  | postfix_expression INC_OP
  {
    $$ = Unary_Operation_Helper($1, Unary_OP::OP_POST_INC, count_temp_var, curr_offset, functions, lst, struct_to_size);


    curr_offset -=4;

    count_temp_var+=1;
  }
  | IDENTIFIER '(' ')' // P3
  {
      $$ = new Expression_node();
      //if the return type of a function is a struct, create a space here before calling
      //function. Also, store the base address of this space in %edx

      Func_Def temp_func_def = funName_to_FuncDef[$1];
      int return_size = temp_func_def.return_size;
      $$->type_spec_size = return_size;
      if(temp_func_def.b_type == Base_Type::STRUCT)
      {
        functions.push_back("\tmovl\t%esp, %edx\n");
        functions.push_back("\tsubl\t$" + std::to_string(4*return_size) + ", %esp\n");
      }
      
      
      functions.push_back("\tcall\t" + $1);
      // return value would be stored in %eax

      $$ = new Expression_node();
      std::string variable_name = "t"+std::to_string(count_temp_var);
      $$->var_name = variable_name;
      curr_offset -=4;
      lst->var_offsets["t"+std::to_string(count_temp_var)] = curr_offset;

      count_temp_var+=1;

      if(temp_func_def.b_type == Base_Type::STRUCT)
      {
          $$->is_struct = true;
          lst->var_to_struct[variable_name] = temp_func_def.struct_name;
      }
    
      // IMPORTANT : Handle the cases where function returns a struct
      // or doesn't return anything at all
      
      // functions.push_back("subl\t$4, %esp");
      // store the value of %eax in $->var_name
      functions.push_back(store(curr_offset, "%ecx", 1));


  }
  | IDENTIFIER '(' expression_list ')' // P3
  {
  
    $$ = new Expression_node();
    //if the return type of a function is struct, create a space here before calling
    //function. Also, store the base address of this space in %edx
    Func_Def temp_func_def = funName_to_FuncDef[$1];
    int return_size = temp_func_def.return_size;
    $$->type_spec_size = return_size;
    if(temp_func_def.b_type == Base_Type::STRUCT)
    {
      functions.push_back("\tmovl\t%esp, %edx\n");
      functions.push_back("\tsubl\t$" + std::to_string(4*return_size) + ", %esp\n");
    }
    
    std::vector<Expression_node> temp_exp_list;
    temp_exp_list = $3->exp_list;

    // std::reverse(temp_exp_list.begin(), temp_exp_list.end());

    // e

    for(auto i:temp_exp_list)
    {
      if(i.is_struct)
      {
        functions.push_back("\tmovl\t" + std::to_string(lst->var_offsets[i.var_name]) + "(%ebp), %eax");
        // functions.push_back("Copying variable " + i.var_name + " of type struct " + lst->var_to_struct[i.var_name] + " with size " + std::to_string(i.type_spec_size) + "\n");
        for(int j=0;j<i.type_spec_size;j++)
          functions.push_back("\tpushl\t"+ std::to_string(-4*j) +"(%eax)");
      }
      else
        functions.push_back("\tpushl\t" + std::to_string(lst->var_offsets[i.var_name]) + "(%ebp)");
    }


    functions.push_back("\tcall\t" + $1);
    // return value would be stored in %eax


    functions.push_back("\taddl\t$" + std::to_string(4*(temp_exp_list.size())) + ", %esp");

    std::string variable_name = "t"+std::to_string(count_temp_var);
    $$->var_name = variable_name;
    curr_offset -=4;
    lst->var_offsets["t"+std::to_string(count_temp_var)] = curr_offset;

    count_temp_var+=1;
  
    if(temp_func_def.b_type == Base_Type::STRUCT)
    {
        $$->is_struct = true;
        lst->var_to_struct[variable_name] = temp_func_def.struct_name;
    }
    
    // functions.push_back("subl\t$4, %esp");
    // store the value of %eax in $->var_name
    functions.push_back(store(curr_offset, "%ecx", 1));
    
  }
  | postfix_expression '.' IDENTIFIER // P4
  {
    // name_to_struct[$1->var_name]->lst->var_offsets[$3] + lst->var_offsets[$1->var_name] + 4
    
    // std::cout<<"ETF ";
    $$ = new Expression_node();

    
    int temp = lst->var_offsets[$1->var_name];

    // if(!temp)
    functions.push_back("\tmovl\t"+std::to_string(temp) + "(%ebp), %eax");
    // functions.push_back("\tmovl\t(%eax), %eax");

    // std::cout<<s->size;
    LST struct_lst = struct_to_lst[lst->var_to_struct[$1->var_name]];

    // functions.push_back("name of struct is " + lst->var_to_struct[$1->var_name] + "\n");
    // functions.push_back("name of variable is " + $1->var_name + "\n");

    int new_offset = struct_lst.var_offsets[$3];
    // functions.push_back("The variable name is " + $3 + " and its offset is " + std::to_string(new_offset) + "\n");

    std::string variable_name = "t"+std::to_string(count_temp_var);
    $$->var_name = variable_name;

    //check if x.a is a pointer. If yes, make an entry in the pointer_to_details
    if(struct_lst.pointer_to_details.count($3) > 0)
    {
      lst->pointer_to_details[variable_name] = struct_lst.pointer_to_details[$3];
    }


    curr_offset -= 4;
    count_temp_var += 1;
    lst->var_offsets[variable_name] = curr_offset;

    // std::cout<<"new offset of \t"<<$3<<"\t"<<std::to_string(new_offset) << "\n";
    // std::cout<<"Size of struct lst var offsets"<<" of "<<$3<<" "<<struct_lst.var_offsets.size()<<"\n";

    // std::cout<<"\n\n";
    // for(auto i:struct_lst.var_offsets)
    //   std::cout<<i.first<<"\t"<<i.second<<"\n";
    // std::cout<<"number of struct nodes "<<temp_s_node_vec.size()<<"\n";
    // std::cout<<"number of name to struct index "<<name_to_struct_ind.size()<<"\n";
    functions.push_back("\tleal\t" + std::to_string(4+new_offset) + "(%eax), %eax");
    // functions.push_back("debugging\n");
    functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset)+"(%ebp)");

    if(struct_lst.var_to_struct[$3]!="")
    {
      $$->type_spec_size = struct_to_size[struct_lst.var_to_struct[$3]];
      lst->var_to_struct[variable_name] = struct_lst.var_to_struct[$3];
      // functions.push_back("variable name : " + struct_lst.var_to_struct[$3] + $1->var_name + "." + $3 +" size : " + std::to_string(struct_to_size[struct_lst.var_to_struct[$3]]));
    }
    else
    {
      $$->type_spec_size =1;
    }

    $$->is_struct = true;
  }
  | postfix_expression PTR_OP IDENTIFIER
  {
    $$ = new Expression_node();

    
    int temp = lst->var_offsets[$1->var_name];

    // if(!temp)
    functions.push_back("\tmovl\t"+std::to_string(temp) + "(%ebp), %eax");
    // functions.push_back("\tmovl\t(%eax), %eax");

    // std::cout<<s->size;
    LST struct_lst = struct_to_lst[lst->pointer_to_details[$1->var_name].struct_name];

    // functions.push_back("name of struct is " + lst->var_to_struct[$1->var_name] + "\n");
    // functions.push_back("name of variable is " + $1->var_name + "\n");

    int new_offset = struct_lst.var_offsets[$3];
    // functions.push_back("The variable name is " + $3 + " and its offset is " + std::to_string(new_offset) + "\n");

    std::string variable_name = "t"+std::to_string(count_temp_var);
    $$->var_name = variable_name;

    //check if x.a is a pointer. If yes, make an entry in the pointer_to_details
    if(struct_lst.pointer_to_details.count($3) > 0)
    {
      lst->pointer_to_details[variable_name] = struct_lst.pointer_to_details[$3];
    }


    curr_offset -= 4;
    count_temp_var += 1;
    lst->var_offsets[variable_name] = curr_offset;

    // std::cout<<"new offset of \t"<<$3<<"\t"<<std::to_string(new_offset) << "\n";
    // std::cout<<"Size of struct lst var offsets"<<" of "<<$3<<" "<<struct_lst.var_offsets.size()<<"\n";

    // std::cout<<"\n\n";
    // for(auto i:struct_lst.var_offsets)
    //   std::cout<<i.first<<"\t"<<i.second<<"\n";
    // std::cout<<"number of struct nodes "<<temp_s_node_vec.size()<<"\n";
    // std::cout<<"number of name to struct index "<<name_to_struct_ind.size()<<"\n";
    functions.push_back("\tleal\t" + std::to_string(4+new_offset) + "(%eax), %eax");
    // functions.push_back("debugging\n");
    functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset)+"(%ebp)");

    if(struct_lst.var_to_struct[$3]!="")
    {
      $$->type_spec_size = struct_to_size[struct_lst.var_to_struct[$3]];
      lst->var_to_struct[variable_name] = struct_lst.var_to_struct[$3];
      // functions.push_back("variable name : " + struct_lst.var_to_struct[$3] + $1->var_name + "." + $3 +" size : " + std::to_string(struct_to_size[struct_lst.var_to_struct[$3]]));
    }
    else
    {
      $$->type_spec_size =1;
    }

    $$->is_struct = true;
  }
  | postfix_expression '[' expression ']' //P6
  {
    $$ = new Expression_node();
    
    std::string variable_name = "t"+std::to_string(count_temp_var);
    $$->var_name = variable_name;

    curr_offset -= 4;
    count_temp_var += 1;
    lst->var_offsets[variable_name] = curr_offset;

    $$->is_pointer = true;

    
    
    int array_unitary_size;
    if(lst->pointer_to_details.count($1->var_name) > 0)
    {
      PointerVariable pointerDetails = lst->pointer_to_details[$1->var_name];
      if(pointerDetails.base_type == Base_Type::STRUCT)
      {
        array_unitary_size = struct_to_size[pointerDetails.struct_name];
        $$->is_struct = true;
      }
      else
        array_unitary_size = 1;
    }
    else
      array_unitary_size = 1;

    //store exp_value in %eax
    functions.push_back(load(lst->var_offsets[$3->var_name], "%eax", 1));

    //store array_unitary_size in %ebx
    functions.push_back("\tmovl\t$" + std::to_string(array_unitary_size) + ", %ebx");

    //multiply %ebx by %eax
    functions.push_back("\timull\t%eax, %ebx");

    int offset1 = lst->var_offsets[$1->var_name];

    //store the base address of array in eax
    functions.push_back("\tleal\t"+std::to_string(offset1) + "(%ebp), %eax");

    functions.push_back("\taddl\t%ebx, %eax");

    //store the value in %eax to the variable created
    functions.push_back(store(curr_offset, "%eax", 1));

    $$->type_spec_size = array_unitary_size;
  }






primary_expression :
  IDENTIFIER
  {
    $$ = new Expression_node();
    $$->var_name = $1;

    if(lst->var_to_struct[$1]!="")
    {
      $$->is_struct = true;
      // allocate new temp variable
      std::string variable_name = "t"+std::to_string(count_temp_var);
      $$->var_name = variable_name;

      int struct_size = struct_to_size[lst->var_to_struct[$1]];
      $$->type_spec_size = struct_size;

      curr_offset -= 4;
      count_temp_var += 1;
      lst->var_offsets[variable_name] = curr_offset;
      lst->var_to_struct[variable_name] = lst->var_to_struct[$1];

      functions.push_back("\tleal\t" + std::to_string(lst->var_offsets[$1]) + "(%ebp), %eax");
      functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset)+"(%ebp)");

      // copy_struct(curr_offset-4, lst->var_offsets[$1], struct_size, functions);
      // curr_offset -= 4*struct_size;
      // count_temp_var += struct_size;

    }
  }
  | INT_CONSTANT
  {
    $$ = new Expression_node();
    $$->var_name = "t"+std::to_string(count_temp_var);
    curr_offset -=4;
    lst->var_offsets["t"+std::to_string(count_temp_var)] = curr_offset;

    count_temp_var+=1;

    // store the value INT_CONSTANT to %eax
    functions.push_back("\tmovl\t$" + $1 + ", %eax");
    
    // functions.push_back("subl\t$4, %esp");
    // store the value of %eax in $->var_name
    functions.push_back(store(curr_offset, "%eax", 1));
  }
  | '(' expression  ')'
  {
    $$ = $2;
  }





unary_operator :
  '-'
  {
    $$ = new Unary_Operator_Node();
    $$->op = Unary_OP::OP_SUB;
  }
  | '!'
  {
    $$ = new Unary_Operator_Node();
    $$->op = Unary_OP::OP_NOT;
  }
  | '&' //P5
  {
    $$ = new Unary_Operator_Node();
    $$->op = Unary_OP::OP_DEREF;
  }
  | '*' //P5
  {
    $$ = new Unary_Operator_Node();
    $$->op = Unary_OP::OP_REF;
  }





selection_statement :
  IF '(' expression
  {
    //Label to jump to else
    reserve_lbl1.push(count_label);

    functions.push_back("\tcmpl\t$0, " + std::to_string(lst->var_offsets[$3->var_name]) + "(%ebp)");
    functions.push_back("\tje\tLC" + std::to_string(count_label));

    count_label+=1;
  } ')' statement
  {
    // Label to jump to after executing corresponding to when "if" is true
    reserve_lbl2.push(count_label);

    functions.push_back("\tjmp\tLC" + std::to_string(count_label));
    count_label+=1;
  } ELSE
  {
    functions.push_back("LC" + std::to_string(reserve_lbl1.top()) + ":");
    reserve_lbl1.pop();
  } statement

iteration_statement :
  WHILE '('
  {
    reserve_lbl2.push(count_label);
    functions.push_back("LC" + std::to_string(count_label) + ":");

    count_label+=1;
  } expression ')'
  {
    reserve_lbl1.push(count_label);

    functions.push_back("\tcmpl\t$0, " + std::to_string(lst->var_offsets[$4->var_name]) + "(%ebp)");
    functions.push_back("\tje\tLC" + std::to_string(count_label));

    count_label+=1;
  } statement
  {
    functions.push_back("\tjmp\tLC" + std::to_string(reserve_lbl2.top()));
    reserve_lbl2.pop();
  }
  | FOR '(' assignment_expression ';'
  {
    // pushing Ly to stack2
    reserve_lbl2.push(count_label);
    functions.push_back("LC" + std::to_string(count_label) + ":");

    count_label+=1;
  } expression  ';'
  {
    functions.push_back("\tcmpl\t$0, " + std::to_string(lst->var_offsets[$6->var_name]) + "(%ebp)");
    
    // pushing Lx to stack1
    reserve_lbl1.push(count_label);
    functions.push_back("\tje\tLC" + std::to_string(count_label));
    count_label+=1;

    // pushing Lz to stack2
    reserve_lbl2.push(count_label);
    functions.push_back("\tjmp\tLC" + std::to_string(count_label));
    count_label+=1;


    // pushing Lp to stack1
    reserve_lbl1.push(count_label);
    functions.push_back("LC" + std::to_string(count_label) + ":");
    count_label+=1;

  } assignment_expression ')'
  {
    int tempz = reserve_lbl2.top();
    reserve_lbl2.pop();

    int tempy = reserve_lbl2.top();
    reserve_lbl2.pop();

    functions.push_back("\tjmp\tLC" + std::to_string(tempy));

    functions.push_back("LC" + std::to_string(tempz) + ":");
  } statement
  {
    functions.push_back("\tjmp\tLC" + std::to_string(reserve_lbl1.top()));
    reserve_lbl1.pop();
  }

expression_list :
  expression
  {
    $$ = new Expression_List();
    $$->exp_list.push_back(*$1);

    // functions.push_back("Executing printf and function call expression list");
  }
  | expression_list ',' expression
  {
    $$ = $1;
    $$->exp_list.push_back(*$3);
  }


/* Procedure Call */
procedure_call
  : IDENTIFIER '(' ')' ';' // P3
  {
    functions.push_back("\tcall\t" + $1);

  }
  | IDENTIFIER '(' expression_list ')' ';' // P3
  {
    std::vector<Expression_node> temp_exp_list;
    temp_exp_list = $3->exp_list;

    // std::reverse(temp_exp_list.begin(), temp_exp_list.end());

    for(auto i:temp_exp_list)
    {
      if(i.is_struct)
      {
        functions.push_back("\tmovl\t" + std::to_string(lst->var_offsets[i.var_name]) + "(%ebp), %eax");
        
        for(int j=0;j<i.type_spec_size;j++)
          functions.push_back("\tpushl\t"+ std::to_string(-4*j) +"(%eax)");
      }
      else
        functions.push_back("\tpushl\t" + std::to_string(lst->var_offsets[i.var_name]) + "(%ebp)");
    }
    functions.push_back("\tcall\t" + $1);

    functions.push_back("\taddl\t$" + std::to_string(4*(temp_exp_list.size())) + ", %esp");
  }


printf_call : 
PRINTF '(' STRING_LITERAL ')' ';'
{
  $$ = new printf_astnode();

  $$->label_number = count_label;
  $$->p_statement = $3;
  labels.push_back("LC"+std::to_string(count_label)+":");
  labels.push_back("\t.string "+$3);
  count_label+=1;
}
| PRINTF '(' STRING_LITERAL ',' expression_list ')' ';'
{
  $$ = new printf_astnode();

  $$->label_number = count_label;
  $$->p_statement = $3;
  labels.push_back("LC"+std::to_string(count_label)+":");
  labels.push_back("\t.string "+$3);
  count_label+=1;

  $$->arguments = $5->exp_list;

  
}

%%

void 
IPL::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cout << "Error at line " << l.begin.line << ": " << err_message <<"\n";
   exit(1);
}


