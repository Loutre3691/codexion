#include "codexion.h"

/*premeir arrive, premier premier servi*/
long long    fifo(t_coder *coder)
{
    return (coder->id);
}

/*deadline la plus proche*/
long long   edf(t_coder *coder)
{
    return (coder->id);
}