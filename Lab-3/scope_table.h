#include "symbol_info.h"

class scope_table
{ 
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;
    
    int hash_function(string name){
        int hash = 0;
        for (char letter : name){
            hash += letter; 
        }
        return hash % bucket_count; 
    }



public:

    scope_table() : bucket_count(101), unique_id(0), parent_scope(nullptr), table(vector<list<symbol_info*>>(101)) {}
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope);
    scope_table *get_parent_scope();
    int get_unique_id();
    symbol_info *lookup_in_scope(symbol_info* symbol);
    bool insert_in_scope(symbol_info* symbol);
    void print_scope_table(ofstream& outlog, int current_scope_id);
    ~scope_table();

    
};

scope_table::scope_table(int bucket_count, int unique_id, scope_table *parent_scope) //scope table creation
{
    this->bucket_count = bucket_count;
    this->unique_id = unique_id;
    this->parent_scope = parent_scope;
    this->table = vector<list<symbol_info*>>(bucket_count); //vector of lists of symbol_info pointers
}

scope_table* scope_table::get_parent_scope() {
    return parent_scope;
}

int scope_table::get_unique_id() {
    return unique_id;
}


symbol_info* scope_table::lookup_in_scope(symbol_info* symbol) { //look for the symbol in cur scope
    int index = hash_function(symbol->get_name());
   
    for (symbol_info* sym : table[index]) {         //iterate over the list of symbol_info pointers
        if (sym->get_name() == symbol->get_name()) {
            return sym;
        }
    }
    return nullptr;
}

bool scope_table::insert_in_scope(symbol_info* symbol) {
    if (lookup_in_scope(symbol) != nullptr) {
        return false; //Symbol present
    }
    int index = hash_function(symbol->get_name());
    table[index].push_back(symbol);  //insert the symbol in the list of symbol_info pointers
    return true;
}






void scope_table::print_scope_table(ofstream& outlog, int current_scope_id) {
    
    
    outlog << "ScopeTable # " << current_scope_id << endl;
    
    for (int i = 0; i < bucket_count; ++i) {
        
        if (!table[i].empty()) {
            
            outlog << i << " -->"<<endl;
            
            for (auto symbol : table[i]) {
                
                std::string name = symbol->get_name();

                
                if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                    continue;
                }
                
                outlog << "< " << symbol->get_name() << " : " << "ID" << " >" << endl;

                
                if (symbol->get_data_type() == "function") {
                    
                    outlog << "Function Definition" << endl;
                    outlog << "Return Type: " << symbol->get_type() << endl;
                    outlog << "Number of Parameters: " << symbol->get_param_types().size() << endl;

                   
                    outlog << "Parameter Details: ";
                    
                    for (size_t j = 0; j < symbol->get_param_types().size(); ++j) {
                        outlog << symbol->get_param_types()[j] << " " << symbol->get_param_names()[j];
                        if (j != symbol->get_param_types().size() - 1) {
                            outlog << ", ";  
                        }
                    }
                    outlog << endl;
                } else if (symbol->get_data_type() == "Array") {
                    
                    outlog << "Array" << endl;
                    outlog << "Type: " << symbol->get_type() << endl;
                    outlog << "Size: " << symbol->get_array_size() << endl;
                }
                else {
                    outlog << "" << symbol->get_data_type() << endl;
                    outlog << "Type: " << symbol->get_type() << endl;
                }

                outlog << endl; //newline
            }
        }
    }

    
}




scope_table::~scope_table()
{
    for (int i = 0; i < bucket_count; ++i)
    {
        for (auto symbol : table[i])
        {
            delete symbol;
        }
    }
    
}
