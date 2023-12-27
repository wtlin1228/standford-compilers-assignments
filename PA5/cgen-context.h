
//**************************************************************
//
// The Context has three components: 
//     - an environment: a mapping of variable identifiers to locations
//     - a store: a mapping of locations to values
//     - a self object: the current self object
//
// Operational Rules:
//
//                    .
//                    .
//                    .            
//        --------------------------
//          so, S, E ⊢ e1 : v, S'
//
// The rule should be read as: In the context where `self` is the 
// object `so`, the store is `S`, and the environment is `E`, the
// expression `e1` evaluates to value `v` and the new store is `S'`.
//
// Note that the new store `S'` contains all changes to memory
// resulting as a side effect of evaluating `e1`.
//
// Please refer to the Operational Semantics for Cool for more details.
//
//**************************************************************

#include "symtab.h"
#include <map>

class CgenContext;
typedef CgenContext *CgenContextP;
typedef std::pair<int, char*> MemoryAddress;

class CgenContext {
private:
    Symbol so;
    SymbolTable<Symbol, int> E;
    std::map<int, MemoryAddress> S;
    int next_loc;

public:
    CgenContext() : next_loc(0) { }
    int newloc() { return next_loc++; }

    void enterscope() { E.enterscope(); }
    void exitscope()  { E.exitscope(); }
    
    void   set_self_object(Symbol s) { so = s; }
    Symbol get_self_object() { return so; }

    void set_loc(Symbol s, int loc) { E.addid(s, new int(loc)); }
    int  get_loc(Symbol s) { return *(E.lookup(s)); }

    void          set_memory_address(int loc, MemoryAddress m) { S[loc] = m; }
    MemoryAddress get_memory_address(int loc) { return S[loc]; }
};
