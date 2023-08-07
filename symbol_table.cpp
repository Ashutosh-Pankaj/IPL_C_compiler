#include "symbol_table.hh"

namespace IPL
{
    void copy_struct(int off_struct1, int off_struct2, int struct_size, std::vector<std::string>& functions)
    {
        // struct1 = struct2
    }
    

    void struct_OP_handler(Expression_node* exp, std::vector<std::string>& functions, LST* lst)
    {
        if(exp->is_struct == true || exp->is_pointer == true)
        {
        
        functions.push_back("\tmovl\t" + std::to_string(lst->var_offsets[exp->var_name]) + "(%ebp), %eax");
        functions.push_back("\tmovl\t(%eax), %eax");
        functions.push_back("\tmovl\t%eax, "+ std::to_string(lst->var_offsets[exp->var_name]) + "(%ebp)");

        exp->is_struct = false;
        exp->is_pointer = false;
        }
    }

    std::string load(int offset, std::string reg, int tabs)
    {
        // load value from offset(%ebp) to reg
        std::string s="";
        while(tabs--)
        {
            s += "\t";
        }

        s += "movl\t" + std::to_string(offset) + "(%ebp), " + reg;

        return s;
    }

    std::string store(int offset, std::string reg, int tabs)
    {
        // store value in reg to offset(%ebp)

        std::string s="";
        while(tabs--)
        {
            s += "\t";
        }

        s += "movl\t" + reg + ", " + std::to_string(offset) + "(%ebp)";

        return s;
    }
    
    // PointerVariable :: PointerVariable(int n, Base_Type b_type)
    // {
    //     numberOfStars = n;
    //     base_type = b_type;
    //     struct_name = "";
    // }

    // PointerVariable :: PointerVariable(int n, Base_Type b_type, std::string s_name)
    // {
    //     numberOfStars = n;
    //     base_type = b_type;
    //     struct_name = s_name;
    // }

    Parameter :: Parameter()
    {
        numberOfStars = 0;
        array_size = 1;
    }
    
    Expression_node :: Expression_node()
    {
        type_spec_size = 1;
        is_struct = false;
        is_pointer = false;
    }

    Declarator :: Declarator()
    {
        is_pointer = false;
        numberOfStars = 0;
        array_size = 1;
    }
    
    Declaration :: Declaration()
    {
        type_spec_size = 1;
    }

    Func_Def::Func_Def()
    {
        return_size = 1;
    }

    
    void Assign_Node :: assembly_print(std::vector<std::string>& functions, LST* lst)
    {
        
        if(exp1->is_struct == false && exp2->is_struct == false)
        {
            // var x = var y
            assembly_print1(functions, lst);
        }
        else if(exp1->is_struct == false && exp2->is_struct == true)
        {
            // var x = var struct.a
            assembly_print2(functions, lst);   
        }
        else if(exp1->is_struct == true && exp2->is_struct == false)
        {
            // var struct.a = var x;
            assembly_print3(functions, lst);
        }
        else
        {
            // var struct.a = var struct.b;
            assembly_print4(functions, lst);
        }
        
    }
    
    
    void Assign_Node :: assembly_print1(std::vector<std::string>& functions, LST* lst)
    {
        // var x = var y
        functions.push_back(load(lst->var_offsets[exp2->var_name], "%eax", 1));

        //if exp2 is a pointer, actual value is stored in *eax
        if(exp2->is_pointer)
            functions.push_back("\tmovl\t(%eax), %eax");
        
        int offset = lst->var_offsets[exp1->var_name];
        if(exp1->is_pointer)
        {
            //Read the address of the variable exp1 is pointing to
            functions.push_back(load(offset, "%ebx", 1));
            //store the value of eax in *ebx
            functions.push_back("\tmovl\t%eax, 0(%ebx)");
        }
        else
            functions.push_back(store(offset, "%eax", 1));
        
    }

    void Assign_Node :: assembly_print2(std::vector<std::string>& functions, LST* lst)
    {
        // var x = var struct.a

        int offset1 = lst->var_offsets[exp2->var_name];
        // functions.push_back("\tmovl\t" + std::to_string(offset1) + "(%ebp), %eax");
        functions.push_back(load(offset1, "%eax", 1));

        functions.push_back("\tmovl\t(%eax), %eax");

        int offset2 = lst->var_offsets[exp1->var_name];
        // functions.push_back("\tmovl\t%eax, " + std::to_string(offset2) + "(%ebp)");

        if(exp1->is_pointer)
        {
            //Read the address of the variable exp1 is pointing to
            functions.push_back(load(offset2, "%ebx", 1));
            //store the value of eax in *ebx
            functions.push_back("\tmovl\t%eax, 0(%ebx)");
        }
        else
            functions.push_back(store(offset2, "%eax", 1));
        
    }

    void Assign_Node :: assembly_print3(std::vector<std::string>& functions, LST* lst)
    {
        // var struct.a = var x;

        int offset1 = lst->var_offsets[exp1->var_name];
        // functions.push_back("\tmovl\t" + std::to_string(offset1) + "(%ebp), %eax");
        functions.push_back(load(offset1, "%eax", 1));

        

        int offset2 = lst->var_offsets[exp2->var_name];
        // functions.push_back("\tmovl\t" + std::to_string(offset2) + "(%ebp), %ebx");
        functions.push_back(load(offset2, "%ebx", 1));

        //if exp2 is a pointer, actual value is stored in *eax
        if(exp2->is_pointer)
            functions.push_back("\tmovl\t(%ebx), %ebx");

        functions.push_back("\tmovl\t%ebx, 0(%eax)");
        
    }

    void Assign_Node :: assembly_print4(std::vector<std::string>& functions, LST* lst)
    {
        // struct s1 = struct s2;
        int offset1 = lst->var_offsets[exp1->var_name];
        // functions.push_back("\tmovl\t" + std::to_string(offset1) + "(%ebp), %eax");
        functions.push_back(load(offset1, "%eax", 1));

        int offset2 = lst->var_offsets[exp2->var_name];
        // functions.push_back("\tmovl\t" + std::to_string(offset2) + "(%ebp), %ebx");
        functions.push_back(load(offset2, "%ebx", 1));

        for(int i=0;i<exp1->type_spec_size;i++)
        {
            // functions.push_back("variable name : " + exp1->var_name + " size : " + std::to_string(exp1->type_spec_size));
            functions.push_back("\tmovl\t" + std::to_string(-4*i) + "(%ebx), %ecx");
            functions.push_back("\tmovl\t%ecx, " + std::to_string(-4*i) + "(%eax)");
        }
        
    }

    void Expression_node :: compare_statements_print(Expression_node* exp1, Expression_node* exp2, Binary_OP operand, std::vector<std::string>& functions, LST* lst)
    {
        if(operand == Binary_OP::OR)
        {
            std::string s;

            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));
            functions.push_back("\tcmpl\t$0, %eax");
            functions.push_back("\tsetne\t%al");

            // eax now stores 1 if exp1 is non-zero else 0
            functions.push_back("\tmovzbl\t%al, %eax");

            // load exp1 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));
            functions.push_back("\tcmpl\t$0, %ebx");
            functions.push_back("\tsetne\t%bl");

            // ebx now stores 1 if exp2 is non-zero else 0
            functions.push_back("\tmovzbl\t%bl, %ebx");

            // The result of exp1 OR exp2 is stored in eax now.
            functions.push_back("\torl\t%ebx, %eax");
        }
        else if(operand == Binary_OP::AND)
        {

            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));
            functions.push_back("\tcmpl\t$0, %eax");
            functions.push_back("\tsetne\t%al");

            // eax now stores 1 if exp1 is non-zero else 0
            functions.push_back("\tmovzbl\t%al, %eax");

            // load exp1 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));
            functions.push_back("\tcmpl\t$0, %ebx");
            functions.push_back("\tsetne\t%bl");

            // ebx now stores 1 if exp2 is non-zero else 0
            functions.push_back("\tmovzbl\t%bl, %ebx");

            // The result of exp1 AND exp2 is stored in eax now.
            functions.push_back("\tandl\t%ebx, %eax");
        }
        else if(operand == Binary_OP::NE)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            // load exp2 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));

            functions.push_back("\tcmpl\t%ebx, %eax");
            functions.push_back("\tsetne\t%al");

            // %eax finally stores 1 if exp1 != exp2
            functions.push_back("\tmovzbl\t%al, %eax");

        }
        else if(operand == Binary_OP::EQ)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            // load exp2 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));

            functions.push_back("\tcmpl\t%ebx, %eax");
            functions.push_back("\tsete\t%al");

            // %eax finally stores 1 if exp1 == exp2
            functions.push_back("\tmovzbl\t%al, %eax");

        }
        else if(operand == Binary_OP::LE)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            // load exp2 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));

            functions.push_back("\tcmpl\t%ebx, %eax");
            functions.push_back("\tsetle\t%al");

            // %eax finally stores 1 if exp1 == exp2
            functions.push_back("\tmovzbl\t%al, %eax");

        }
        else if(operand == Binary_OP::GE)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            // load exp2 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));

            functions.push_back("\tcmpl\t%ebx, %eax");
            functions.push_back("\tsetge\t%al");

            // %eax finally stores 1 if exp1 == exp2
            functions.push_back("\tmovzbl\t%al, %eax");

        }
        else if(operand == Binary_OP::GG)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            // load exp2 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));

            functions.push_back("\tcmpl\t%ebx, %eax");
            functions.push_back("\tsetg\t%al");

            // %eax finally stores 1 if exp1 == exp2
            functions.push_back("\tmovzbl\t%al, %eax");

        }
        else if(operand == Binary_OP::LL)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            // load exp2 in ebx
            functions.push_back(load(lst->var_offsets[exp2->var_name], "%ebx", 1));

            functions.push_back("\tcmpl\t%ebx, %eax");
            functions.push_back("\tsetl\t%al");

            // %eax finally stores 1 if exp1 == exp2
            functions.push_back("\tmovzbl\t%al, %eax");

        }
        else if(operand == Binary_OP::ADD)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            functions.push_back("\taddl\t" + std::to_string(lst->var_offsets[exp2->var_name]) + "(%ebp), %eax");
        }
        else if(operand == Binary_OP::SUB)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            functions.push_back("\tsubl\t" + std::to_string(lst->var_offsets[exp2->var_name]) + "(%ebp), %eax");
        }
        else if(operand == Binary_OP::MUL)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            functions.push_back("\timull\t" + std::to_string(lst->var_offsets[exp2->var_name]) + "(%ebp), %eax");
        }
        else if(operand == Binary_OP::DIV)
        {
            // load exp1 in eax
            functions.push_back(load(lst->var_offsets[exp1->var_name], "%eax", 1));

            functions.push_back("\tcltd\n\tidivl\t" + std::to_string(lst->var_offsets[exp2->var_name]) + "(%ebp)");
        }
    }

    Expression_node* Binary_Operation_Helper(Expression_node* exp1, Expression_node* exp2, Binary_OP binary_op, int count_temp_var, int curr_offset, std::vector<std::string>& functions, LST* lst)
    {
        Expression_node* ans;
        
        ans = new Expression_node();

        // the address of a temporary variable corresponding to type struct s.a would
        // contain the net address (ebp+offset) of variable a.
        // struct_OP_handler fetches the value of variable a and stores it in the address
        // of the temporary variable
        struct_OP_handler(exp1, functions, lst);
        struct_OP_handler(exp2, functions, lst);

        // retrieving value of exp1 OR exp2 in eax
        ans->compare_statements_print(exp1, exp2, binary_op, functions, lst);

        ans->var_name = "t"+std::to_string(count_temp_var);
        // curr_offset -=4;
        lst->var_offsets["t"+std::to_string(count_temp_var)] = curr_offset-4;
        

        // count_temp_var+=1;

        // functions.push_back("subl\t$4, %esp");
        // store the value of %eax in $->var_name
        functions.push_back(store(curr_offset-4, "%eax", 1));

        return ans;
    }

    Expression_node* Unary_Operation_Helper(Expression_node* exp, Unary_OP unary_op, int count_temp_var, int curr_offset, std::vector<std::string>& functions, LST* lst, std::map<std::string, int>& struct_to_size)
    {
        Expression_node* ans;
        
        ans = new Expression_node();


        
        if(unary_op == Unary_OP::OP_SUB)
        {
            struct_OP_handler(exp, functions, lst);
            
            // load $0 to eax
            functions.push_back("\tmovl\t$0, %eax");

            // sub $2's value from %eax
            functions.push_back("\tsubl\t" + std::to_string(lst->var_offsets[exp->var_name]) + "(%ebp), %eax");

            // create a new temp variable and store %eax to it
            ans->var_name = "t"+std::to_string(count_temp_var);
            // curr_offset -=4;
            lst->var_offsets["t"+std::to_string(count_temp_var)] = curr_offset-4;

            // count_temp_var+=1;

            // functions.push_back("subl\t$4, %esp");
            // store the value of %eax in $->var_name
            functions.push_back(store(curr_offset-4, "%eax", 1));

        }
        else if(unary_op == Unary_OP::OP_NOT)
        {
            struct_OP_handler(exp, functions, lst);
            
            functions.push_back(load(lst->var_offsets[exp->var_name], "%eax", 1));

            functions.push_back("\tcmpl\t$0, %eax");
            functions.push_back("\tsete\t%al");

            // eax now stores 0 if exp1 is non-zero else 1
            functions.push_back("\tmovzbl\t%al, %eax");

            // create a new temp variable and store %eax to it
            ans->var_name = "t"+std::to_string(count_temp_var);
            // curr_offset -=4;
            lst->var_offsets["t"+std::to_string(count_temp_var)] = curr_offset-4;

            // count_temp_var+=1;

            // functions.push_back("subl\t$4, %esp");
            // store the value of %eax in $->var_name
            functions.push_back(store(curr_offset-4, "%eax", 1));
        }
        else if(unary_op == Unary_OP::OP_POST_INC)
        {
            struct_OP_handler(exp, functions, lst);
            
            // load value of $1 to eax and then to $$
            functions.push_back(load(lst->var_offsets[exp->var_name], "%eax", 1));

            ans->var_name = "t"+std::to_string(count_temp_var);
            // curr_offset -=4;
            lst->var_offsets["t"+std::to_string(count_temp_var)] = curr_offset-4;

            // count_temp_var+=1;

            // functions.push_back("subl\t$4, %esp");
            // store the value of %eax in $->var_name
            functions.push_back(store(curr_offset-4, "%eax", 1));

            // increase value of %eax by 1 and store it back
            functions.push_back("\taddl\t$1, %eax");
            functions.push_back(store(lst->var_offsets[exp->var_name], "%eax", 1));
        }
        else if(unary_op == Unary_OP::OP_REF)
        {
            // functions.push_back("Must enter this one to execute *a");
            
            
            
            std::string variable_name = "t"+std::to_string(count_temp_var);
            ans->var_name = variable_name;

            lst->var_offsets[variable_name] = curr_offset-4;

            PointerVariable pointerDetails = lst->pointer_to_details[exp->var_name];

            if(pointerDetails.numberOfStars == 1)
            {
                if(pointerDetails.base_type == Base_Type::STRUCT)
                {
                    ans->type_spec_size = struct_to_size[pointerDetails.struct_name];
                    ans->is_struct = true;

                    // functions.push_back("Entering struct *");
                    
                    functions.push_back(load(lst->var_offsets[exp->var_name], "%eax", 1));
                    //eax has the actual address of the struct and not the offset w.r.t. ebp
                    //therefore, we need to subtract epb from eax
                    functions.push_back("\tsubl\t%ebp, %eax");
                    //temporary variable of type struct only returns the base address of the struct
                    functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset-4) + "(%ebp)");
                }
                else if(pointerDetails.base_type == Base_Type::VOID)
                {
                    ans->type_spec_size = 0;
                    ans->is_struct = false;
                }
                else
                {
                    ans->type_spec_size = 1;
                    ans->is_struct = false;
                    ans->is_pointer = true;


                    // functions.push_back("Entering normal *");


                    functions.push_back(load(lst->var_offsets[exp->var_name], "%eax", 1));
                    // functions.push_back("\tmovl\t(%eax), %eax");
                    functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset-4) + "(%ebp)");
                }
            }
            else if(pointerDetails.numberOfStars > 1)
            {
                pointerDetails.numberOfStars -= 1;
                lst->pointer_to_details[variable_name] = pointerDetails;

                ans->type_spec_size = 1;
                ans->is_struct = false;
                ans->is_pointer = true;

                // functions.push_back("Entering weird *");

                functions.push_back(load(lst->var_offsets[exp->var_name], "%eax", 1));
                functions.push_back("\tmovl\t(%eax), %eax");
                functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset-4) + "(%ebp)");
            }
        }
        else if(unary_op == Unary_OP::OP_DEREF)
        {
            std::string variable_name = "t"+std::to_string(count_temp_var);
            ans->var_name = variable_name;
            lst->var_offsets[variable_name] = curr_offset-4;

            ans->type_spec_size = 1;
            ans->is_struct = false;
            // ans->is_pointer = true;

            PointerVariable* pointerDetails = new PointerVariable();
            
            if(exp->is_struct == true)
            {
                //temp variables for struct s
                if(lst->var_to_struct[exp->var_name] != "")
                {
                    pointerDetails->base_type = Base_Type::STRUCT;
                    pointerDetails->struct_name = lst->var_to_struct[exp->var_name];
                }
                //temp variables for s.a (where a id either int or a pointer)
                else
                {
                    pointerDetails->base_type = Base_Type::DEFAULT;
                    pointerDetails->struct_name = "";
                }

                // functions.push_back("Entering struct &");
                functions.push_back(load(lst->var_offsets[exp->var_name], "%eax", 1));
                functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset-4) + "(%ebp)");
            }
            else
            {
                pointerDetails->base_type = Base_Type::DEFAULT;
                pointerDetails->struct_name = "";
                
                // functions.push_back("Entering normal &");
                functions.push_back("\tleal\t" + std::to_string(lst->var_offsets[exp->var_name]) + "(%ebp), %eax");
                functions.push_back("\tmovl\t%eax, " + std::to_string(curr_offset-4) + "(%ebp)");
            }

            //if the "exp" is already a pointer
            if(lst->pointer_to_details.count(exp->var_name) > 0)
            {
                pointerDetails->numberOfStars = lst->pointer_to_details[exp->var_name].numberOfStars + 1;
            }
            else
            {
                pointerDetails->numberOfStars = 1;
            }

            lst->pointer_to_details[variable_name] = *pointerDetails;
        }

        return ans;
    }

    void catchReturnValue(int return_size, std::vector<std::string>& functions, LST *lst)
    {
        if(return_size == 1)
        {
            
        }
    }

}