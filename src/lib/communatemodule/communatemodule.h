#ifndef COMMUNATEMODULE_H
#define COMMUNATEMODULE_H

#include <singleton/TSingleton.hpp>
#include "communatemodule_global.h"

class COMMUNATEMODULE_EXPORT Communatemodule : public TSingleton<Communatemodule>
{
    friend class TSingleton<Communatemodule>;
public:
    void subscribeSig();
    void publishSig();

    void registerSig();
    void unRegisterSig();

private:
    Communatemodule();


};

#endif // COMMUNATEMODULE_H
