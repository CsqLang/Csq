#include <Csq/Core/Runtime/memory.h>
#include <Csq/Core/Runtime/core.h>

auto sys=[&](Cell command){
    system(command.stringVal->c_str());
};

auto shutdown=[&](){
    system("shutdown");
};