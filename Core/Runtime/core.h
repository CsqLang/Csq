#if !defined(RUNTIME_CORE_CSQ)
#define RUNTIME_CORE_CSQ

int line_ = 1;

#include "object.h"
#include "memory.h"
#include "function.h"
#include "eval.h"
#include "class.h"

map<string, int> SymTable;
map<string, Class> __classes__;

inline bool inTable(const std::string& name) {
    return SymTable.find(name) != SymTable.end();
}

inline const Cell& id(const std::string& identifier) {
    auto it = SymTable.find(identifier);
    if (it != SymTable.end()) {
        return memory[it->second];
    }

    // Handle the case when the identifier is not found
    static Cell defaultCell = f_val(0); // Provide an appropriate default value
    return defaultCell;
}

inline void allocateVar(const std::string& id_, const Cell& c) {
    memory.push_back(c);
    SymTable[id_] = static_cast<int>(memory.size()) - 1;
}

inline void assignVar(const std::string& id_, const Cell& c) {
    auto it = SymTable.find(id_);
    if (it != SymTable.end()) {
        memory[it->second] = c;
    }
}

// inline void forLoop(int start, int end, int step, std::function<void(int)> action) {
//     int count = (end - start) / step + 1;
//     int current = start;
    
//     for (int i = 0; i < count; i += 4) {
//         action(current);
//         current += step;
        
//         if (i + 1 < count) {
//             action(current);
//             current += step;
//         }
        
//         if (i + 2 < count) {
//             action(current);
//             current += step;
//         }
        
//         if (i + 3 < count) {
//             action(current);
//             current += step;
//         }
//     }
// }

// inline void forLoop(int start, int end, int step, std::function<void(int)> action) {
//     int i = start;
//     int unrollCount = 8;  // Unroll the loop by a factor of 8

//     // Process groups of 8 elements in each iteration
//     for (; i <= end - unrollCount * step; i += unrollCount * step) {
//         action(i);
//         action(i + step);
//         action(i + 2 * step);
//         action(i + 3 * step);
//         action(i + 4 * step);
//         action(i + 5 * step);
//         action(i + 6 * step);
//         action(i + 7 * step);
//     }

//     // Handle remaining iterations
//     for (; i <= end; i += step) {
//         action(i);
//     }
// }





#endif // RUNTIME_CORE_CSQ