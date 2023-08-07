#ifndef SYMBOLTABLE_HH
#define SYMBOLTABLE_HH


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

namespace IPL
{
    enum class Symbol_Type
    {
        Struct,
        Func
    };

    enum class Binary_OP
    {
        OR,
        AND,
        NE,
        EQ,
        LE,
        GE,
        LL,
        GG,
        ADD,
        SUB,
        MUL,
        DIV
    };

    enum class Unary_OP
    {
        OP_SUB,
        OP_NOT,
        OP_POST_INC,
        OP_REF,
        OP_DEREF
    };

    enum class Base_Type
    {
        VOID,
        INT,
        STRUCT,
        ARRAY,
        POINTER,
        DEFAULT
    };

    std::string load(int offset, std::string reg, int tabs);
    std::string store(int offset, std::string reg, int tabs);
    void copy_struct(int off_struct1, int off_struct2, int struct_size, std::vector<std::string>& functions);
    
    
    class Type
    {
        public:
            Type* sub_type;

    };

    class Type_Specifier
    {
        public:
            Base_Type b_type;
            std::string struct_name;
            int size;   //required
    };

    class PointerVariable
    {
        public:
            int numberOfStars;
            Base_Type base_type;
            std::string struct_name;

            // PointerVariable(int n, Base_Type b_type);
            // PointerVariable(int n, Base_Type b_type, std::string s_name);

    };
    
    class LST
    {
        public:
            std::map<std::string, int> var_offsets;
            std::map<std::string, std::string> var_to_struct;
            std::map<std::string, PointerVariable> pointer_to_details;
    };

    class GST_entry
    {
        public:
            std::string name;
            Symbol_Type type;
            LST lst;
            int size;   //For struct, this would be the size of struct
                        //and for functions, this would be the size of return type of function

            // For Structs
            GST_entry(std::string name, Symbol_Type type, LST lst, int size)
            {
                this->name = name;
                this->type = type;
                this->lst = lst;
                this->size = size;
            }

            // For Functions
            GST_entry(std::string name, Symbol_Type type, int size)
            {
                this->name = name;
                this->type = type;
                this->size = size;
            }
    };


    class Declarator
    {
        public:
            std::string name;
            Type* type_;
            bool is_pointer;
            int numberOfStars;
            int array_size;

            Declarator();
    };

    class Declarator_List
    {
        public:
            std::stack<Declarator> var_stack;
            Type* type_;
    };

    class Declaration
    {
        public:
            std::stack<Declarator> var_stack;
            int type_spec_size;
            Type* type_;

            Declaration();
    };



    class Declaration_List
    {
        public:
            std::stack<Declaration> declarations_stack;
    };

    class Expression_node
    {
        public:
            int cvalue;
            std::string var_name;
            int type_spec_size;
            bool is_struct;
            bool is_pointer;

            Expression_node();
            
            void compare_statements_print(Expression_node* exp1, Expression_node* exp2, Binary_OP operand, std::vector<std::string>& functions, LST* lst);
    };

    class Expression_List
    {
        public:
            std::vector<Expression_node> exp_list;
            
    };

    class Assign_Node
    {
        public:
            Expression_node* exp1;
            Expression_node* exp2;

            void assembly_print(std::vector<std::string>& functions, LST* lst);
            void assembly_print1(std::vector<std::string>& functions, LST* lst);
            void assembly_print2(std::vector<std::string>& functions, LST* lst);
            void assembly_print3(std::vector<std::string>& functions, LST* lst);
            void assembly_print4(std::vector<std::string>& functions, LST* lst);
    };

    class printf_astnode
    {
        public:
            int label_number;
            std::string p_statement;
            std::vector<Expression_node> arguments;
    };

    class Unary_Operator_Node
    {
        public:
            Unary_OP op;
    };

    class selection_astnode
    {
        public:
            int else_label;
            Expression_node* condn;
        
    };

    class iteration_astnode
    {
        public:
            int true_label;
            int false_label;
            Expression_node* condn;
    };

    class for_astnode
    {
        public:
            int for_label;
            int jump_label;
            Assign_Node* assign1;
            Expression_node* condn;
            Assign_Node* assign2;
    };

    class Parameter
    {
        public:
            std::string name;
            Type* type_;
            Base_Type b_type;
            std::string struct_name;
            int numberOfStars;
            int array_size;

            Parameter();
    };

    class Parameter_List
    {
        public:
            std::stack<Parameter*> param_list;
    };

    class Struct_Node
    {
        public:
            LST lst;
            std::string struct_name;
            int size;
    };
    void struct_OP_handler(Expression_node* exp, std::vector<std::string>& functions, LST* lst);

    class Func_Def
    {
        public:
            int return_size;
            Base_Type b_type;
            int param_size;
            std::string struct_name;

            Func_Def();
    };
    
    Expression_node* Binary_Operation_Helper(Expression_node* exp1, Expression_node* exp2, Binary_OP binary_op, int count_temp_var, int curr_offset, std::vector<std::string>& functions, LST* lst);
    Expression_node* Unary_Operation_Helper(Expression_node* exp, Unary_OP unary_op, int count_temp_var, int curr_offset, std::vector<std::string>& functions, LST* lst, std::map<std::string, int>& struct_to_size);
    void catchReturnValue(int return_size, std::vector<std::string>& functions, LST *lst);
}

#endif