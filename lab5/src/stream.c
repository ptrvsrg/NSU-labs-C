#define _CRT_SECURE_NO_WARNINGS
#include "stream.h"

TStream CreateStream(void)
{
    TStream stream = { NULL, NULL };

    stream.In = fopen("in.txt", "rb");
    if (stream.In == NULL)
    {
        ExitWithError(__FILE__, __LINE__);
    }

    stream.Out = fopen("out.txt", "wb");
    if (stream.In == NULL)
    {
        ExitWithError(__FILE__, __LINE__);
    }

    return stream;
}

int InputStream(void* value, int size, int count, TStream* stream)
{
    if (fread(value, size, count, stream->In) != count)
    {
        if (feof(stream->In))
        {
            return EOF;
        }

        DestroyStream(stream);
        ExitWithError(__FILE__, __LINE__);
    }

    return count;
}

void OutputStream(void* value, int size, int count, TStream* stream)
{
    if (fwrite(value, size, count, stream->Out) != count)
    {
        DestroyStream(stream);
        ExitWithError(__FILE__, __LINE__);
    }
}

void DestroyStream(TStream* stream)
{
    fclose(stream->In);
    fclose(stream->Out);
    stream->In = NULL;
    stream->Out = NULL;
}
