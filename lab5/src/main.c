#include <stdlib.h>
#include "decode.h"
#include "encode.h"
#include "stream.h"

int main(void)
{
    TStream stream = CreateStream();
    
    char workMode = 0;
    if (InputStream(&workMode, sizeof(workMode), 1, stream) == EOF)
    {
        return EXIT_FAILURE;
    }

    switch (workMode)
    {
        case 'c':
            Encode(stream);
            break;
        case 'd':
            Decode(stream);
            break;
        default:
            return EXIT_FAILURE;
    }

    DestroyStream(&stream);
    return EXIT_SUCCESS;
}
